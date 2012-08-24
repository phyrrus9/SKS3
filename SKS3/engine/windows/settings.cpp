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
 File: settings.cpp
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
    vin = newwin(0, 0, 0, 0);
    wmove(vin, 0, 0);
    char ch;
    while (true)
    {
        setdisplay(vin, "Control panel");
        wprintw(vin, "Please select the correct panel\n"
                     "1.) Key control panel          \n"
                     "*.) Developer control panel    \n"
                     "2.) Back to game               \n\n"
                     " * denotes a disabled panel    \n");
        wprintw(vin, ">");
        wrefresh(vin);
        ch = getch();
        if (ch == '1')
        {
            key_settings_window();
            controlled = true;
        }
        if (ch == '2')
            break;
        if (controlled)
            break;
    }
}

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
    vin=newwin(0,0,0,0);
    wmove(vin,0,0);
    setdisplay(vin, "Key settings");
    wprintw(vin, "Up movement key\n");
    wprintw(vin, "Current: %c\n", env.settings.keys.w);
    wprintw(vin,"New:");
    wrefresh(vin);
    env.settings.keys.w = getch();
    setdisplay(vin, "Key settings");
    wprintw(vin, "Left movement key\n");
    wprintw(vin, "Current: %c\n", env.settings.keys.a);
    wprintw(vin,"New:");
    wrefresh(vin);
    env.settings.keys.a = getch();
    setdisplay(vin, "Key settings");
    wprintw(vin, "Down movement key\n");
    wprintw(vin, "Current: %c\n", env.settings.keys.s);
    wprintw(vin,"New:");
    wrefresh(vin);
    env.settings.keys.s = getch();
    setdisplay(vin, "Key settings");
    wprintw(vin, "Right movement key\n");
    wprintw(vin, "Current: %c\n", env.settings.keys.d);
    wprintw(vin,"New:");
    wrefresh(vin);
    env.settings.keys.d = getch();
    
    setdisplay(vin, "Key settings");
    wprintw(vin, "Up look key\n");
    wprintw(vin, "Current: %c\n", env.settings.keys.i);
    wprintw(vin,"New:");
    wrefresh(vin);
    env.settings.keys.i = getch();
    setdisplay(vin, "Key settings");
    wprintw(vin, "Down look key\n");
    wprintw(vin, "Current: %c\n", env.settings.keys.j);
    wprintw(vin,"New:");
    wrefresh(vin);
    env.settings.keys.j = getch();
    setdisplay(vin, "Key settings");
    wprintw(vin, "Left look key\n");
    wprintw(vin, "Current: %c\n", env.settings.keys.k);
    wprintw(vin,"New:");
    wrefresh(vin);
    env.settings.keys.k = getch();
    setdisplay(vin, "Key settings");
    wprintw(vin, "Right look key\n");
    wprintw(vin, "Current: %c\n", env.settings.keys.l);
    wprintw(vin,"New:");
    wrefresh(vin);
    env.settings.keys.l = getch();
    
    setdisplay(vin, "Key settings");
    wprintw(vin, "Save key\n");
    wprintw(vin, "Current: %c\n", env.settings.keys.S);
    wprintw(vin,"New:");
    wrefresh(vin);
    env.settings.keys.S = getch();
    setdisplay(vin, "Key settings");
    wprintw(vin, "Restore key\n");
    wprintw(vin, "Current: %c\n", env.settings.keys.R);
    wprintw(vin,"New:");
    wrefresh(vin);
    env.settings.keys.R = getch();
    
    setdisplay(vin, "Key settings");
    wprintw(vin, "Attack key\n");
    wprintw(vin, "Current: %c\n", env.settings.keys.attack);
    wprintw(vin,"New:");
    wrefresh(vin);
    env.settings.keys.attack = getch();
    setdisplay(vin, "Key settings");
    wprintw(vin, "Pause key\n");
    wprintw(vin, "Current: %c\n", env.settings.keys.pause);
    wprintw(vin,"New:");
    wrefresh(vin);
    env.settings.keys.pause = getch();
    setdisplay(vin, "Key settings");
    wprintw(vin, "Quit key\n");
    wprintw(vin, "Current: %c\n", env.settings.keys.quit);
    wprintw(vin,"New:");
    wrefresh(vin);
    env.settings.keys.quit = getch();
    setdisplay(vin, "Key settings");
    wprintw(vin, "Engine command key\n");
    wprintw(vin, "Current: %c\n", env.settings.keys.engine);
    wprintw(vin,"New:");
    wrefresh(vin);
    env.settings.keys.engine = getch();
    
    setdisplay(vin, "Key settings");
    wprintw(vin, "Control panel key\n");
    wprintw(vin, "Current: %c\n", env.settings.keys.settings);
    wprintw(vin,"New:");
    wrefresh(vin);
    env.settings.keys.settings = getch();
    
    delwin(vin);
    endwin();
}

void setdisplay(WINDOW * w, const char * title)
{
    /*
     * Function to write title to a window.
     * This is an optimization and really
     * shouldnt be changed.
     */
    
    wclear(w);
    wprintw(w, "%s\n", title);
    wrefresh(w);
}