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
 File: main.h
 Description: Function prototypes for all the garbage the main
 program uses. If you want to read the description look in main.cpp
 Authors: phyrrus9 <phyrrus9@gmail.com>
*****************************************************************/
#ifndef SKS3_engine_h
#include "engine/engine.h"
#endif
#include "engine/hiscore.h"
#include "sks4200/sks4200.h"
#include "ks4200/ks4200.h"
#include <signal.h>
#define _move moving = true
extern _environment env; //fixes issues with xcode compilations
//external functions to control the background music threads
extern void music_start(void);
extern void music_stop(void);
int main(int argc, const char * argv[]); //main function
void game(int argc, const char * argv[]); //the game itself
int displaylauncher(long &); //shows the main menu selection
void selectdifficulty(void); //select some environment options
void devsettings(void);