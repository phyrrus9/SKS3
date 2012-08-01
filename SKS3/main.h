/*
 * Super Key Seeker Version 3
 * Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 * This software is free, it may be customized, redistributed, blah blah blah...
 */
#ifndef SKS3_engine_h
#include "engine/engine.h"
#endif
#include "sks4200/sks4200.h"
#include "ks4200/ks4200.h"
#define _move moving = true
extern _environment env; //fixes issues with xcode compilations
//external functions to control the background music threads
extern void music_start(void);
extern void music_stop(void);
int main(int argc, const char * argv[]); //main function
void game(int argc, const char * argv[]); //the game itself
void displaylauncher(void); //shows the main menu selection