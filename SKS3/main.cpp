/*
 * Super Key Seeker Version 3
 * Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 * This software is free, it may be customized, redistributed, blah blah blah...
 */
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
    environment_init(env);
    clear();
    displaylauncher();
    cout << ">";
    int selection;
    cin >> selection;
    extern int playernum;
    extern char * hostname;
    if (selection == 2)
    {
        multiplayer = true;
        cout << "Which player are you? (1/2) ";
        int player;
        cin >> player;
        playernum = player;
        strcpy(hostname, "localhost");
    }
    if (selection == 3)
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
    if (selection == 4)
    {
        ks4200("help");
        getch_();
        ks4200("not_debug");
        exit(EXIT_SUCCESS);
    }
    if (selection == 5)
    {
        launch_sks4200(); //if your going to use this, you MUST 'make install' first
        exit(EXIT_SUCCESS);
    }
    if (selection == 6)
    {
        ofstream sksfastboot(".sksfastboot", ios::out | ios::trunc);
        sksfastboot << "Hello World!";
        sksfastboot.close();
        exit(EXIT_SUCCESS);
    }
    if (selection == 7)
    {
        system("rm .sksfastboot");
        exit(EXIT_SUCCESS);
    }
    if (selection >= 8 || selection <= 0)
        exit(EXIT_SUCCESS);
    showhelp();
    game(argc, argv);
}
void game(int argc, const char * argv[])
{
    game_initialized = true;
    srand((unsigned)time((long)0));
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
        
        if (env.health <= 0)
        {
            if (env.lives <= 0)
            {
                cout << "You are dead..." << endl
		     << "Your score was " << env.totalscore << endl;
                run = false;
                music_stop();
                colorify(NORMAL);
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
            if (a == '1')
                setselectedweapon(0);
            if (a == '2')
                setselectedweapon(1);
            if (a == '3')
                setselectedweapon(2);
            if (a == '4')
                setselectedweapon(3);
            if (a == '5')
                setselectedweapon(4);
            if (a == '6')
                setselectedweapon(5);
            if (a == 'w')
            {
                t = N;
                moving = true;
            }
            if (a == 'a')
            {
                t = E;
                moving = true;
            }
            if (a == 's')
            {
                t = S;
                moving = true;
            }
            if (a == 'd')
            {
                t = W;
                moving = true;
            }
            if (a == 'i')
            {
                turning = true;
                t = N;
            }
            if (a == 'j')
            {
                turning = true;
                t = E;
            }
            if (a == 'k')
            {
                turning = true;
                t = S;
            }
            if (a == 'l')
            {
                turning = true;
                t = W;
            }
            if (a == 'e')
                attack();
            if (a == 'E')
                increment_attack();
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
            if (a == 'S')
            {
                t = SAV;
                _move;
            }
            if (a == 'R')
            {
                t = RES;
                _move;
            }
            if (a == 'Q')
            {
                t = QUI;
                _move;
            }
            if (a == 'H')
            {
                t = HLP;
                _move;
            }
            if (a == 'p')
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
                    env.music = false;
                    music_stop();
                }
                else
                {
                    env.music = true;
                    music_start();
                }
            }
            if (a == 'N')
                execl(argv[0], argv[0], (char *)NULL);
            if (a == '/')
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
    cout << "#######################################################" << endl
         << "#Welcome  to  Super  Key  Seeker  3  ©  2012  phyrrus9#" << endl
         << "#This game has several modes to select, but if for you#" << endl
         << "#want to play the older games, there is a downloader  #" << endl
         << "#in this menu, it requires internet to work. Thanks :)#" << endl
         << "#Please select an option from the list below to start #" << endl
         << "#1. Single player (local) game                        #" << endl
         << "#2. Single player (local) game no sound (OSX only)    #" << endl
         << "#2. Miltiplayer (local) game                          #" << endl
         << "#3. Multiplayer (online) game                         #" << endl
         << "#4. Play KS4200                                       #" << endl
         << "#5. Play SKS4200                                      #" << endl
         << "#6. Enable fastboot                                   #" << endl
         << "#7. Disable fastboot                                  #" << endl
         << "#8. Exit                                              #" << endl
         << "#######################################################" << endl;
}
