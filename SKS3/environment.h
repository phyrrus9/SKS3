/*
 * Super Key Seeker Version 3
 * Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 * This software is free, it may be customized, redistributed, blah blah blah...
 */
//#include "enumerations.h" //apparently this is all good if I leave it out...bad if not
#include <string.h>
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