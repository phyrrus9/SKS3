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
 File: windows/information_control_panel.cpp
 Description: Code to display some information about the developer
 control panel. This is not anything that can be configured.
 Authors: phyrrus9 <phyrrus9@gmail.com>
 the GNU Project (ncurses)
 *****************************************************************/
#include "settings.h"
void information_window(void)
{
    /*
     * Developer information window. Explains how
     * to use the developer mode with the game and
     * what it is useful for.
     */
    
    WINDOW *vin;
    initscr();
    refresh();
    noecho();
    int height = 18, width = 65;
    int starty = (LINES - height) / 2;	/* Calculating for a center placement */
	int startx = (COLS - width) / 2;	/* of the window		*/
    vin=newwin(height,width,starty,startx);
    wmove(vin,0,0);
    setdisplay(vin, "                  Developer information window ");
    wprintw(vin,    " The developer control panel is a very interesting place to go\n"
                    " about doing business with this game. There are a few options \n"
                    " that you can use to change how you interact with the game and\n"
                    " how the game interacts with you. In order to use the game in \n"
                    " ways it is not intended to be used by the general public. To \n"
                    " enable the developer mode (which also enables the developer  \n"
                    " control panel and removed the * around it), you must run the \n"
                    " game with developer-mode as the first parameter. This mode is\n"
                    " not enableable from within normal mode or during the game. It\n"
                    " holds the enabled effect when restored from a save but it not\n"
                    " if you restart the game in normal mode. If you rely on a seed\n"
                    " you can specify a seed value from the command line after the \n"
                    " developer mode argument. The developer control panel is risky\n"
                    " and not reccommended for all users. This panel will change by\n"
                    " demand. Press any key to return. "
            );
    wrefresh(vin);
    getch_();
    
    cldisplay(vin);
    delwin(vin);
    endwin();
}