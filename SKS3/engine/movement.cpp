/*****************************************************************
 Super Key Seeker Version 3
 Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 This software is free, it may be customized, redistributed
 or used in any way that suits your needs. This software is
 open source, meaning that it MUST be distributed along with
 its source code or have provisions to recieve the source code
 if desired. This program, though it is free and open source
 is still copyright © the following names and companies:
 Ethan Laur (phyrrus9) <phyrrus9@gmail.com> 2012
 MOD Technologies LLC <http:modtech.co> 2012
 This program source code MUST be distributed with this comment
 block intact as a reference to users who would actually like
 to follow the rules. Please do not be a jerk and take credit
 for a program you did not write. This code for the most part
 was written by the following people and companies:
 Ethan Laur (phyrrus9) <phyrrus9@gmail.com>
 Dereck Wonnacott <dereck@gmail.com>
 GNU Project (for ncurses which we all so dearly love)
 All third party lisencing by the above authors is transmitted
 with the source code of this program to its new author, who
 may add his or her name to this block for the works they did
 It is greatly appreciated if any work you do on the program
 is reported back to the original authors (copyright section)
 so that we can incorporate your features into the game as a
 public release. We thank you for reading this file.
 If you want to know how many lines of code are in this project,
 you can just cd into the source directory and run the following
 find . -type f -print0 | xargs -0 cat | wc -l
 =================================================================
 File: movement.cpp
 Description: Code that handles moving and interacting with the
 little red character you see on your screen. It is probablt the
 most unorganized part of the program because it has crap like the
 multiplayer sockets, map population code and all that stuff that
 should be somewhere else...
 Authors: phyrrus9 <phyrrus9@gmail.com>
 *****************************************************************/
