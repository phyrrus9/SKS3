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
 File: environment_functions.h
 Description: Everything in here is commented, figure it all out
 for yourself I dont have time to rewrite my comment lines sorry.
 Authors: phyrrus9 <phyrrus9@gmail.com>
 *****************************************************************/
#include "engine.h"
#ifndef environment_functions_h
#define environment_functions_h
#include "Thread.h"
extern _environment env;
void environment_init(_environment &); //initialize an environment variable. don't know why you would ever need two of these, but it is here just in case (plus it takes away the need to ensure all the externs are set up all the way and prevents the accidental use of two or more environment variables)
void weapons_init(weapons::weaponlist &); //initializes all the weapons stuff, for now it only initializes the weaponlist (which only contains the strengths). This will (eventually) contain a whole more (and some math formula to figure this all out in a loop).
void game_timer_init(game_timer &); //initializes the game timer with double zeros.
void game_timer_increment(game_timer&); //adds one second
void settings_init(_settings &); //initialize the game settings
void competition_init(_competition &); //initialize competition stuff
void modifications_init(_modification_settings &t); //init the modifications struct
#endif