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

inline void sighandle(int signo)
{
    endwin(); //so we dont break our teminal
    exit(-1);
}
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
    //if (streamlib_version != GLOBAL_STREAMLIB_VERSION)
    if (!check_version_compadible()) //better method
    {
        cout << "Error! Streamlib error" << endl;
        exit(-1);
    }
    resizeterm(181, 48);
    environment_init(env);
    long seed = time(0);
    /* BEGIN DEVELOPER MODE CHECK */
    if (argc > 1)
    {
        if (strcmp(argv[1], "developer-mode") == 0)
        {
            env.developer_mode = true;
            devsettings();
            if (argc > 2)
            {
                seed = atol(argv[2]);
            }
        }
        else
        {
            seed = atol(argv[1]);
        }
    }
    /* END DEVELOPER MODE CHECK */
    //clear();
    int selection = -1;
    while (selection == -1)
        selection = displaylauncher(seed);
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
        int difficulty_selection = 1; //patch for difficulty selections
        //while (difficulty_selection < 1 || difficulty_selection > 2)
        {
            selectdifficulty();
            /*cout << "Please select a difficulty:" << endl
                << "1. Normal (1x damage and strength)" << endl
                << "2. Hard   (2x damage and strength)" << endl
                << "--> Hard also has around 2.5x more enemies" << endl;
            cin >> difficulty_selection;*/
        }
        env.difficulty = (character::difficulty)(difficulty_selection);
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
    if ((selection >= 9 || selection <= 0) && selection != 10)
        exit(EXIT_SUCCESS);
	if (!env.competition_mode)
    	srand((int)seed);
	else
		srand(env.competition.number); //seed so everybody has the same map
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
            rerunmods(env.modlist);
			env.kills = 0;
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
                env.allow_autosave = false; //make it so that they can't autosave when dead
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
            int a = getche();
            bool turning = false, moving = false;
            direction t;
            if (char_int(a) != -1)
                for (int i = 0; i < weapons::num_of_weapons + 1; i++)
                    if (char_int(a) == i)
                        setselectedweapon(i - 1);
			/*if (a == ARROW_UP)
			{
				t = N;
				moving = true;
			}
			if (a == ARROW_DOWN)
			{
				t = S;
				moving = true;
			}
			if (a == ARROW_LEFT)
			{
				t = E;
				moving = true;
			}
			if (a == ARROW_RIGHT)
			{
				t = W;
				moving = true;
			}*/
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
            if (a == env.settings.keys.ss)
            {
                t = SAVS;
                _move;
            }
            if (a == env.settings.keys.ss)
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
                    int last_song = env.current_song;
                    while (env.current_song == last_song)
                        env.current_song = rand() % env.number_of_songs;
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

