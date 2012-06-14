/*
 * Super Key Seeker Version 3
 * Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 * This software is free, it may be customized, redistributed, blah blah blah...
 */
#ifndef SKS3_engine_h
#include "engine.h"
#endif
#define _move moving = true
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
        
        if (env.levels_completed > 0) //level 2
            env.weapons[1] = true; //enable the throwing star
        if (env.levels_completed > 4) //level 5
            env.weapons[2] = true; //enable the sword
        if (env.levels_completed > 9) //level 10
            env.weapons[3] = true; //enable the gun
        if (env.levels_completed > 24) //level 25
            env.weapons[4] = true; //enable the canon
        
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
            if (turning)
                turn(t);
            else
                if (moving)
                    move(t);
                else
                    continue;
        }
    }
    return 0;
}
