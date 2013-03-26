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
 File: user.cpp
 Description: This is the interface you see when you play the game
 and any other stuff is done here. The thread responsible for doing
 the screen refreshing automatically on demand is also written here
 in fact you are probably looking at the top of it as you read this
 This file also includes all of the help documents and settings
 interfaces for the program.
 Authors: phyrrus9 <phyrrus9@gmail.com>
 *****************************************************************/
#include "user.h"
extern _environment env; //global variable
extern bool game_initialized;
class display_thread : public tpool::Thread
{
    /*
     * Display everything on screen whenever the
     * program says that a refresh is necessary
     */
    virtual void Entry(void)
    {
        while (true)
        {
            if (env.refresh_screen)
            {
                if (env.allow_refresh)
                {
                    clear();
                    cout << "\r";
                    display();
                    cout << "\r";
                    showmap();
                    cout << "\r";
                    env.refresh_screen = false;
                }
            }
        }
    }
};
class music_thread : public tpool::Thread
{
    /*
     * Keep the background music going in a loop
     * unless the user turns it off, in that case
     * this thread will enter an infinite do nothing
     * loop until it is tuned back on
     */
    struct song
    {
        int length;
        char filename[256];
        char command[512];
    };
    virtual void Entry(void)
    {
        /*
         * In order to make this more customized
         * I decided to add music into a file
         * instead of having everything hardcoded
         * into this program. You will be able to
         * write a file with the number of songs
         * in the loop, and then the file for the
         * song number which will contain the length
         * and file name of the song. when placed in
         * the ./SKS3/music folder it will be copied
         * with the program when you run make install
         * but you will need to update the OSX install
         * package manually to incorporate your new files
         */
        bool failed = false; //so we dont just keep failing
        ifstream numberlist("/usr/share/sks3/songs.conf");
        if (!numberlist)
            failed = true;
        numberlist >> env.number_of_songs; //read it
        ifstream * songs = new ifstream[env.number_of_songs];
        song * songslist = new song[env.number_of_songs];
        int last_song = -1;
        env.current_song = -1;
        //if (env.number_of_songs == 0)
        {
            for (int i = 0; i < env.number_of_songs && !failed; i++)
            {
                string filename; //make an empty string
                filename += "/usr/share/sks3/";
                filename += static_cast<ostringstream*>( &(ostringstream() << i) )->str();
                filename += ".sconf";
                songs[i].open(filename.c_str());
                if (!songs[i])
                {
                    failed = true;
                    break;
                }
                songs[i] >> songslist[i].length >> songslist[i].filename;
                string song_command = "afplay -v 0.5 ";
                song_command += songslist[i].filename;
                song_command += " &";
                strcpy(songslist[i].command, song_command.c_str());
            }
        }
        while (true && !failed)
        {
            while (!env.music) { }
            while (env.music)
            {
                while (env.current_song < env.number_of_songs)
                {
                    while (env.current_song == last_song)
                        env.current_song = rand() % env.number_of_songs;
                    if (env.music)
                        play_music(songslist[env.current_song].command);
                    if (env.music)
                        sleep(songslist[env.current_song].length);
                    //env.current_song++;
                }
                env.current_song = 0; //restart the loop every time
            }
        }
    }
};
music_thread *backgroundmusic; //file global
void showhelp(void)
{
    /*
     * Display the help dialog on the screen, this will be
     * shown once at start (unless music is disabled), and
     * every time the user presses the 'H' key.
     */
    clear();
    env.allow_refresh = false;
    pause(); //so we don't run the timer
    //env.music = true; //ensure it actually starts //nevermind....
    cout << "Super Key Seeker 3 - Copyright © 2012-2013 phyrrus9 <phyrrus9@gmail.com>" << endl
    << "This game is copyright to Ethan laur(phyrrus9) under modtech LLC" << endl
    << "Background Music (mac os x only) copyright 2006-2012, 2008-2012 Goukisan" << endl
    << "Sound effects are music found in the public domain and are mac os only" << endl
    << "To use:" << endl
    << "Run the game from the terminal or SSH." << endl
    << "Your player will show up as the following characters, and it is an arrow:" << endl
    << "^ - You are looking up              > - You are looking to the right" << endl
    << "v - You are looking down            < - You are looking to the left" << endl
    << "Your player will be the red character on the screen, you may move by pressing:" << endl
    << env.settings.keys.w << " - Move Up                         " << env.settings.keys.i <<
                                                                  " - Look Up" << endl
    << env.settings.keys.a << " - Move Left                       " << env.settings.keys.j <<
                                                                  " - Look Left" << endl
    << env.settings.keys.s << " - Move Down                       " << env.settings.keys.k <<
                                                                  " - Look Down" << endl
    << env.settings.keys.d << " - Move Right                      " << env.settings.keys.l <<
                                                                  " - Look Right" << endl
    << "No need to press enter, character icon will update automatically" << endl
    << "You do not need to run into a target to attack it, you may use the following:" << endl
    << env.settings.keys.attack <<
    " - Attack target facing arrow" << endl
    << "E - Increment your attack points" << endl
    << "Weapons are available in the game and will be added to your view when earned" << endl
    << "The current selection will show up in red in the weapons selector." << endl
    << "Here is a list of weapons:" << endl
    << "D - Your fist (default)             x - Throwing star (level 2)" << endl
    << "| - Sword (level 5)                 © - Gun (level 10)" << endl
    << "{}- Canon (level 25)                ~ - Laser (level 50)" << endl
    << "√ - Stocking (level 75)             ø - Admin gun (level 100)" << endl
    << "To select a weapon, just use the keypad number of your choice" << endl
    << "Other commands used in the game are:" << endl
    << env.settings.keys.S << " - Save game                       " << env.settings.keys.R << "- Restore game" << endl
    << env.settings.keys.ss << "- Save to slot                     " << env.settings.keys.rs << "- Restore from slot" << endl
    << "o - View high scores                O - save your score" << endl
    << env.settings.keys.quit << " - Quit game                       N - New game" << endl
    << "p - Pause or unpause game           m - Start or stop music" << endl
    << "H - Show help                       n - Next song if music is on" << endl
    << env.settings.keys.settings << " - Control panel" << endl
    << "Characters in the game are:" << endl
    << "~ - Neutral (empty)                 % - Large bug" << endl
    << "& - Small bug                       $ - Worm" << endl
    << "! - Vicious pitbull                 z - Zombie" << endl
    << "g - Guard (very powerful)           b - Boss (dont trip on one)" << endl
    << "- - Tapeworm (stay away, they hurt)" << endl
    << "k - Key. Eat 500 of these for a massive score boost" << endl
    << "@ - Teleport ****** The teleport will instantly push you to the next level" << endl
    << "    If you were to eat this, you get a massive score boost." << endl;
    if (game_initialized)
    {
        cout << "Press these keys to diaplay other help dialogs " << endl;
        cout << "H - Engine commands                 Z - Zombies" << endl;
        cout << "C - Credits                         T - Tapeworms" << endl;
        cout << "Good luck! Press any other key to exit help.." << endl;
        char c = getch_(); //just got rid of char c = to fix the err below
        if (c == 'H')
            enginecmd_display();
        if (c == 'Z')
            about_zombie();
        if (c == 'T')
            about_tapeworm();
        if (c == 'C')
            copyright();
    }
    else
    {
        if (env.music)
            play_music("say Welcome to Super Key Seeker 3!");
        colorify(RED);
        cout << "This dialog will close in about 15 seconds." << endl
        << "To disable this, just add a file named .sksfastboot to this directory" << endl;
        ifstream sksfastboot(".sksfastboot");
        if (!sksfastboot)
        {
            sleep(15);
        }
        colorify();
        display_thread *backgroundrefresh = new display_thread;
        backgroundrefresh->Run();
        backgroundmusic = new music_thread;
        music_start();
    }
    //delete &c; //gets rid of unused var warning //nevermind: SKS3(19240) malloc: *** error for object 0x7fff655e69f7: pointer being freed was not allocated
    unpause();
    env.allow_refresh = true;
}
void display(void)
{
    /*
     * The HUD. The most important part of the game is what
     * the user can see and do. This tells him all that
     * information (except the multiplayer stuff)
     */
    weapons::weaponlist t;
    weapons_init(t);
    colorify(env.statuscolor);
    cout << setfill(' ') << left
        << setw(13) << VERSION_BUILD
        << setw(7) << "Health:";
        colorify(GREEN);
        if (env.health < 75)
        {
            colorify(BLUE);
        }
        if (env.health < 50)
        {
            colorify(RED);
        }
    printf("%5d ", env.health);
        colorify(env.statuscolor);
    printf("Lives: %-2d Kills: %3d/%-3d ", env.lives, env.kills, env.kills_needed);
    printf("Keys: %-4d Levels completed: %5d\n\r", env.keys, env.levels_completed);
    printf("%13c", ' '); //blank padding
    printf("Attack:%4d  Weapon: %-3d Score: ", env.attack, (env.attack * (t.strength[env.selectedweapon])));
        if (env.totalscore > 0)
        {
            colorify(RED);
        }
        if (env.totalscore > COMPETITION_MIN)
        {
            colorify(BLUE);
        }
        if (env.totalscore > COMPETITION_MAX)
        {
            colorify(GREEN);
        }
    printf("%-6d", env.totalscore);
        colorify(env.statuscolor);
    printf("Time: %02d:%02d Weapons: ", env.timer.minute, env.timer.second);
    showweapons();
    if (env.competition_mode)
    {
        if (env.totalscore < COMPETITION_MIN)
        {
            colorify(RED);
        }
        else
        {
            colorify(GREEN);
        }
        cout << " C";
        colorify(env.statuscolor);
    }
    cout << endl;
    multidisplay();
    colorify();
    if (env.paused)
        cout << "Paused..." << endl;
}
void displayv3(void)
{
    initscr();
    refresh();
    noecho();
    uiwindow w;
    w.resize(3, 70);
    w.refresh();
    weapons::weaponlist t;
    weapons_init(t);
    colorify(env.statuscolor);
    w.print("%13s Health:", VERSION_BUILD);
    colorifyv3(w, GREEN);
    if (env.health < 75)
    {
        colorifyv3(w, BLUE);
    }
    if (env.health < 50)
    {
        colorifyv3(w, RED);
    }
    w.print("%5d", env.health);
    colorifyv3(w, env.statuscolor);
    w.print("Lives: %4d Kills: %3d/%4d ", env.lives, env.kills, env.kills_needed);
    w.print("Keys: %5w ", env.keys);
    w.print("Levels completed: %5d\n\r ", env.levels_completed);
    w.print("Attack: %3d Weapon: %5d ", env.attack, (env.attack * (t.strength[env.selectedweapon])));
    w.print("Score: ");
    if (env.totalscore > 0)
    {
        colorifyv3(w, RED);
    }
    if (env.totalscore > COMPETITION_MIN)
    {
        colorifyv3(w, BLUE);
    }
    if (env.totalscore > COMPETITION_MAX)
    {
        colorifyv3(w, GREEN);
    }
    w.print("%8d ", env.totalscore);
    colorifyv3(w, env.statuscolor);
    w.print("Time: %02d:%02d ", env.timer.minute, env.timer.second);
    w.print("Weapons: ");
    showweaponsv3(w);
    if (env.competition_mode)
    {
        if (env.totalscore < COMPETITION_MIN)
        {
            colorifyv3(w, RED);
        }
        else
        {
            colorifyv3(w, GREEN);
        }
        w.print(" C");
        colorifyv3(w, env.statuscolor);
    }
    w.print("\n");
    //multidisplay();
    colorifyv3(w);
    if (env.paused)
        w.print("Paused...\n");
    endwin();
}

