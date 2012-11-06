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
 File: windows/windows.cpp
 Description: Code for managing windows. The engine for all of the
 windows used in this game.
 Authors: phyrrus9 <phyrrus9@gmail.com>
 *****************************************************************/
#include "windows.h"
void setdisplay(WINDOW * w, const char * title)
{
    /*
     * Function to write title to a window.
     * This is an optimization and really
     * shouldnt be changed.
     */
    wclear(w);
    wprintw(w, "\n%s\n", title);
    //box(w, '|', 0);
    wborder(  w, 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  );
    //wborder(w, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(w);
}

void cldisplay(WINDOW * w)
{
    /*
     * Function to clear out the border and
     * text in a window so we can use that
     * part of the screen for something else
     */
    wborder(w, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wclear(w);
    wrefresh(w);
    refresh();
}

char wpopuperror(const char * title, const char * text, int height, int width)
{
    WINDOW *vin;
    initscr();
    refresh();
    noecho(); //no echo on getch
    height = height + 3; //3 lines for title bar and such
    width = width + 4; //for the padding
    int starty = (LINES - height) / 2;	/* Calculating for a center placement */
	int startx = (COLS - width) / 2;	/* of the window		*/
    vin=newwin(height,width,starty,startx);
    setdisplay(vin, title);
    wprintw(vin, text);
    wrefresh(vin);
    char c = getch_();
    wclear(vin);
    werase(vin);
    cldisplay(vin);
    endwin();
    return c;
}