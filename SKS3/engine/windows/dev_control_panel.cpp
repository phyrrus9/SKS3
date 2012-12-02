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
    int height = 7, width = 42;
    int wheight = 11, wwidth = 42;
    vin = phyrrus9::nwin::wcreatewin(wheight, wwidth);
    wmove(vin,0,0);
    char tmpc;
    //first, before we can allow this to happen we need to display
    //a warning so the user knows we mean business.
    setdisplay(vin, " Developer settings");
    wprintw(vin, " Warning, this is the developer console\n"
                 " this is not something to play with. so\n"
                 " please be careful. This panel will let\n"
                 " you do things beyond your far dreams, \n"
                 " which makes it dangerous. If you don't\n"
                 " know how to handle this, press Q now, \n"
                 " If you know the risks, and you wish to\n"
                 " proceed, press any other key.");
    wrefresh(vin);
    tmpc = getch_();
    if (tmpc != 'Q')
    {
        while (tmpc != '4')
        {
            phyrrus9::nwin::wresizewindow(vin, height, width);
            setdisplay(vin, " Developer settings");
            wprintw(vin, " 1. Game settings\n");
            wprintw(vin, " 2. Engine settings\n", env.cheats);
            wprintw(vin, " 3. Developer mods\n");
            wprintw(vin, " 4. Return ");
            wrefresh(vin);
            tmpc = getch_();
        
            if (tmpc == '1')
            {
                setdisplay(vin, " Game settings");
                wprintw(vin, " Enable cheats?\n");
                wprintw(vin, " Old: %.1d\n", env.cheats);
                wprintw(vin, " New: ");
                wrefresh(vin);
                tmpc = getch_();
                env.cheats = tmpc - 48;
                wrefresh(vin);
                setdisplay(vin, " Developer settings");
                wprintw(vin, " Enable fog?\n");
                wprintw(vin, " Old: %.1d\n", env.showmap);
                wprintw(vin, " New: ");
                wrefresh(vin);
                tmpc = getch_();
                env.showmap = tmpc - 48;
            }
        
            if (tmpc == '2')
            {
                while (tmpc != 'z')
                {
                    phyrrus9::nwin::wresizewindow(vin, height + 2, width);
                    setdisplay(vin, " Engine settings");
                    wprintw(vin, " a. Modify save file location\n");
                    wprintw(vin, " b. Modify map location\n");
                    wprintw(vin, " y. Disable developer mode\n");
                    wprintw(vin, " z. Return to developer menu. ");
                    wrefresh(vin);
                    tmpc = getch_();
                    werase(vin);
                    wrefresh(vin);
                    wresize(vin, height, width);
                    wrefresh(vin);
                    if (tmpc == 'a')
                    {
                        phyrrus9::nwin::wresizewindow(vin, height + 1, width);
                        char * tempstr = new char[30];
                        setdisplay(vin, " Engine save file");
                        wprintw(vin, " Current: %s\n", env.savefile.c_str());
                        wprintw(vin, " Please enter a new name. You\n");
                        wprintw(vin, " will not see this until pressing\n");
                        wprintw(vin, " the enter key. ");
                        wrefresh(vin);
                        scanf("%s", tempstr);
                        env.savefile = tempstr;
                        delete tempstr;
                        werase(vin);
                        wrefresh(vin);
                        wresize(vin, height, width);
                        setdisplay(vin, " Engine save file");
                        wprintw(vin, " Save file: %s\n", env.savefile.c_str());
                        wprintw(vin, " Press any key to return\n ");
                        wrefresh(vin);
                        getch_();
                        werase(vin);
                        wrefresh(vin);
                        wresize(vin, height, width);
                        wrefresh(vin);
                    }
                    
                    if (tmpc == 'b')
                    {
                        setdisplay(vin, " Modify map location");
                        wprintw(vin, " Please enter the map location\n :");
                        wrefresh(vin);
                        int _location;
                        cin >> _location;
                        setdisplay(vin, " Modify map location");
                        wprintw(vin, " Map location: %d\n", _location);
                        wprintw(vin, " Current value: %c\n", env.map[_location]);
                        wprintw(vin, " New value: ");
                        wrefresh(vin);
                        env.map[_location] = getch_();
                        setdisplay(vin, " Map location modified");
                        wprintw(vin, " Map position: %d\n", _location);
                        wprintw(vin, " Value: %c\n", env.map[_location]);
                        wprintw(vin, " Press any key to return... ");
                        wrefresh(vin);
                        getch_();
                        werase(vin);
                    }
                    
                    if (tmpc == 'y')
                    {
                        setdisplay(vin, " Disable developer mode");
                        wprintw(vin, " Are you sure you want to do this?\n");
                        wprintw(vin, " Please enter 1 (yes) or 0 (no)\n");
                        wprintw(vin, " :");
                        wrefresh(vin);
                        char c = getch_();
                        if (c == '1')
                        {
                            env.developer_mode = false;
                            env.can_enable_developer_mode = true;
                        }
                    }
                }
                werase(vin);
            }
            if (tmpc == '3')
            {
                int dmheight = 7;
                int dmwidth = 50;
                dmheight += env.modcount;
                phyrrus9::nwin::wresizewindow(vin, dmheight, dmwidth);
                setdisplay(vin, " Developer mods");
                wprintw(vin, " Please select mod to enable.\n");
                wprintw(vin, " Enabled mods cannot be disabled (yet)\n");
                wprintw(vin, " * denotes an enabled mod\n");
                if (env.modcount > 0)
                {
                    for (int i = 0; i < env.modcount; i++)
                    {
                        wprintw(vin, " %d Name: %s", i + 1, env.modlist[i].name);
                        if (env.modlist[i].enabled == true)
                        {
                            wprintw(vin, "*");
                        }
                        wprintw(vin, "\n");
                    }
                    wprintw(vin, " :");
                    wrefresh(vin);
                    char modnum = 0;
                    do
                    {
                        modnum = getch_();
                    } while (modnum < '0' && modnum > env.modcount + 48);
                    int mod_number = char_int(modnum) - 1;
                    if (env.modlist[mod_number].enabled == false)
                    {
                        phyrrus9::nwin::wresizewindow(vin, 4, 35);
                        setdisplay(vin, " Mod enabled");
                        wprintw(vin, " %s enabled\n", env.modlist[mod_number].name);
                        env.modlist[mod_number].enabled = true;
                        enablemod(mod_number);
                    }
                    else
                    {
                        phyrrus9::nwin::wresizewindow(vin, 4, 35);
                        setdisplay(vin, " Error!");
                        wprintw(vin, " %s is already enabled\n", env.modlist[mod_number].name);
                    }
                }
                wrefresh(vin);
                getch_();
            }
        }
    }
    werase(vin);
    cldisplay(vin);
}