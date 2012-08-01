/*
 * Super Key Seeker Version 3
 * Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 * This software is free, it may be customized, redistributed, blah blah blah...
 */
#include "zombie.h"
bool zombiecheck(int p)
{
    /*
     * This function just checks to see if there
     * is a zombie at location p, if there is, it
     * returns that there is one and it is processed
     * in some other function.
     */
    if (env.map[p] == 'z')
        return true;
    return false;
}
void do_zombie_damage(void)
{
    /*
     * This function does the damage a zombie would
     * do to you if you were to
     * 1.) run on top of it
     * 2.) eat it without killing it
     * 3.) run away from it
     * 4.) run by it
     */
    if (env.zombies_do_damage)
        if (env.levels_completed >= env.min_zombie_does_damage_level)
            env.health = env.health - ((env.position / 3) - (env.levels_completed + env.attack));
}