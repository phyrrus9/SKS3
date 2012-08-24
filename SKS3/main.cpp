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
 File: main.cpp
 Description: The main processing code of the game, every single
 part of the game starts and ends up in either the main or game
 function of this code. This is where all of the decision making
 is done. If you want to add a new dialog to the game and have it
 accessable to the players this is where you will mess with it.
 This code will first initialize the environment variable and then
 prompt for some basic settings for the game so we know what type
 of game mode to set up. Next it will call the game function and
 pass all of the parameters (unparsed but not for long as SKS4
 will have patched most of the exploitable security errors in the
 game) and the game function will set up the screen based on the
 enviroment RAM and generate the map variables. Then it will
 start the actual game process of parsing user commands and then
 passing it on to the engine for further parsing.
 This is where it all comes together so I suggest not messing with
 this unless you know what you are doing and have already read all
 of the other files so you know what all this stuff does.
 Authors: phyrrus9 <phyrrus9@gmail.com>
 *****************************************************************/
#include "main.h"
//#include "sks4200_mainfunc.h"
bool server_mode = false;
bool client_mode = false;
bool multiplayer = false;
bool game_initialized = false;
extern int client_port;
extern int server_port;
class newlevel_thread : public tpool::Thread
{
    /*
     * This thread just plays the new level beep sound effect
     * on a separate thread once you clear a level. It is only
     * called once a level at the beginning.
     */
    virtual void Entry(void)
    {
        //while (true) //play it once, not forever....
        {
            {
                if (env.music)
                    play_music("afplay /usr/share/sks3/next_level.mp3 -v 3 &");
            }
        }
    }
};
int main(int argc, const char * argv[])
{
    /*
     * Main function, this is what the OS calls when the
     * program execution is requested (and on some systems
     * after the signature is verified and a sandbox is set
     * up). This sets everything up for the game to be playable.
     * After everything is set up, it forwards its args to the 
     * game function and all is good.
     */
    resizeterm(181, 48);
    environment_init(env);
    long seed = time(0);
    clear();
    displaylauncher();
    cout << ">";
    int selection;
    cin >> selection;
    extern int playernum;
    extern char * hostname;
    //env.allow_refresh = false;
    if (selection == 1)
    {
        //nothing here... idk why i added this
    }
    if (selection == 2)
    {
        env.music = false;
    }
    if (selection == 1 || selection == 2)
    {
        int difficulty_selection = 0;
        while (difficulty_selection < 1 || difficulty_selection > 2)
        {
            cout << "Please select a difficulty:" << endl
                << "1. Normal (1x damage and strength)" << endl
                << "2. Hard   (2x damage and strength)" << endl
                << "--> Hard also has around 2.5x more enemies" << endl;
            cin >> difficulty_selection;
        }
        env.difficulty = (character::difficulty)(difficulty_selection - 1);
    }
    if (selection == 3)
    {
        multiplayer = true;
        cout << "Which player are you? (1/2) ";
        int player;
        cin >> player;
        playernum = player;
        strcpy(hostname, "localhost");
    }
    if (selection == 4)
    {
        cout << "This game uses TCP ports 5101-5103. Please make sure to patch them through"
             << " your firewall if you wish for this to actually work." << endl
             << "This game uses networking before the screen refreshes, so playing over "
             << "an internet connection may be slow." << endl;
        multiplayer = true;
        cout << "Which player are you? (1/2) ";
        int player;
        cin >> player;
        playernum = player;
        cout << "Please enter the server host: ";
        char * host = new char[255];
        cin >> host;
        strcpy(hostname, host);
        delete host;
    }
    if (selection == 3 || selection == 4)
    {
        do
        {
            cout << "Please enter a seed number (between 1 and " << INT_MAX << ") ";
            cin >> seed;
        } while (seed < 0 || seed > INT_MAX);
    }
    if (multiplayer)
        env.multiplayer = true;
    if (selection == 5)
    {
        ks4200("help");
        getch_();
        ks4200("not_debug");
        exit(EXIT_SUCCESS);
    }
    if (selection == 6)
    {
        launch_sks4200(); //if your going to use this, you MUST 'make install' first
        exit(EXIT_SUCCESS);
    }
    if (selection == 7)
    {
        ofstream sksfastboot(".sksfastboot", ios::out | ios::trunc);
        sksfastboot << "Hello World!";
        sksfastboot.close();
        exit(EXIT_SUCCESS);
    }
    if (selection == 8)
    {
        system("rm .sksfastboot");
        exit(EXIT_SUCCESS);
    }
    if (selection >= 9 || selection <= 0)
        exit(EXIT_SUCCESS);
    if (argc > 1)
    {
        seed = atoi(argv[1]);
    }
    srand((int)seed);
    showhelp();
    game(argc, argv);
}
void game(int argc, const char * argv[])
{
    /*
     * This is the entire game, yes it is all inside one function,
     * what ya gonna do about it. Anyways this uses all the engine
     * commands to make it all wok. This does some minor thinking
     * and the engine does the rest. See engine.h
     */
    game_initialized = true;
    populate();
    extern int playernum;
    if (multiplayer)
    {
        if (playernum == 1) //player 1
        {
            server_port = portnum;
            server(server_port);
            client_port = portnum + 1;
        }
        if (playernum == 2) //player 2
        {
            server_port = portnum + 1;
            server(server_port);
            client_port = portnum;
        }
    }
    bool run = true;
    while (run)
    {
        if (!env.showmap)
            env.view = (char *)&env.map;
        else
            env.view = (char *)&env.grid;
        if (env.kills >= env.kills_needed)
        {
            newlevel_thread *newlvl_sound = new newlevel_thread;
            newlvl_sound->Run();
            env.levels_completed++;
            env.position = 0;
            env.score += env.kills;
            populate();
            continue;
        }
        if (env.keys >= 500)
        {
            env.score += (env.keys /= 5);
            env.keys -= 500;
        }
        
        if (env.levels_completed > 0) //level 2
            env.weapons[1] = true; //enable the throwing star
        if (env.levels_completed > 4) //level 5
            env.weapons[2] = true; //enable the sword
        if (env.levels_completed > 9) //level 10
            env.weapons[3] = true; //enable the gun
        if (env.levels_completed > 24) //level 25
            env.weapons[4] = true; //enable the canon
        if (env.levels_completed > 49) //level 50
            env.weapons[5] = true; //enable the laser
        if (env.levels_completed > 74) //level 75
            env.weapons[6] = true; //enable the stocking
        if (env.levels_completed > 99) //level 100
            env.weapons[7] = true; //enable the admin gun
        
        if (env.health <= 0 || env.time_up)
        {
            if (env.lives <= 0 || env.time_up)
            {
                env.allow_refresh = false;
                //clear();
                if (env.lives <= 0 && env.health <= 0)
                    cout << "You are dead..." << endl;
                else
                    cout << "Time up!" << endl;
                cout << "Your score was " << env.totalscore << endl;
                bool high = false;
                for (int i = 0; i < hiscore::num_scores; i++)
                    if (env.totalscore > env.hiscorelist[i].score)
                        high = true;
                if (high)
                    hiscore::user_save();
                music_stop();
                colorify(NORMAL);
                run = false;
                hiscore::display();
            }
            else
            {
                env.lives -= 1;
                env.health = 100;
            }
        }
        if (run)
        {
            env.refresh_screen = true;
            char a = getch_();
            bool turning = false, moving = false;
            direction t;
            if (char_int(a) != -1)
                for (int i = 0; i < weapons::num_of_weapons + 1; i++)
                    if (char_int(a) == i)
                        setselectedweapon(i - 1);
            if (a == env.settings.keys.w)
            {
                t = N;
                moving = true;
            }
            if (a == env.settings.keys.a)
            {
                t = E;
                moving = true;
            }
            if (a == env.settings.keys.s)
            {
                t = S;
                moving = true;
            }
            if (a == env.settings.keys.d)
            {
                t = W;
                moving = true;
            }
            if (a == env.settings.keys.i)
            {
                turning = true;
                t = N;
            }
            if (a == env.settings.keys.j)
            {
                turning = true;
                t = E;
            }
            if (a == env.settings.keys.k)
            {
                turning = true;
                t = S;
            }
            if (a == env.settings.keys.l)
            {
                turning = true;
                t = W;
            }
            if (a == env.settings.keys.attack)
                attack();
            if (a == 'E')
                increment_attack();
            if (a == 'o')
            {
                env.allow_refresh = false;
                //clear();
                hiscore::display();
            }
            if (a == 'O')
            {
                t = HSC_SAV;
                _move;
            }
            if (a == -97) //alt/option + s
            {
                t = SAVS;
                _move;
            }
            if (a == -82) //alt/option + r
            {
                t = RESS;
                _move;
            }
            if (a == env.settings.keys.S)
            {
                t = SAV;
                _move;
            }
            if (a == env.settings.keys.R)
            {
                t = RES;
                _move;
            }
            if (a == env.settings.keys.quit)
            {
                t = QUI;
                _move;
            }
            if (a == 'H')
            {
                t = HLP;
                _move;
            }
            if (a == env.settings.keys.pause)
            {
                if (env.paused)
                    t = UNPAU;
                else
                    t = PAU;
                _move;
            }
            if (a == 'm')
            {
                if (env.music)
                {
                    music_stop();
                }
                else
                {
                    env.music = true;
                    music_start();
                }
            }
            if (a == 'n')
            {
                if (env.music)
                {
                    music_stop();
                    env.current_song++;
                    if (env.current_song >= env.number_of_songs)
                        env.current_song = 0;
                    env.music = true;
                    music_start();
                }
            }
            if (a == 'N')
                execl(argv[0], argv[0], (char *)NULL);
            if (a == env.settings.keys.settings)
            {
                env.allow_refresh = false;
                clear();
                settings_window();
                env.allow_refresh = true;
            }
            if (a == env.settings.keys.engine)
            {
                cout << ">";
                env.allow_refresh = false;
                string command1, command2;
                cin >> command1 >> command2;
                enginecmd(command1, command2);
                env.allow_refresh = true;
                t = NIL;
            }

            if (turning)
                turn(t);
            else
                if (moving)
                    move(t);
                else
                    continue;
        }
    }
    return;
}
void displaylauncher(void)
{
    /*
     * This is a pretty simple function, just displays a menu allowing
     * the user to select what he/she wants to do with the game. Options
     * parsed in main function.
     */
    cout << "#######################################################" << endl
         << "#Welcome  to  Super  Key  Seeker  3  ©  2012  phyrrus9#" << endl
         << "#This game has several modes to select, but if for you#" << endl
         << "#want to play the older games, there is a downloader  #" << endl
         << "#in this menu, it requires internet to work. Thanks :)#" << endl
         << "#Please select an option from the list below to start #" << endl
         << "#1. Single player (local) game                        #" << endl
         << "#2. Single player (local) game no sound (OSX only)    #" << endl
         << "#3. Miltiplayer (local) game                          #" << endl
         << "#4. Multiplayer (online) game                         #" << endl
         << "#5. Play KS4200                                       #" << endl
         << "#6. Play SKS4200                                      #" << endl
         << "#7. Enable fastboot                                   #" << endl
         << "#8. Disable fastboot                                  #" << endl
         << "#9. Exit                                              #" << endl
         << "*** Note: you can specify a seed by running \"sks3 #\"  #" << endl
         << "*** ->seeds make the map the same across all games    #" << endl
         << "#######################################################" << endl;
}
