/*
 * Super Key Seeker Version 3
 * Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 * This software is free, it may be customized, redistributed, blah blah blah...
 */
#include "user.h"
extern _environment env; //global variable
extern bool game_initialized;
class display_thread : public tpool::Thread
{
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
    virtual void Entry(void)
    {
        while (true)
        {
            if (!env.music)
            {
                //system("killall afplay"); //stop the music, please (pun)
            }
            while (!env.music)
            {
                //no music is played
            }
            while (env.music)
            {
                if (env.music)
                    play_music("afplay /usr/share/sks3/1.mp3 -v 0.5 &");
                if (env.music)
                    sleep(289); //betrayal of fear
                if (env.music)
                    play_music("afplay /usr/share/sks3/2.mp3 -v 0.5 &");
                if (env.music)
                    sleep(173); //betrayal of fate
                if (env.music)
                    play_music("afplay /usr/share/sks3/3.mp3 -v 0.f &");
                if (env.music)
                    sleep(256); //guitar vs piano v1.2
            }
        }
    }
};
music_thread *backgroundmusic; //file global
void showhelp(void)
{
    clear();
    //env.music = true; //ensure it actually starts //nevermind....
    cout << "Super Key Seeker 3 - Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>" << endl
    << "This game is copyright to Ethan laur(phyrrus9) under modtech LLC" << endl
    << "Background Music (mac os x only) copyright 2006-2012, 2008-2012 Goukisan" << endl
    << "Sound effects are music found in the public domain and are mac os only" << endl
    << "To use:" << endl
    << "Run the game from the terminal or SSH." << endl
    << "Your player will show up as the following characters, and it is an arrow:" << endl
    << "^ - You are looking up              > - You are looking to the right" << endl
    << "v - You are looking down            < - You are looking to the left" << endl
    << "Your player will be the red character on the screen, you may move by pressing:" << endl
    << "w - Move Up                         i - Look Up" << endl
    << "a - Move Left                       j - Look Left" << endl
    << "s - Move Down                       k - Look Down" << endl
    << "d - Move Right                      l - Look Right" << endl
    << "No need to press enter, character icon will update automatically" << endl
    << "You do not need to run into a target to attack it, you may use the following:" << endl
    << "e - Attack target facing arrow" << endl
    << "E - Increment your attack points" << endl
    << "Weapons are available in the game and will be added to your view when earned" << endl
    << "The current selection will show up in red in the weapons selector." << endl
    << "Here is a list of weapons:" << endl
    << "D - Your fist (default)             x - Throwing star (level 2)" << endl
    << "| - Sword (level 5)                 © - Gun (level 10)" << endl
    << "{}- Canon (level 25)                ~ - Laser (level 50)" << endl
    << "To select a weapon, just use the keypad number of your choice" << endl
    << "Other commands used in the game are:" << endl
    << "S - Save game                       R - Restore game" << endl
    << "&S- Save to slot                    &R- Restore from slot      -- & denotes pressing alt(PC/linux) or option(osx)" << endl
    << "Q - Quit game                       N - New game" << endl
    << "p - Pause or unpause game           m - Start or stop music" << endl
    << "H - Show help" << endl
    << "Characters in the game are:" << endl
    << "~ - Neutral (empty)                 % - Large bug" << endl
    << "& - Small bug                       $ - Worm" << endl
    << "! - Vicious pitbull                 z - Zombie" << endl
    << "You can change the color of the text (if your terminal does not support it)" << endl
    << "To do so, type /colorify (or /env->pcolor) and then one of the following colors:" << endl
    << "red, blue, green, yellow, normal" << endl
    << "You can disable the fog by typing /env->foggy 0 and turn it on by using 1" << endl;
    if (game_initialized)
    {
        cout << "For a list of engine commands, press H again" << endl;
        cout << "Good luck! Press any other key to exit help.." << endl;
        char c = getch_(); //just got rid of char c = to fix the err below
        if (c == 'H')
        {
            enginecmd_display();
        }
    }
    else
    {
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
}
void display(void)
{
    weapons::weaponlist t;
    weapons_init(t);
    colorify(env.statuscolor);
    cout << setfill(' ') << left << setw(13) << VERSION_BUILD << setw(7) << "Health:" << setw(5) << env.health << setw(7) << "Lives:" << setw(4) << env.lives <<  setw(7) << "Kills:" << setw(3) << env.kills << setw(14) << "Kills needed:" << setw(5) << env.kills_needed << setw(20) << "Levels completed:" << setw(5) << env.levels_completed << "\n\r" << setw(13) << " " << setw(7) << "Attack:" << setw(3) << env.attack << setw(8) << "Weapon:" << setw(5) << (env.attack * (t.strength[env.selectedweapon])) << setw(7) << setprecision(6) << fixed << "Score:" << setw(7) << env.totalscore << setw(6) << "Time:" << right << setw(2) << setprecision(2) << setfill('0') << env.timer.minute << ":" << right << setw(2) << env.timer.second << setfill(' ') << left << setw(5) << " " << setw(9) << "Weapons:";
    showweapons();
    cout << endl;
    multidisplay();
    colorify();
    if (env.paused)
        cout << "Paused..." << endl;
}
void multidisplay(void)
{
    if (strcmp(env.socket_message, "\251") != 0)
        cout << "[player 2] " << env.socket_message << "\n\r";
}
void enginecmd_display(void)
{
    clear();
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
         << "<color> is filled by a color (red, green, blue, normal)           " << endl;
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
         << "/zom->min_damagelevel  <int>                When zombies attack (level)   " << endl
         << "/zom->damage           <bool>               If the zombies will attack you" << endl
         << "Data type <int> is any real whole number, <bool> is a 0 or a 1    " << endl
         << "NOTE: cheats are NOT available in multiplayer mode (sorry)        " << endl;
    cout << "Press any key to exit..." << endl;
    getch_();
}
void music_stop(void)
{
    backgroundmusic->Stop();
    kill_music("killall sleep; killall afplay"); //this will cause a jump in one second
    //env.timer.second--;
    env.timer.clock--;
}
void music_start(void)
{
    backgroundmusic->Run();
}
