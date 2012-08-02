/*
 * Super Key Seeker Version 3
 * Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 * This software is free, it may be customized, redistributed, blah blah blah...
 */
#include "environment_functions.h"
void environment_init(_environment &t)
{
    /*
     * This function just sets up the initial environment
     * variables in their default values. It needed to be
     * a function instead of static initializations because
     * it would not compile for any system other than mac os x
     * that way, and even then it threw a few hundred warnings.
     */
    t.paused = false;
    t.music = true;
    t.socket_paused = false;
    strcpy(t.map, "\0");
    strcpy(t.grid, "\0");
    t.showmap = true;
    t.single = false;
    t.cheats = false;
    t.refresh_screen = true;
    t.allow_refresh = true;
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
    t.total_enemies = 0;
    t.levels_completed = 0;
    t.attack = 1;
    t.totalscore = 0;
    t.selectedweapon = 0;
    t.keys = 0;
    //savedata
    t.savefile = "save.dat";
    //character stuff
    t.bgcolor = NORMAL;
    t.playercolor = RED;
    t.statuscolor = NORMAL;
    t.player = character::N;
    t.difficulty = character::NORMAL; //set it this for now
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
    /*
     * This just initializes the strength array for weapons
     * its here because it cant be initialized in a header file
     */
    //{ 2, 4, 8, 16, 32, 64 }
    for (int i = 0, j = 2; i < 6; i++, j *= 2) //all powers of two
        t.strength[i] = j; //its all easier this way for adding say 128 weapons :P
}

class timer_thread : public tpool::Thread
{
    /*
     * This thread runs CONSTANTLY in the background, NO exceptions
     * all it does is count, literally. This is a timer, we use it to
     * track how many points to take off a user's score every ten seconds
     */
    virtual void Entry(void)
    {
        int count = 0;
        while (true)
        {
            sleep(1);
            if (env.moves > 1)
            {
                if (!env.paused)
                {
                    //env.score -= env.timer.clock;
                    game_timer_increment(env.timer);
                    env.refresh_screen = true;
                }
            }
            else 
            {
                env.timer.second = env.timer.minute = 0;
                //env.timer.clock /= 5;
            }
            env.totalscore = (((((env.score * (env.levels_completed * 2)) + (env.health / 3)) + env.kills) + env.lives) - (env.moves / 30) - ((env.timer.clock / 10) * env.levels_completed)) + (env.keys * 2);
            //figured i would do this here
            if (env.totalscore < 0)
                env.totalscore = 0;
            count++;
            if (count == 2)
            {
                env.refresh_screen = true;
                count = 0;
            }
        }
    }
};

void game_timer_init(game_timer &t)
{
    /*
     * Initialize the game timer to 00:00/0
     */
    t.second = t.minute = t.clock = 0;
    timer_thread *env_timer_thread = new timer_thread;
    env_timer_thread->Run();
}

void game_timer_increment(game_timer & t)
{
    /*
     * Increment by 00:01/1
     * if the seconds is more than xx:59/x, add 1 to the minutes
     */
    t.second++;
    t.clock++;
    if (t.second >= 60)
    {
        t.minute++;
        t.second = t.second - 60;
    }
}