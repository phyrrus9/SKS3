/*
 * Super Key Seeker Version 3
 * Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 * This software is free, it may be customized, redistributed, blah blah blah...
 */
#include "zombie.h"
bool zombiecheck(int p)
{
    if (env.map[p] == 'z')
        return true;
    return false;
}
void do_zombie_damage(void)
{
    if (env.zombies_do_damage)
        if (env.levels_completed >= env.min_zombie_does_damage_level)
            env.health = env.health - ((env.position / 3) - (env.levels_completed + env.attack));
}