#include "movement.h"
extern _environment env; //global variable
bool thread_started = false;
class socket_thread : public tpool::Thread
{
    /*
     * This thread (multiplayer only) just gets rid of the way I used to do
     * multiplayer (by making it a turn-by-turn game where one player moved
     * and then had to wait for the other to move in order to move again
     * while there was only a relatively small ammount of data [like 25 bytes]
     * being send between clients). Now, the multiplayer works by sending and
     * recieving data every second (which really means every 5-25 sepending on
     * the speed of the internet connection) and no longer interrupts the game
     * while it waits for another set of data, instead it just displayes the
     * current env.socket_message until it gets a new one, then it sends its
     * socket message and displays the one recieved. All of this is done in
     * the background, so dont expect to see any status of it. When player 1
     * or 2 disconnect the game will still exit as usual.
     */
    virtual void Entry(void)
    {
        extern bool multiplayer;
        extern int client_port;
        extern int server_port;
        while (true)
        {
            if (multiplayer)
            {
                char host[] = "localhost";
                extern int playernum;
                if (playernum == 2)
                {
                    server(server_port);
                    client(host, client_port);
                }
                else
                {
                    client(host, client_port);
                    server(server_port);
                }
            }
            sleep(1); //update once a second instead of 1 million times a second
        }
    }
};
socket_thread *_socket_thread = new socket_thread;
void populate(void)
{
    /*
     * Seed a new map. This happens in about a quarter of a second.
     * It goes through 899 random numbers and parses what to put in
     * each section of the map. Very useful, NEVER bypass this unless
     * you want to use static maps like sks4200 did (but with the size
     * of this engine I wouldnt reccommend it because sks4200 took a 
     * good 5 minutes to compile on its 10 function engine. This one has
     * at least 50.)
     */
    int health_i = 0;
    env.map[0] = env.grid[0] = '@';
    if (!env.single)
    {
        env.kills_needed = env.kills = 0;
        for (int i = 1; i < 900; i++)
        {
            env.grid[i] = '?';
            int r = rand() % 52;
            env.map[i] = echar;
            if (r == 1)
            {
                env.kills_needed++;
                env.map[i] = '%';
            }
            if (r == 2)
            {
                env.kills_needed++;
                env.map[i] = '&';
            }
            if (r == 3)
            {
                env.kills_needed++;
                env.map[i] = '$';
            }
            if (r == 4)
            {
                health_i++;
                if (health_i % 7 == 0)
                    env.map[i] = '+';
            }
            if (r == 5)
            {
                env.kills_needed++;
                env.map[i] = '!';
            }
            if (r == 6)
            {
                env.map[i] = 'z';
                if (i % env.settings.zombie.zombie_active == 0)
                    zombie *z = new zombie(i); //activate only x% of zombies
                /************************************************
                 In Xcode, this line will throw a warning,
                 this is only because I never actually use
                 the result of the creation of z, because if
                 you look in zombie.cpp at the class constructor
                 you will see that the run method of the base
                 thread class is called from the private method
                 inside the constructor, making it one line
                 shorter and making my debug life a lot simpler
                 ***********************************************/
            }
            if (r == 7)
            {
                env.map[i] = 'k'; //don't place a whole lot of keys
            }
            if (r == 8)
            {
                env.map[i] = 'g';
                env.health++; //just give a little boost
                env.score++; //a little score boost too
            }
            if (r == 9)
            {
                env.map[i] = 'b';
                env.score += 10;
            }
            if (r == 10)
            {
                env.map[i] = '-';
            }
            if (r >= 11 && r <= 14)
                env.map[i] = '#';
            if (env.difficulty >= character::PRO)
            {
                if (r > 15 && r < 20)
                {
                    env.map[i] = 'z';
                    if (i % env.settings.zombie.zombie_active == 0)
                        zombie *z = new zombie(i); //activate more zombies as pro
                    env.kills_needed++;
                }
                if (r > 20 && r < 25)
                {
                    env.map[i] = '!';
                    env.kills_needed++;
                }
                if (r > 25 && r < 30)
                {
                    env.map[i] = '$';
                    env.kills_needed++;
                }
                if (r > 30 && r < 40)
                {
                    env.map[i] = 'g';
                    env.kills_needed++;
                    env.health += (r / 4);
                }
                if (r > 40 && r < 50)
                {
                    env.map[i] = 'b';
                    env.kills_needed += 2;
                    env.health += (r / 6);
                }
            }
            if (r > 50)
            {
                env.map[i] = 'M';
            }
                //env.dragons = new dragon[10];
        }
    }
    else
    {
        //??
    }
    env.total_enemies = env.kills_needed; //record what the full total is before subtraction
    /* do the subtraction */
    if (env.difficulty == character::NORMAL)
        env.kills_needed /= 3;
    else if (env.difficulty == character::PRO)
    {
        env.kills_needed /= 3; //sorry... but 2 just made it really hard and annoying
        env.kills_needed -= 50;
        /********************************************
         You may ask why I subtract 50 kills after
         i divide the kills by three just like I
         do when you are in normal mode. I too
         myself thought that was a bug becuase my
         thinking went "hey wait wont that actually
         make pro mode easier than normal mode??"
         Well, fact is no it will not because if
         you look above you will see that pro gets
         about 3-5 times the characters on screen
         therefore when divided by three, it is
         only the same number or a little more
         than the total number of creatures in a
         normal gameplay mode. Still though trying
         to get 200 kills is pretty annoying so we
         make it a little easier by taking off
         fifty, because 150 is easier than 200
         ********************************************/
    }
    env.map[rand() % 400] = '@'; //randomly place a teleport
    /*
     * This part is where we will check to make
     * sure that the map is playable, because
     * for some reason there is always that
     * one map that is at like level 50 that
     * has blocks at the 1 and 30 positions,
     * which means that you can't move out
     * of this trap without having cheats
     * enabled, so we will check for it and
     * correct the problem if need be.
     */
    if (env.map[1] == '#' && env.map[30] == '#') //both are walls, anything else is good
        populate(); //reseed the map so this won't happen again.
}
void turn(direction d)
{
    /*
     * When you use 'i/j/k/l' this just rotates your
     * character in that direction so you can use the
     * 'e' command to attack and such
     */
    env.player = (character::player)(d);
}
void move(direction d)
{
    /*
     * This parses most of your actions. This just figures out
     * if there are any zombies nearby, if there are not then
     * it will make your move and call the respective functions
     * to do exactly what you want. This is the first link of the
     * chain call that can go 30+ functions back in the engine
     * before it must return here and update your monitor. All
     * of this happens in less than an eighth of a second.
     */
    if (env.paused && d != UNPAU)
        return; //you arnt allowed to move while paused... thats cheating...
    void (*prev_fn)(int);
    prev_fn = signal (SIGSEGV,terminate); //bugfix
    int prev = env.position;
    bool moved = false;
    if (zombiecheck(env.position + 1))
        do_zombie_damage();
    if (zombiecheck(env.position - 1))
        do_zombie_damage();
    if (zombiecheck(env.position + 30))
        do_zombie_damage();
    if (zombiecheck(env.position - 30))
        do_zombie_damage();
    d(N)
        if (env.map[env.position - 30] != '#' && (env.position - 30 > 0))
        {
            eat(env.position - 30);
            env.position -= 30;
            moved = true;
        }
    d(S)
        if (env.map[env.position + 30] != '#' && (env.position + 30 < 900))
        {
            eat(env.position + 30);
            env.position += 30;
            moved = true;
        }
    d(E)
        if (env.map[env.position - 1] != '#' && (env.position - 1 > 0))
        {
            eat(env.position - 1);
            env.position -= 1;
            moved = true;
        }
    d(W)
        if (env.map[env.position + 1] != '#' && (env.position + 1 < 900))
        {
            eat(env.position+ 1);
            env.position += 1;
            moved = true;
        }
    d(SAV)
        save();
    d(SAVS)
        save_slot();
    d(RESS)
        restore_slot();
    d(RES)
        restore_slot();
    d(QUI)
    {
        server_end(); //disconnect and unbind the socket
        colorify(NORMAL); //un-colorify
        if (env.music)
            kill_music("killall afplay"); //kill the music
        wpopuperror(" Program exit", " Your game is now closed.\n Press any key to close. ", 2, 24);
        exit(EXIT_SUCCESS);
    }
    d(HLP)
        showhelp();
    d(PAU)
    {
        env.paused = true;
    }
    d(UNPAU)
    {
        env.paused = false;
    }
//#define log(a) cout << a << endl;
    d(HSC_SAV)
        hiscore::user_save();
    if (moved)
    {
        env.player = (character::player)(d);
        env.map[prev] = env.grid[prev] = echar;
        env.view[env.position] = '@';
        light(env.position);
        env.moves += 1;
        if (!thread_started)
        {
            _socket_thread->Run();
            thread_started = true;
        }
    }
}
void showmap(void)
{
    /*
     * Called from the refresh thread,
     * displays the 30x30 map on the screen
     * so you can make your next move and
     * eventually die, etc
     */
    colorify();
    colorify(BORDER);
    //cout << "#  ";
    //for (int i = 0; i < 46; i++)
      //  cout << "# ";
    colorify();
    cout << "\n\r";
    for (int i = 0, j = 1; i < 900; i++, j++)
    {
        if (i % 30 == 0)
        {
            colorify(BORDER);
            //cout << "#";
            colorify();
            cout << "  ";
        }
        if (i != env.position)
        {
            if (env.view[i] != echar && env.view[i] != '#' && env.view[i] != '?')
            {
                if (env.view[i] == '+')
                {
                    colorify(BLUE);
                }
                else
                {
                    if (env.view[i] == '@') //teleport
                    {
                        colorify(RED);
                    }
                    else if (env.view[i] == 'g') //guard
                    {
                        colorify(BLUE);
                    }
                    else if (env.view[i] == 'b') //boss
                    {
                        colorify(RED);
                    }
                    else
                    {
                        colorify(GREEN);
                    }
                }
            }
            if (env.view[i] != '?' && env.view == env.map)
            {
                cout << env.view[i] << "  ";
            }
            else
            {
                cout << "   ";
            }
            colorify();
        }
        else
        {
            colorify(env.playercolor);
            //cout <<  "@";
            showplayer();
            colorify();
            cout << "  ";
        }
        if (j == 30)
        {
            colorify(BORDER);
            //cout << '#' << "\n\r";
            cout << "\n\r";
            colorify();
            j = 0;
        }
    }
    colorify(BORDER);
    //cout << "#";
    colorify();
    cout << "  ";
    for (int i = 0; i < 46; i++)
    {
        colorify(BORDER);
        //cout << "# ";
        colorify();
    }
    cout << endl;
    colorify();
    cout << "\r" << env.status_message << endl;
}
void showplayer(void)
{
    /*
     * Displays your character on screen
     */
    if (env.player == character::N)
        cout << '^';
    if (env.player == character::S)
        cout << 'v';
    if (env.player == character::E)
        cout << '<';
    if (env.player == character::W)
        cout << '>';
}
void light(int p)
{
    /*
     * With the newer versions of the game (sks4200 release 2
     * and newer), there has been a fog so you can't make an
     * effecient path to the portal (removed in sks3 but I will
     * more than likely add it again soon). This function shows
     * you the entire block around your character so you can see
     * nearby. Sorry it is hardcoded and not in an efficient loop.
     */
    if ((p - 29) >= 0)
        env.grid[p - 29] = env.map[p - 29];
    if ((p - 30) >= 0)
        env.grid[p - 30] = env.map[p - 30];
    if ((p - 31) >= 0)
        env.grid[p - 31] = env.map[p - 31];
    if ((p - 1) >= 0)
        env.grid[p - 1] = env.map[p - 1];
    if ((p + 1) < 900)
        env.grid[p + 1] = env.map[p + 1];
    if ((p + 29) < 900)
        env.grid[p + 29] = env.map[p + 29];
    if ((p + 30) < 900)
        env.grid[p + 30] = env.map[p + 30];
    if ((p + 31) < 900)
        env.grid[p + 31] = env.map[p + 31];
}
