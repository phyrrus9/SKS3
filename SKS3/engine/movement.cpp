/*
 * Super Key Seeker Version 3
 * Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 * This software is free, it may be customized, redistributed, blah blah blah...
 */
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
            int r = rand() % 32;
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
            }
            if (r >= 7 && r <= 11)
                env.map[i] = '#';
            if (env.difficulty >= character::PRO)
            {
                if (r > 15 && r < 20)
                {
                    env.map[i] = 'z';
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
            }
        }
    }
    else 
    {
        //??
    }
    env.total_enemies = env.kills_needed;
    if (env.difficulty == character::NORMAL)
        env.kills_needed /= 3;
    else if (env.difficulty == character::PRO)
    {
        env.kills_needed /= 3; //sorry... but 2 just made it really hard and annoying
        env.kills_needed -= 50;
    }
    env.map[rand() % 400] = '@'; //randomly place a teleport
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
    if (d == N)
        if (env.map[env.position - 30] != '#' && (env.position - 30 > 0))
        {
            eat(env.position - 30);
            env.position -= 30;
            moved = true;
        }
    if (d == S)
        if (env.map[env.position + 30] != '#' && (env.position + 30 < 900))
        {
            eat(env.position + 30);
            env.position += 30;
            moved = true;
        }
    if (d == E)
        if (env.map[env.position - 1] != '#' && (env.position - 1 > 0))
        {
            eat(env.position - 1);
            env.position -= 1;
            moved = true;
        }
    if (d == W)
        if (env.map[env.position + 1] != '#' && (env.position + 1 < 900))
        {
            eat(env.position+ 1);
            env.position += 1;
            moved = true;
        }
    if (d == SAV)
        save();
    if (d == SAVS)
        save_slot();
    if (d == RESS)
        restore_slot();
    if (d == RES)
        restore();
    if (d == QUI)
    {
        server_end(); //disconnect and unbind the socket
        colorify(NORMAL); //un-colorify
        if (env.music)
            kill_music("killall afplay"); //kill the music
        exit(EXIT_SUCCESS);
    }
    if (d == HLP)
        showhelp();
    if (d == PAU)
    {
        env.paused = true;
    }
    if (d == UNPAU)
    {
        env.paused = false;
    }
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
    cout << "#  ";
    for (int i = 0; i < 46; i++)
        cout << "# ";
    colorify();
    cout << "\n\r";
    for (int i = 0, j = 1; i < 900; i++, j++)
    {
        if (i % 30 == 0)
        {
            colorify(BORDER);
            cout << "#";
            colorify();
            cout << "  ";
        }
        if (i != env.position)
        {
            if (env.view[i] != '~' && env.view[i] != '#' && env.view[i] != '?')
            {
                if (env.view[i] != '+')
                {
                    if (env.view[i] == '@') //teleport
                        colorify(RED);
                    else
                        colorify(GREEN);
                }
                if (env.view[i] == '+')
                    colorify(BLUE);
            }
            cout << env.view[i] << "  ";
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
            cout << '#' << "\n\r";
            colorify();
            j = 0;
        }
    }
    colorify(BORDER);
    cout << "#";
    colorify();
    cout << "  ";
    for (int i = 0; i < 46; i++)
    {
        colorify(BORDER);
        cout << "# ";
        colorify();
    }
    cout << endl;
    colorify();
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
