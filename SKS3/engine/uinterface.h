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
 Description: Header file for the uiwindow class (and possibly more
 in the future). This will not be implemented until engine version
 3.1 when we attempt to replace cout entirely with windows. This
 class will make it a lot easier for us to manage windows, since it
 does it all for us. I will get around to commenting this all when
 I get a chance (right around the time of release for 3.1)
 Authors: phyrrus9 <phyrrus9@gmail.com>
 the GNU Project (ncurses)
 *****************************************************************/
#ifndef __SKS3__uinterface__
#define __SKS3__uinterface__
#include "engine.h"
#include "nwin/nwin.h"

typedef class _uiwindow
{
private:
    WINDOW *w;
    int x;
    int y;
    int height;
    int width;
    bool initialized;
    bool border;
public:
    _uiwindow();
    void setborder(bool _border);
    void move(int _x, int _y);
    void resize(int _h, int _w);
    void title(const char *title);
    void print(const char *fmt, ...);
    void refresh();
    void empty();
} uiwindow;
void userdisplay(void); //handles all of the user stuff

#endif /* defined(__SKS3__uinterface__) */
