/*****************************************************************
 Super Key Seeker Version 3
 Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 This software is free, it may be customized, redistributed
 or used in any way that suits your needs. This software is
 open source, meaning that it MUST be distributed along with
 its source code or have provisions to recieve the source code
 if desired. This program, though it is free and open source
 is still copyright © the following names and companies:
 Ethan Laur (phyrrus9) <phyrrus9@gmail.com> 2012
 MOD Technologies LLC <http:modtech.co> 2012
 This program source code MUST be distributed with this comment
 block intact as a reference to users who would actually like
 to follow the rules. Please do not be a jerk and take credit
 for a program you did not write. This code for the most part
 was written by the following people and companies:
 Ethan Laur (phyrrus9) <phyrrus9@gmail.com>
 Dereck Wonnacott <dereck@gmail.com>
 GNU Project (for ncurses which we all so dearly love)
 All third party lisencing by the above authors is transmitted
 with the source code of this program to its new author, who
 may add his or her name to this block for the works they did
 It is greatly appreciated if any work you do on the program
 is reported back to the original authors (copyright section)
 so that we can incorporate your features into the game as a
 public release. We thank you for reading this file.
 If you want to know how many lines of code are in this project,
 you can just cd into the source directory and run the following
 find . -type f -print0 | xargs -0 cat | wc -l
 =================================================================
 File: environment.h
 Description: General definitions for the main RAM of the game.
 This is probably the most important header file in the code as it
 defines all of our global data which hopefully in SKS4 I will 
 change this so it is all private data and cant be corrupted as
 easily as it can right now.
 Authors: phyrrus9 <phyrrus9@gmail.com>
 *****************************************************************/
#include "engine.h"
#ifndef environment_h
#define environment_h
#include "hiscore.h"
#include "devmod.h"
struct game_timer
{
    int second, minute, clock;
};

struct _keys
{
    char attack, pause, quit, engine;
    char w, a, s, d;
    char i, j, k, l;
    char S, R;
    char ss, rs;
    char settings;
};

struct _zombie
{
    int zombie_active;
};

struct _settings
{
    _keys keys;
    _zombie zombie;
};

struct _competition
{
    int number;
    char username[30];
    char password[30];
};

struct _modification_settings
{
    char game_mode[30];
};

struct _environment
{
    char version[25];
    bool paused, music, socket_paused, multiplayer, time_up;
    char map[900], grid[900];
    char * view;
    bool showmap, single, cheats, zombies_do_damage, refresh_screen, allow_refresh;
    bool weapons[weapons::num_of_weapons];
    int health, lives, score, position, moves, kills, kills_needed, total_enemies, levels_completed, attack,
    totalscore, selectedweapon, min_zombie_does_damage_level, keys, number_of_songs, current_song, zombies, score_multiplier;
    std::string savefile;
    color bgcolor, playercolor, statuscolor;
    character::player player;
    character::difficulty difficulty;
    char socket_message[256];
    game_timer timer;
    hiscore::score hiscorelist[hiscore::num_scores]; //all x high scores
    _settings settings;
    //new as of engine v3
    bool developer_mode, can_enable_developer_mode;
    bool competition_mode;
    _competition competition;
    bool allow_autosave;
    int modcount;
    developermod modlist[10];
    _modification_settings modification_settings;
    int tapeworm_count;
    char status_message[90]; //displayed underneath the map for 5 seconds
};
#endif