/*
 * Super Key Seeker Version 3
 * Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 * This software is free, it may be customized, redistributed, blah blah blah...
 */
#ifndef SKS3_engine_h
#include "engine.h"
#endif
extern _environment env; //fixes issues with xcode compilations
int main(int argc, const char * argv[])
{
    bool single = false;
    if (argc > 1)
        single = true;
    srand(time(0));
    if (!single)
        populate();
    else
    {
        ifstream f("1.map");
        //i have no idea what i'm doing with this
        //so i will just stop here....continue it 
        //if you feel like it....
    }
    bool run = true;
    while (run)
    {
        if (!env.showmap)
            env.view = (char *)&env.map;
        else
            env.view = (char *)&env.grid;
        clear();
        if (env.kills >= env.kills_needed)
        {
            env.levels_completed++;
            env.position = 0;
            env.score += env.kills;
            populate();
            continue;
        }
        display();
        if (env.health <= 0)
        {
            if (env.lives <= 0)
            {
                cout << "You are dead..." << endl;
                run = false;
            }
            else
            {
                env.lives -= 1;
                env.health = 100;
            }
        }
        if (run)
        {
            showmap();
            char a = getch_();
            direction t;
            if (a == 'w')
                t = N;
            if (a == 'a')
                t = E;
            if (a == 's')
                t = S;
            if (a == 'd')
                t = W;
            if (a == 'S')
                t = SAV;
            if (a == 'R')
                t = RES;
            if (a == 'Q')
                t = QUI;
            if (a == 'H')
                t = HLP;
            if (a == 'N')
                execl(argv[0], argv[0]);
            if (a == '/')
            {
                cout << ">";
                string command1, command2;
                cin >> command1 >> command2;
                enginecmd(command1, command2);
                t = NIL;
            }
            move(t);
        }
    }
    return 0;
}
