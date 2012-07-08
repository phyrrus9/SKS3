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
    t.player = character::N;
    //socket init
    strcpy(t.socket_message, "\251");
    //zombie globals
    t.min_zombie_does_damage_level = 5;
    t.zombies_do_damage = true;
}

void weapons_init(weapons::weaponlist &t)
{
    //{ 2, 4, 8, 16, 32, 64 }
    for (int i = 0, j = 2; i < 6; i++, j *= 2) //all powers of two
        t.strength[i] = j; //its all easier this way for adding say 128 weapons :P
}