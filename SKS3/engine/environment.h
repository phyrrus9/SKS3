/*
 * Super Key Seeker Version 3
 * Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 * This software is free, it may be customized, redistributed, blah blah blah...
 */
//#include "enumerations.h" //apparently this is all good if I leave it out...bad if not
#include <string.h>
struct game_timer
{
    int second, minute, clock;
};

struct _environment
{
    char map[900], grid[900];
    char * view;
    bool showmap, single, cheats, zombies_do_damage, refresh_screen;
    bool weapons[6];
    int health, lives, score, position, moves, kills, kills_needed, levels_completed, attack,
    totalscore, selectedweapon, min_zombie_does_damage_level;
    std::string savefile;
    color bgcolor, playercolor, statuscolor;
    character::player player;
    char socket_message[256];
    game_timer timer;
};