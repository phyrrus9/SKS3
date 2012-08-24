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
 File: windows/settings.cpp
 Description: This code contains the instructions for the settings
 windows used when the user presses the settings key. It will
 display a menu with various sub control panels and allow you to
 select one of them to control the sub settings. After this is
 complete, a flag variable will be set to ensure that the control
 panel will now save your settings structure to disk. Upon the
 initialization of the environment variable (where all settings
 are stored for use), the disk settings structure is read into the
 environment if it exists (by overwriting the default values).
 Authors: phyrrus9 <phyrrus9@gmail.com>
 the GNU Project (ncurses)
 *****************************************************************/
#include "settings.h"

void settings_window(void)
{
    /*
     * The main control panel function. This
     * is where the main control panel menu
     * is displayed so the user can select a
     * panel. Once a panel has been returned
     * the flag will be set and the struct
     * will be written to disk.
     */
    
    bool controlled = false;
    WINDOW *vin;
    initscr();
    refresh();
    noecho(); //no echo on getch
    int height = 10, width = 35;
    int starty = (LINES - height) / 2;	/* Calculating for a center placement */
	int startx = (COLS - width) / 2;	/* of the window		*/
    vin=newwin(height,width,starty,startx);
    wmove(vin, 0, 0);
    char ch;
    while (true)
    {
        setdisplay(vin, " Control panel");
        wprintw(vin, " Please select the correct panel\n "
                     " 1.) Key control panel          \n "
                     " 2.) Developer control panel    \n "
                     " 3.) Back to game               \n\n "
                     " * denotes a disabled panel    \n ");
        wrefresh(vin);
        ch = getch();
        cldisplay(vin);
        if (ch == '1')
        {
            key_settings_window();
            controlled = true;
        }
        if (ch == '2')
        {
            developer_settings_window();
        }
        if (ch == '3')
            break;
        if (controlled)
            break;
    }
}