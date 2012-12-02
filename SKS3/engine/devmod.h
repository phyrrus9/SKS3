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
 File: devmod.h
 Description: Function definition and type definitions for the mod
 system. Very minimal as of version 3.0b2
 Authors: phyrrus9 <phyrrus9@gmail.com>
 *****************************************************************/
#ifndef devmod
#define devmod

enum modtype { NOMOD, ENVMOD };

struct developermod
{
    char name[30];
    char filename[50];
    modtype type;
    bool enabled;
};
#endif


#ifndef __SKS3__devmod__
#define __SKS3__devmod__

#include <cstdio>
#include "engine.h"
#include "uinterface.h"
#include <iostream>

#define MODFILE_LOCATION "/usr/share/sks3/mods.conf"

void mod_init(void);
void readmods(developermod *modlist);
void enablemod(int modnum);

#endif /* defined(__SKS3__devmod__) */
