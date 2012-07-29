/*
 * Super Key Seeker Version 3
 * Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 * This software is free, it may be customized, redistributed, blah blah blah...
 */
#include "environment_functions.h"
void environment_init(_environment &t)
{
    strcpy(t.map, "\0");
    strcpy(t.grid, "\0");
    t.showmap = true;
    t.single = false;
    t.cheats = false;
    t.refresh_screen = true;
    //weapons
    t.weapons[0] = true;
    for (int i = 1; i < 6; i++)
        t.weapons[i] = false;
    //integers
    t.health = 100;
    t.lives = 3;
    t.score = 0;
    t.position = 0;
    t.moves = 1;
    t.kills = 0;
    t.kills_needed = 0;
    t.levels_completed = 0;
    t.attack = 1;
    t.totalscore = 0;
    t.selectedweapon = 0;
    //savedata
    t.savefile = "save.dat";
    //character stuff
    t.bgcolor = NORMAL;
    t.playercolor = RED;
    t.statuscolor = NORMAL;
    t.player = character::N;
    //socket init
    strcpy(t.socket_message, "\251");
    //zombie globals
    t.min_zombie_does_damage_level = 5;
    t.zombies_do_damage = true;
    //game timer stuffs
    game_timer_init(t.timer);
}

void weapons_init(weapons::weaponlist &t)
{
    //{ 2, 4, 8, 16, 32, 64 }
    for (int i = 0, j = 2; i < 6; i++, j *= 2) //all powers of two
        t.strength[i] = j; //its all easier this way for adding say 128 weapons :P
}

class timer_thread : public tpool::Thread
{
    virtual void Entry(void)
    {
        while (true)
        {
            sleep(1);
            if (env.moves > 1)
            {
                //env.score -= env.timer.clock;
                game_timer_increment(env.timer);
                env.refresh_screen = true;
            }
            else 
            {
                env.timer.second = env.timer.minute = 0;
                //env.timer.clock /= 5;
            }
            env.totalscore = (((((env.score * (env.levels_completed * 2)) + (env.health / 3)) + env.kills) + env.lives) - (env.moves / 3) - ((env.timer.clock / 10) * env.levels_completed));
            //figured i would do this here
            if (env.totalscore < 0)
                env.totalscore = 0;
        }
    }
};

void game_timer_init(game_timer &t)
{
    t.second = t.minute = t.clock = 0;
    timer_thread *env_timer_thread = new timer_thread;
    env_timer_thread->Run();
}

void game_timer_increment(game_timer & t)
{
    t.second++;
    t.clock++;
    if (t.second >= 60)
    {
        t.minute++;
        t.second = t.second - 60;
    }
}