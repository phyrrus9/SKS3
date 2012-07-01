/*
 * Super Key Seeker Version 3
 * Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 * This software is free, it may be customized, redistributed, blah blah blah...
 */
#ifndef SKS3_engine_h
#include "engine.h"
#endif
_environment env; //global var
int client_port, server_port, playernum;
char * hostname = new char[256];
void terminate(int param) //segmentation fault on clean exit (unalloc from restore bug tempfix)
{
    kill(getpid(), SIGTERM);
}
char getch_()
{
    char c;
    initscr();
    cbreak();
    c = getch();
    endwin();
    return c;
}
void colorify(void)
{
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

        if (c == RED)
            cout << "\33[31m";
        if (c == BLUE)
            cout << "\33[34m";
        if (c == GREEN)
            cout << "\33[32m";
        if (c == NORMAL)
            cout << "\33[0m";
}
void enginecmd(string c, string d)
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
    if (c == "gam->savefile")
        env.savefile = d;
    if (c == "env->foggy")
        env.showmap = atoi(d.c_str());
    if (c == "env->attack")
        env.attack = atoi(d.c_str());

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
        cout << "Press any key to continue..." << endl;
        getch_(); //char c = ...
    }
}