void selectdifficulty(void)
{
    /*
     * Select the difficulty to play the game at. Very simple
     * function that uses ncurses windows to accomplish the
     * goal. Added in version 2.0, will be used instead of
     * the old system (of just 1 and 2) but will probably
     * at some point add support for the overseed in that
     * system for something like a level 6. Though at level
     * 6 you would only last 2 moves.
     */
    
    WINDOW *vin;
    initscr();
    refresh();
    noecho();
    int height = 11, width = 60;
    int starty = (LINES - height) / 2;	/* Calculating for a center placement */
	int startx = (COLS - width) / 2;	/* of the window		*/
    vin=newwin(height,width,starty,startx);
    wmove(vin,0,0);
    char c;
    bool finished = false;
    while (!finished)
    {
        wclear(vin);
        setdisplay(vin, " Select difficulty");
        wprintw(vin, " Please select a difficulty. Press i# for information\n or press Q to exit\n");
        wprintw(vin," 1. Easy\n"
                    " 2. Normal\n"
                    " 3. Hard\n"
                    " 4. Insane\n"
                    " 5. Good luck!\n");
        wprintw(vin, " :");
        wrefresh(vin);
        c = getch_();
        if (c == 'Q')
        {
            wpopuperror(" Program exit", " Your game is now closed.\n Press any key to close. ", 2, 24);
            _exit(1);
        }
        if (c == '1')
        {
            env.lives = 5;
            env.health = 100;
            env.zombies_do_damage = false;
            env.min_zombie_does_damage_level = 100;
            finished = true;
        }
        if (c == '2')
        {
            env.lives = 3;
            env.health = 100;
            env.zombies_do_damage = true;
            env.zombies_do_damage = 5;
            finished = true;
        }
        if (c == '3')
        {
            env.lives = 2;
            env.health = 50;
            env.zombies_do_damage = true;
            env.min_zombie_does_damage_level = 2;
            env.score_multiplier = 2;
            finished = true;
        }
        if (c == '4')
        {
            env.lives = 1;
            env.health = 100;
            env.zombies_do_damage = true;
            env.min_zombie_does_damage_level = 0;
            env.score_multiplier = 3;
            finished = true;
        }
        if (c == '5')
        {
            env.lives = 0;
            env.health = 100;
            env.zombies_do_damage = true;
            env.min_zombie_does_damage_level = 0;
            env.score_multiplier = 5;
            finished = true;
        }
        if (c == 'i')
        {
            wclear(vin);
            setdisplay(vin, " Information");
            wprintw(vin, " Please give the difficulty number\n :");
            wrefresh(vin);
            c = getch_();
            wclear(vin);
            setdisplay(vin, " Information");
            switch (c)
            {
                    /*
                     * Test switch for information. If you are
                     * wondering what the %% is for, the wprintw
                     * statements work like printf and "% " prints
                     * a null character. "%%" prints "%"
                     */
                    
                case '1':
                    wprintw(vin," Level 1: Easy\n"
                            " This level is the simplest of the five levels\n"
                            " because it gives you the following:\n"
                            " 1. 5 spare lives\n"
                            " 2. 100%% Health\n"
                            " 3. No zombie damage (ever)\n");
                    wprintw(vin, " Press any key to return. ");
                    wrefresh(vin);
                    getch_();
                    break;
                case '2':
                    wprintw(vin," Level 2: Normal\n"
                            " With this level, you get the following:\n"
                            " 1. 3 spare lives\n"
                            " 2. 100%% Health\n"
                            " 3. No zombie damage until level 5\n");
                    wprintw(vin, " Press any key to return. ");
                    wrefresh(vin);
                    getch_();
                    break;
                case '3':
                    wprintw(vin," Level 3: Hard\n"
                            " With this level, you get the following:\n"
                            " 1. 2 spare lives\n"
                            " 2. 50%% Health\n"
                            " 3. No zombie damage until level 2\n"
                            " 4. Score multiplier of x2\n");
                    wprintw(vin, " Press any key to return. ");
                    wrefresh(vin);
                    getch_();
                    break;
                case '4':
                    wprintw(vin," Level 4: Insane\n"
                            " With this level, you get the following:\n"
                            " 1. 2 spare lives\n"
                            " 2. 100%% Health\n"
                            " 3. Zombies always do damage\n"
                            " 4. Score multiplier of x3\n");
                    wprintw(vin, " Press any key to return. ");
                    wrefresh(vin);
                    getch_();
                    break;
                case '5':
                    wprintw(vin," Level 5: Good luck!\n"
                            " With this level, you get the following:\n"
                            " 1. 0 spare lives\n"
                            " 2. 100%% Health\n"
                            " 3. Zombies always do damage\n"
                            " 4. Score multiplier of x5\n");
                    wprintw(vin, " You probably will not make it past 3 levels\n");
                    wprintw(vin, " Press any key to return. ");
                    wrefresh(vin);
                    getch_();
                    break;
            }
        }
    }
    werase(vin);
    cldisplay(vin);
    endwin();
}

