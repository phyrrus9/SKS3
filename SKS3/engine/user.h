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
 File: user.h
 Description: Function prototypes for the user interface and the
 help, instructional, and settings dialogs for the user to use at
 will when keys are pressed and functions are triggered.
 Authors: phyrrus9 <phyrrus9@gmail.com>
 *****************************************************************/
#include "engine.h"
#ifndef user_h
#define user_h
void showhelp(void); //shows the help screen
void display(void); //shows the bar at top of screen
void display_v3(void); //ncurses version of display (enginev3)
void multidisplay(void); //for multiplayer
void enginecmd_display(void);
void about_zombie(void);
void about_tapeworm(void);
void copyright(void);
void music_stop(void); //stop the music
void music_start(void); //start the music
#endif