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
 File: uinterface.h
 Description: Code file for the uinterfaces, this is going to be
 used in the 3.1 engine (not publicly before it though I will work
 on the code in the background). This block will update as I do.
 Authors: phyrrus9 <phyrrus9@gmail.com>
 the GNU Project (ncurses)
 *****************************************************************/
#include "uinterface.h"

_uiwindow::_uiwindow()
{
    x = 0;
    y = 0;
    height = 0;
    width = 0;
    initialized = false;
    border = false;
}

void _uiwindow::setborder(bool _border)
{
    border = _border;
}

void _uiwindow::move(int _x, int _y)
{
    if (!initialized)
        return;
    delwin(w);
    x = _x;
    y = _y;
    w = newwin(height, width, x, y);
    wrefresh(w);
}

void _uiwindow::resize(int _h, int _w)
{
    height = _h;
    width = _w;
    if (!initialized)
    {
        w = newwin(height, width, x, y);
        wrefresh(w);
    }
    else
    {
        phyrrus9::nwin::wresizewindow(w, height, width);
    }
}

void _uiwindow::title(const char *title)
{
    char *str = new char[strlen(title) + 5];
    strcpy(str, " ");
    strcat(str, title);
    wclear(w);
    wprintw(w, "\n%s\n", str);
    //box(w, '|', 0);
    if (border)
        wborder(  w, 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  );
    //wborder(w, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(w);
}

void _uiwindow::print(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    wprintw(w, fmt, args);
    va_end(args);
}

void _uiwindow::refresh()
{
    wrefresh(w);
}

void _uiwindow::empty()
{
    wclear(w);
    wrefresh(w);
}