/*
 * Super Key Seeker Version 3
 * Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 * This software is free, it may be customized, redistributed, blah blah blah...
 */
#include "environment_functions.h"
/*
 struct _environment
 {
 char map[900] = "\0", grid[900] = "/0";
 char * view;
 bool showmap = true, single = false;
 bool weapons[6] = { true, false, false, false, false, false };
 int health = 100, lives = 3, score = 30, position = 0, moves = 1, kills = 0, kills_needed = 0,
 levels_completed = 0, attack = 0, totalscore = 0, selectedweapon = 0;
 std::string savefile = "save.dat";
 color bgcolor = NORMAL, playercolor = RED;
 character::player player = character::N;
 char socket_message[256] = "\251";
 };
*/
void environment_init(void)
{
    strcpy(env.map, "\0");
    strcpy(env.grid, "\0");
    env.showmap = true;
    env.single = false;
    env.cheats = false;
    //weapons
    env.weapons[0] = true;
    for (int i = 1; i < 6; i++)
        env.weapons[i] = false;
    //integers
    env.health = 100;
    env.lives = 3;
    env.score = 0;
    env.position = 0;
    env.moves = 1;
    env.kills = 0;
    env.kills_needed = 0;
    env.levels_completed = 0;
    env.attack = 1;
    env.totalscore = 0;
    env.selectedweapon = 0;
    //savedata
    env.savefile = "save.dat";
    //character stuff
    env.bgcolor = NORMAL;
    env.playercolor = RED;
    env.player = character::N;
    //socket init
    strcpy(env.socket_message, "\251");
}

void weapons_init(weapons::weaponlist t)
{
    //{ 2, 4, 8, 16, 32, 64 }
    t.strength[0] = 2;
    t.strength[1] = 4;
    t.strength[2] = 8;
    t.strength[3] = 16;
    t.strength[4] = 32;
    t.strength[5] = 64;
}