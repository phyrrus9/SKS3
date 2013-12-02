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
 File: windows/keys_control_panel.cpp
 Description: Code for the keys configuration control panel.
 Authors: phyrrus9 <phyrrus9@gmail.com>
 the GNU Project (ncurses)
 *****************************************************************/
#include "settings.h"
void key_settings_window(void)
{
    /*
     * Key settings code. This code
     * will create a new window for
     * configuring the game keys
     * and popping them into the
     * environment.
     */
    
    WINDOW *vin;
    initscr();
    refresh();
    noecho();
    int height = 7, width = 22;
    vin = phyrrus9::nwin::wcreatewin(height, width);
    wmove(vin,0,0);
    setdisplay(vin, " Key settings");
    wprintw(vin, " Up movement key\n");
    wprintw(vin, " Current: %c\n", env.settings.keys.w);
    wprintw(vin," New:");
    wrefresh(vin);
    env.settings.keys.w = getche();
    setdisplay(vin, " Key settings");
    wprintw(vin, " Left movement key\n");
    wprintw(vin, " Current: %c\n", env.settings.keys.a);
    wprintw(vin," New:");
    wrefresh(vin);
    env.settings.keys.a = getche();
    setdisplay(vin, " Key settings");
    wprintw(vin, " Down movement key\n");
    wprintw(vin, " Current: %c\n", env.settings.keys.s);
    wprintw(vin," New:");
    wrefresh(vin);
    env.settings.keys.s = getche();
    setdisplay(vin, " Key settings");
    wprintw(vin, " Right movement key\n");
    wprintw(vin, " Current: %c\n", env.settings.keys.d);
    wprintw(vin," New:");
    wrefresh(vin);
    env.settings.keys.d = getche();
    
    setdisplay(vin, " Key settings");
    wprintw(vin, " Up look key\n");
    wprintw(vin, " Current: %c\n", env.settings.keys.i);
    wprintw(vin," New:");
    wrefresh(vin);
    env.settings.keys.i = getche();
    setdisplay(vin, " Key settings");
    wprintw(vin, " Down look key\n");
    wprintw(vin, " Current: %c\n", env.settings.keys.j);
    wprintw(vin," New:");
    wrefresh(vin);
    env.settings.keys.j = getche();
    setdisplay(vin, " Key settings");
    wprintw(vin, " Left look key\n");
    wprintw(vin, " Current: %c\n", env.settings.keys.k);
    wprintw(vin," New:");
    wrefresh(vin);
    env.settings.keys.k = getche();
    setdisplay(vin, " Key settings");
    wprintw(vin, " Right look key\n");
    wprintw(vin, " Current: %c\n", env.settings.keys.l);
    wprintw(vin," New:");
    wrefresh(vin);
    env.settings.keys.l = getche();
    
    setdisplay(vin, " Key settings");
    wprintw(vin, " Save key\n");
    wprintw(vin, " Current: %c\n", env.settings.keys.S);
    wprintw(vin," New:");
    wrefresh(vin);
    env.settings.keys.S = getche();
    setdisplay(vin, " Key settings");
    wprintw(vin, " Restore key\n");
    wprintw(vin, " Current: %c\n", env.settings.keys.R);
    wprintw(vin," New:");
    wrefresh(vin);
    env.settings.keys.R = getche();
    
    setdisplay(vin, " Key settings");
    wprintw(vin, " Save slot key\n");
    wprintw(vin, " Current: %c\n", env.settings.keys.ss);
    wprintw(vin," New:");
    wrefresh(vin);
    env.settings.keys.ss = getche();
    setdisplay(vin, " Key settings");
    wprintw(vin, " Restore slot key\n");
    wprintw(vin, " Current: %c\n", env.settings.keys.rs);
    wprintw(vin," New:");
    wrefresh(vin);
    env.settings.keys.rs = getche();
    
    setdisplay(vin, " Key settings");
    wprintw(vin, " Attack key\n");
    wprintw(vin, " Current: %c\n", env.settings.keys.attack);
    wprintw(vin," New:");
    wrefresh(vin);
    env.settings.keys.attack = getche();
    setdisplay(vin, " Key settings");
    wprintw(vin, " Pause key\n");
    wprintw(vin, " Current: %c\n", env.settings.keys.pause);
    wprintw(vin," New:");
    wrefresh(vin);
    env.settings.keys.pause = getche();
    setdisplay(vin, " Key settings");
    wprintw(vin, " Quit key\n");
    wprintw(vin, " Current: %c\n", env.settings.keys.quit);
    wprintw(vin," New:");
    wrefresh(vin);
    env.settings.keys.quit = getche();
    setdisplay(vin, " Key settings");
    wprintw(vin, " Engine command key\n");
    wprintw(vin, " Current: %c\n", env.settings.keys.engine);
    wprintw(vin," New:");
    wrefresh(vin);
    env.settings.keys.engine = getche();
    
    setdisplay(vin, " Key settings");
    wprintw(vin, " Control panel key\n");
    wprintw(vin, " Current: %c\n", env.settings.keys.settings);
    wprintw(vin," New:");
    wrefresh(vin);
    env.settings.keys.settings = getche();
    
    cldisplay(vin);
    delwin(vin);
    endwin();
}