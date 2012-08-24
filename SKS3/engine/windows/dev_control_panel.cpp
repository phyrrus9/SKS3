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
 File: windows/dev_control_panel.cpp
 Description: Code for the development control panel.
 Authors: phyrrus9 <phyrrus9@gmail.com>
 the GNU Project (ncurses)
 *****************************************************************/
#include "settings.h"
void developer_settings_window(void)
{
    /*
     * Developer control panel
     * This is what we will use to control
     * developer stuff that we make public
     * to help debug the program like thread
     * hooks, pointer references, and pauses
     */
    
    WINDOW *vin;
    initscr();
    refresh();
    noecho();
    int height = 12, width = 62;
    int starty = (LINES - height) / 2;	/* Calculating for a center placement */
	int startx = (COLS - width) / 2;	/* of the window		*/
    vin=newwin(height,width,starty,startx);
    wmove(vin,0,0);
    setdisplay(vin, " Developer settings");
    waddstr(vin, " Sorry, there is not any configurable controls here       \n"
                 " If you would like to learn about how you can develop for \n"
                 " the developers of this program, please visit the github  \n"
                 " page for SKS3 at https://github.com/phyrrus9/SKS3 and get\n"
                 " a copy of the source code (git clone) for development use\n"
                 " and when you are finished please email me (Ethan Laur) at\n"
                 " phyrrus9@gmail.com with your changes so I can credit you \n"
                 " and add your code to the main stream released as binaries\n"
                 " Thank you for your support, please press any key to exit \n");
    wrefresh(vin);
    getch();
    cldisplay(vin);
}