void multidisplay(void)
{
    /*
     * The "multiplayer stuff" from above is
     * shown using this function on a new line right
     * below the first HUD
     */
    if (!env.multiplayer)
        return;
    cout << '\r'; //return to the beginning now.... please
    env.socket_message[0] = ' '; //so the P wont show up
    if (strcmp(env.socket_message, "\251") != 0)
        cout << "[player 2] " << env.socket_message << "\n\r";
}
void enginecmd_display(void)
{
    /*
     * This is the second help screen that
     * shows all of the cheats and engine
     * commands that can be used with the '/'
     * key. Some of them require cheats to be
     * turned on. Parsed in the engine.cpp file
     * inside the enginecmd function
     */
    clear();
    env.allow_refresh = false;
    cout << "Engine commands are accessed by pressing the '/' key which will display a >"
         << " at the bottom of the screen" << endl
    << "Commands are as shown below." << endl;
    colorify(RED);
    cout << "Useful commands:" << endl;
    colorify();
    cout << "/colorify              <color>              Changes the foreground color  " << endl
         << "/env->pcolor           <color>              Changes your player icon color" << endl
         << "/gam                   [option]                                           " << endl
         << "   save                                     Saves the game (not slotsave) " << endl
         << "   restore                                  Restores the game (not slot)  " << endl
         << "/get                   [option]                                           " << endl
         << "   env->health                              Displays the current health   " << endl
         << "   env->lives                               Displays the current lives    " << endl
         << "   env->score                               Displays the current score    " << endl
         << "   env->position                            Displays the current position " << endl
         << "   env->moves                               Displays the current move #   " << endl
         << "   env->kills                               Displays the current kills    " << endl
         << "   env->kills_needed                        Displays the kills needed     " << endl
         << "   env->lc                                  Displays the levels completed " << endl
         << "   env->size                                Displays the savefile size    " << endl
         << "   env->cheats                              Displays cheats on or off     " << endl
         << "   zom->min_damagelevel                     Displays when zombies attack  " << endl
         << "   zom->damage                              Weather they attack or not    " << endl
         << "   zom->active                              Display # of active zombies   " << endl
         << "   env->tapeworms                           Display # of infections       " << endl
         << "/zombie                 <int>               Create a zombie at location   " << endl
         << "<color> is filled by a color (red, green, blue, normal)                   " << endl;
    colorify(RED);
    cout << "Cheat commands:" << endl;
    colorify();
    cout << "/env->cheats           <bool>               Enable or disable cheating    " << endl
         << "/env->health           <int>                Change the health value       " << endl
         << "/env->lives            <int>                Change the number of lives    " << endl
         << "/env->score            <int>                Change your base score        " << endl
         << "/env->position         <int>                Change your position          " << endl
         << "/env->moves            <int>                Change the number of moves    " << endl
         << "/env->kills            <int>                Change the number of kills    " << endl
         << "/env->lc               <int>                Change the levels completed   " << endl
         << "/env->foggy            <bool>               Enable or disable fog         " << endl
         << "/env->attack           <int>                Change your attack value      " << endl
         << "/env->keys             <int>                Change your number of keys    " << endl
         << "/zom->min_damagelevel  <int>                When zombies attack (level)   " << endl
         << "/zom->damage           <bool>               If the zombies will attack you" << endl
         << "Data type <int> is any real whole number, <bool> is a 0 or a 1    " << endl
         << "NOTE: cheats are NOT available in multiplayer mode (sorry)        " << endl;
    cout << "Press any key to exit..." << endl;
    getch_();
    env.allow_refresh = true;
}
void about_zombie(void)
{
    /*
     * Function to show all the juicy details about
     * the zombie AI system and what it does.
     */
    env.allow_refresh = false;
    clear();
    cout << "From the dawn of man, zombies have been a threat to survival of all creatures" << endl
         << "because since man is the most dominant creature on Earth, it would only make " << endl
         << "sense that a creature created by an ill human that had characteristics much  " << endl
         << "like savages without any mercy that they would be dominant over not only the " << endl
         << "humans but also the other creatures on the planet. In Super Key Seeker 3, I  " << endl
         << "decided it might be a good idea to add some of their vicious rampagingness to" << endl
         << "enhance your gameplay experience. Zombies can deal a lot of damage and they  " << endl
         << "should not be taken lightly. Not all zombies are like the rest on the other  " << endl
         << "hand. Some zombies are mobile, and some are not which makes your job a lot   " << endl
         << "more difficult as the player of this game.                                   " << endl
         << "With the AI system, only twenty five percent of the total zombies on the map " << endl
         << "will be active (able to move around) and therefore your experience wont be as" << endl
         << "laggy as it would be if I had 250 threads running again instead of 20 at the " << endl
         << "maximum. Zombies will move once every two seconds using the clock as an AI   " << endl
         << "base and will only move in blank squares or on you (which will hurt).        " << endl
         << "Thank you for reading my brief explanation of the zombies in this game       " << endl
         << endl
         << "Press any key to exit this dialog..." << endl;
    getch_();
    env.allow_refresh = true;
}
void about_tapeworm(void)
{
    /*
     * Function that describes how the tapeworm system works
     */
    env.allow_refresh = false;
    clear();
    cout << "Tapeworms have always been a problem when traveling, so they will be a problem" << endl
         << "in this game as well. Tapeworms can be identified by a - on the map, which was" << endl
         << "done intentionally to make it harder to accidently walk on one. Tapeworms will" << endl
         << "take a bite out of you once every minute for each tapeworm. The only way to   " << endl
         << "get rid of the worms is to find a life pack (+) and eat it. This will get rid " << endl
         << "exactly one tapeworm from your system. To check if you have any infections you" << endl
         << "can run the engine command /get env->tapeworms and it will tell you. The best " << endl
         << "method of prevention is to just not do it (yes, the sex talk from high school)" << endl
         << "they have a strength multiplier of 0, so you can attack them, but I would just" << endl
         << "simply stay away from them. There is no enabled AI yet, but there may be one  " << endl
         << "later on in the future.                                                       " << endl
         << endl
         << "Press any key to exit this dialog..." << endl;
    getch_();
    env.allow_refresh = true;
}
void copyright(void)
{
    /*
     * This just shows the credits,
     * pretty self explanitory and if it
     * isnt press 'H' then 'C' while in
     * game and you will find out.
     */
    env.allow_refresh = false;
    clear();
    cout << "This game would not be possible without the help of a few great people and " << endl
         << "organizations. The ammount of code it would take to completely write this  " << endl
         << "game by myself would have taken me a lot longer than the year it took me to" << endl
         << "write the first release version of this game. I would like to thank all of " << endl
         << "the people for their hard work on the libraries and code this game uses.   " << endl
         << "Firstly, the game author: I, Ethan Laur, wrote most of the code this game  " << endl
         << "uses for free, and on my own time with almost no help and mainly my ideas. " << endl
         << "I did it and then distributed the source code openly to the public so that " << endl
         << "you might be able to see what it takes to write even a simple game like so " << endl
         << "and that it might inspire you to learn new things and gain more experience " << endl
         << "as you go along programming (if you are a programmer). So, without further " << endl
         << "distraction, I would like to say that this code is mostly copyright © 2012 " << endl
         << "Ethan Laur (phyrrus9) <phyrrus9@gmail.com> and is open source, meaning that" << endl
         << "at any time you may visit http://github.com/phyrrus9/SKS3/ and browse the  " << endl
         << "source code and do what you please, please note the lisence block at the   " << endl
         << "top of every file as it will let you know what you can and cannot do with  " << endl
         << "the source code I am providing you with.                                   " << endl
         << "Next, I would like to thank the guy who gave me the original idea back in  " << endl
         << "2011 with Key Seeker 4200: Dereck Wonnacott. He helped make this game into " << endl
         << "what it is now and I want him to have some credit for it.                  " << endl
         << "Here comes the big one, back when I wrote the first game, I was using some " << endl
         << "simple cin or getch functions for movement and it got pretty painful after " << endl
         << "the workout of pressing 'w' and then enter every time I wanted to move up  " << endl
         << "so after a little bit of research I found that the GNU Project has a code  " << endl
         << "library that I could use to getch() without the need of pressing enter like" << endl
         << "in a regular video game. So for their hard work on that extensive library I" << endl
         << "would like to say THANK YOU, because the little snippet of code getch_()   " << endl
         << "in the engine is used more times than anything else and it wouldnt be the  " << endl
         << "great game it is without their hard work and dedication, so I would like to" << endl
         << "say that part of this code is copyright to the GNU Project for the ncurses " << endl
         << "library that we all love.                                                  " << endl
         << "Lastly, I must thank the company that helped me get it all put together and" << endl
         << "release my code to the public, MOD Technologies LLC <http://modtech.co> has" << endl
         << "made my work so much easier when it is time to release because they help me" << endl
         << "cover server cost as well as feed me advice and developers. So I would like" << endl
         << "to thank my company, MOD Technologies LLC for all the help Jerrick has been" << endl
         << "providing me with. This game is also copyright © 2012 MOD Technologies LLC " << endl
         << endl
        << "Press any key to continue..." << endl;
    getch_();
    env.allow_refresh = true;
}
void music_stop(void)
{
    /*
     * This will stop the music thread from
     * starting another song. Then it will kill
     * all of the running processes playing music
     */
    backgroundmusic->Stop();
    if (env.music)
        kill_music("killall sleep>/tmp/null-log; killall afplay>/tmp/null-log"); //this will cause a jump in one second
    env.music = false;
    //env.timer.second--;
    env.timer.clock--;
}
void music_start(void)
{
    /*
     * Re-start the music thread. Simple and fast
     */
    backgroundmusic->Run();
}
