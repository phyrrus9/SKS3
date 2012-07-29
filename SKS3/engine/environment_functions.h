/*
 * Super Key Seeker Version 3
 * Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 * This software is free, it may be customized, redistributed, blah blah blah...
 */
#include "engine.h"
#include "Thread.h"
extern _environment env;
void environment_init(_environment &); //initialize an environment variable. don't know why you would ever need two of these, but it is here just in case (plus it takes away the need to ensure all the externs are set up all the way and prevents the accidental use of two or more environment variables)
void weapons_init(weapons::weaponlist &); //initializes all the weapons stuff, for now it only initializes the weaponlist (which only contains the strengths). This will (eventually) contain a whole more (and some math formula to figure this all out in a loop).
void game_timer_init(game_timer &); //initializes the game timer with double zeros.
void game_timer_increment(game_timer&); //adds one second