int displaylauncher(long &seed)
{
    /*
     * This is a pretty simple function, just displays a menu allowing
     * the user to select what he/she wants to do with the game. Options
     * parsed in main function. Using ncurses and nwin we can display a
     * bunch of options and get rid of that annoying cout stuff we were
     * using back in engine < 1.9.2
     */
    
    signal(SIGSEGV, sighandle);
    
    char selection;
    int ret;
    initscr();
    refresh();
    noecho();
    WINDOW *vin;
    while (true)
    {
        vin = phyrrus9::nwin::wcreatewin(21, 65);
        setdisplay(vin, " Welcome  to  Super  Key  Seeker  3  ©  2012  phyrrus9");
        wprintw(vin, " This game has several modes to select, but if for you\n "
                    "want to play the older games, there is a downloader\n "
                    "in this menu, it requires internet to work. Thanks :)\n "
                    "Please select an option from the list below to start\n "
                    "1. Single player (infinite) game (OSX only)\n "
                    "2. Single player (infinite) game no sound\n "
					"s. Single player (story mode)\n"
                    "3. Miltiplayer (local) game\n "
                    "4. Multiplayer (online) game\n "
                    "5. Play KS4200\n "
                    "6. Play SKS4200\n "
                    "7. Enable fastboot\n "
                    "8. Disable fastboot\n "
                    "9. Exit\n "
                    "** You can pass a parameter to this game as a seed\n "
                    "*** You may also press S to set the seed from this menu\n "
                    "*** Press C to enter competition mode now.\n "
                    " >");
        wrefresh(vin);
        selection = getch_();
        phyrrus9::nwin::wcldisplay(vin);
		if (selection == 's')
		{
			env.single = true;
			selectdifficulty();
			WINDOW *w = phyrrus9::nwin::wcreatewin(1, 1);
			wclear(w);
            phyrrus9::nwin::wresizewindow(w, 6, 35);
            setdisplay(w, " Sound settings");
            wprintw(w, " Y. Play with sound\n");
            wprintw(w, " N. Play without sound\n");
            wprintw(w, " :");
            wrefresh(w);
			wclear(w);
			delwin(w);
            char sound = toupper(getch_());
            env.music = sound == 'Y' ? true : false;
			return 10;
		}
        if (selection == 'S')
        {
            WINDOW *w;
            w = phyrrus9::nwin::wcreatewin(5, 30);
            setdisplay(w, " Seed input dialog");
            wprintw(w, " Current seed: %d\n", seed);
            wprintw(w, " New: ");
            wrefresh(w);
            cin >> seed;
            phyrrus9::nwin::wcldisplay(w);
        }
        else if (selection == 'C')
        {
            WINDOW *w;
            w = phyrrus9::nwin::wcreatewin(4, 35);
            setdisplay(w, " Competition mode setup");
            wprintw(w, " Competition number: ");
            wrefresh(w);
            cin >> env.competition.number;
            wclear(w);
            setdisplay(w, " Competition mode setup");
            wprintw(w, " Competition password: ");
            wrefresh(w);
            cin >> env.competition.password;
            setdisplay(w, " Competition mode setup");
            wprintw(w, " Username: ");
            wrefresh(w);
            cin >> env.competition.username;
            wclear(w);
            phyrrus9::nwin::wresizewindow(w, 7, 35);
            wclear(w);
            setdisplay(w, " Competition settings");
            wprintw(w, " Number: %d\n", env.competition.number);
            wprintw(w, " Password: %s\n", env.competition.password);
            wprintw(w, " User: %s\n", env.competition.username);
            wprintw(w, " Press any key to start. ");
            wrefresh(w);
            getch_();
            
            env.competition_mode = true;
            env.developer_mode = false;
            env.cheats = false;
            env.multiplayer = false;
            multiplayer = false;
            
            wclear(w);
            phyrrus9::nwin::wresizewindow(w, 6, 35);
            setdisplay(w, " Sound settings");
            wprintw(w, " Y. Play with sound\n");
            wprintw(w, " N. Play without sound\n");
            wprintw(w, " :");
            wrefresh(w);
            char sound = toupper(getch_());
            ret = sound == 'Y' ? 1 : 2; // mode 1 = sound, 2 = no sound
            break;
        }
        else if (selection == 'D' && env.developer_mode)
        {
            game_initialized = true;
            WINDOW *w;
            w = phyrrus9::nwin::wcreatewin(4, 35);
            setdisplay(w, " Competition reader");
            wprintw(w, " filename: ");
            wrefresh(w);
            cin >> env.savefile;
            wclear(w);
            
            phyrrus9::nwin::wresizewindow(w, 3, 20);
            setdisplay(w, " Checking file...");
            wrefresh(w);
            restore();
            sleep(1);
            bool valid = true;
            if (env.cheats)
                valid = false;
            if (env.developer_mode)
                valid = false;
            if (env.multiplayer)
                valid = false;
            if (!env.competition_mode)
                valid = false;
            if (env.can_enable_developer_mode)
                valid = false;
            if (env.totalscore < COMPETITION_MIN)
                valid = false;
	    	for (int i = 0; i < env.modcount; i++)
	    	{
				if (env.modlist[i].enabled)
					valid = false;
	    	}
            for (int i = 0; i < 900; i++)
            {
                //any error checking for the map goes here
            }
            wclear(w);
            
            if (valid)
            {
                phyrrus9::nwin::wresizewindow(w, 11, 35);
                setdisplay(w, " File information");
                wprintw(w, " Score: %d\n", env.totalscore);
                wprintw(w, " Time: %d:%d\n", env.timer.minute, env.timer.second);
                wprintw(w, " Number: %d\n", env.competition.number);
                wprintw(w, " Password: %s\n", env.competition.password);
                wprintw(w, " Username: %s\n", env.competition.username);
				wprintw(w, " Time: %02d:%02d\n", env.timer.minute, env.timer.second);
                wprintw(w, " Press any key to return ");
				wborder(w, 0, 0, 0, 0, 0, 0, 0, 0);
                wrefresh(w);
                getch_();
            }
            else
            {
                phyrrus9::nwin::wresizewindow(w, 4, 25);
                setdisplay(w, " This file is invalid!");
                wprintw(w, " Press any key to return ");
                wrefresh(w);
                getch_();
            }
            
            cldisplay(w);
            
            ret = -1;
        }
        else if (selection == 'F')
        {
            initscr();
            refresh();
            noecho();
            uiwindow w;
            w.resize(4, 35);
            w.title("Hello World!");
            //colorifyv3(w, BLUE);
            w.print("This is a test!\n");
            //colorifyv3(w);
            w.refresh();
            getch_();
            w.empty();
            endwin();
        }
        else
        {
            ret = char_int(selection);
            break;
        }
    }
    endwin();
    return ret;
}

void devsettings(void)
{
    initscr();
    refresh();
    noecho();
    WINDOW *w;
    w = phyrrus9::nwin::wcreatewin(4, 50);
    setdisplay(w, " Developer setup");
    wprintw(w, "Press S to configure, any other key to continue ");
    wrefresh(w);
    char c = getch();
    if (c == 'S')
    {
        phyrrus9::nwin::wresizewindow(w, 9, 50);
        char done = 0;
        while (done == 0)
        {
            setdisplay(w, " Developer setup");
            wprintw(w, "Enable cheats? 0 (1/0) ");
            wrefresh(w);
            env.cheats = getch() - 48;
            wprintw(w, "%d\n", env.cheats);
            wrefresh(w);
            wprintw(w, "Disable fog? 0 (1/0) ");
            wrefresh(w);
            env.showmap = getch() - 48;
            wprintw(w, "%d\n", env.showmap);
            wrefresh(w);
            done = 1;
        }
    }
    werase(w);
    wclear(w);
    wrefresh(w);
    delwin(w);
}
