/*
 * Super Key Seeker Version 3
 * Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 * This software is free, it may be customized, redistributed, blah blah blah...
 */
//#include "enumerations.h" //apparently this is all good if I leave it out...bad if not
#include <string.h>
struct _environment
{
    char map[900], grid[900];
    char * view;
    bool showmap, single, cheats;
    bool weapons[6];
    int health, lives, score, position, moves, kills, kills_needed, levels_completed, attack,
    totalscore, selectedweapon;
    std::string savefile;
    color bgcolor, playercolor;
    character::player player;
    char socket_message[256];
};