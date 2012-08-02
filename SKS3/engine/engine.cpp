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
 *****************************************************************/
#ifndef SKS3_engine_h
#include "engine.h"
#endif
_environment env; //global var
int client_port, server_port, playernum;
char * hostname = new char[256];
void terminate(int param) //segmentation fault on clean exit (unalloc from restore bug tempfix)
{
    /*
     * Sometimes, after a save this will cause a sigsegv on closing the game
     * this is just here to catch it, and sigterm it so it wont throw
     * an error to the os and clutter your screen with crap
     */
    kill(getpid(), SIGTERM);
}
char getch_()
{
    /*
     * Get a single character using the ncurses functions
     * so that you no longer need to press enter (like in
     * the original version of sks4200). This function being
     * here just makes it a lot easier to grab a character
     * instead of pasting this code everywhere we needed it
     */
    char c;
    initscr();
    cbreak();
    c = getch();
    endwin();
    return c;
}
void colorify(void)
{
    /*
     * Not to be confused with colorify(color),
     * this changes the screen color to whatever
     * color is the bgcolor set with the /colorify
     * engine command
     */
    color c = env.bgcolor;
    if (c == RED)
        cout << "\33[31m";
    if (c == BLUE)
        cout << "\33[34m";
    if (c == GREEN)
        cout << "\33[32m";
    if (c == NORMAL)
        cout << "\33[0m";
}
void colorify(color c)
{
    /*
     * This sets the screen to a specific color
     * useful in threading or whenever you want
     * to change the color of a piece of text.
     * it used to be that in order to do this we
     * would just add the code to the actual object.
     * in SKS3 I decided to save memory and stop using
     * a 3D string array for maps and use a 2D character
     * array (a 1D string) instead. So each object takes
     * 1 byte of RAM instead of 8.
     */
    if (c == RED)
        cout << "\33[31m";
    if (c == BLUE)
        cout << "\33[34m";
    if (c == GREEN)
        cout << "\33[32m";
    if (c == NORMAL)
        cout << "\33[0m";
    if (c == BORDER)
        cout << "\33[32m";
}
void enginecmd(string c, string d)
{
    /*
     * Called when the user presses '/', this just
     * parses the input and performes the output
     * which could be useful commands like save
     * or not useful commands like cheating your
     * score or something stupid like that. It is
     * also useful for engineering savedata for
     * testing functions at say level 51.
     */
    if (c == "env->cheats")
    {
        extern bool multiplayer; //in main.cpp
        if (!multiplayer)
        {
            env.cheats = atoi(d.c_str());
        }
    }
    if (env.cheats)
    {
        if (c == "env->health")
            env.health = atoi(d.c_str());
        if (c == "env->lives")
            env.lives = atoi(d.c_str());
        if (c == "env->score")
            env.score = atoi(d.c_str());
        if (c == "env->position")
            env.position = atoi(d.c_str());
        if (c == "env->moves")
            env.moves = atoi(d.c_str());
        if (c == "env->kills")
            env.kills = atoi(d.c_str());
        if (c == "env->kills_needed")
            env.kills_needed = atoi(d.c_str());
        if (c == "env->lc")
            env.levels_completed = atoi(d.c_str());
        if (c == "env->keys")
            env.keys = atoi(d.c_str());
        if (c == "gam->savefile")
            env.savefile = d;
        if (c == "env->foggy")
            env.showmap = atoi(d.c_str());
        if (c == "env->attack")
            env.attack = atoi(d.c_str());
        if (c == "zom->min_damagelevel")
            env.min_zombie_does_damage_level = atoi(d.c_str());
        if (c == "zom->damage")
            env.zombies_do_damage = atoi(d.c_str());
    }
    if (c == "colorify")
    {
        if (d == "red")
            env.bgcolor = RED;
        if (d == "green")
            env.bgcolor = GREEN;
        if (d == "blue")
            env.bgcolor = BLUE;
        if (d == "normal")
            env.bgcolor = NORMAL;
        move(NIL);
    }
    if (c == "env->pcolor")
    {
        if (d == "red")
            env.playercolor = RED;
        if (d == "green")
            env.playercolor = GREEN;
        if (d == "blue")
            env.playercolor = BLUE;
        if (d == "normal")
            env.playercolor = RED;
    }
    if (c == "gam")
    {
        if (d == "save")
            save();
        if (d == "restore")
            restore();
    }
    if (c == "ssav")
    {
        //more here later
    }
    if (c == "sres")
    {
        //more here later
    }
    if (c == "get")
    {
        if (d == "env->health")
            cout << env.health << endl;
        if (d == "env->lives")
            cout << env.lives << endl;
        if (d == "env->score")
            cout << env.score << endl;
        if (d == "env->position")
            cout << env.position << endl;
        if (d == "env->moves")
            cout << env.moves << endl;
        if (d == "env->kills")
            cout << env.kills << endl;
        if (d == "env->kills_needed")
            cout << env.kills_needed << endl;
        if (d == "env->lc")
            cout << env.levels_completed << endl;
        if (d == "gam->savefile")
            cout << env.savefile << endl;
        if (d == "env->size")
            cout << sizeof(_environment) << endl;
        if (d == "env->attack")
            cout << env.attack << endl;
        if (d == "env->cheats")
            cout << env.cheats << endl;
        if (d == "zom->min_damagelevel")
            cout << env.min_zombie_does_damage_level << endl;
        if (d == "zom->damage")
            cout << env.zombies_do_damage << endl;
        cout << "Press any key to continue..." << endl;
        getch_(); //char c = ...
    }
}