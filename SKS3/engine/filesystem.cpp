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
 File: filesystem.cpp
 Description: Code responsible for interacting with the filesystem
 and the environment variables.
 Authors: phyrrus9 <phyrrus9@gmail.com>
 *****************************************************************/
#include "filesystem.h"
extern _environment env; //global variable
void save(void)
{
    /*
     * Saves the current env variable to disk,
     * see environment.h to see what exactly it
     * writes. This contains all RAM used in
     * the program that is useful to the user
     */
    save_slot();
    /*pause();
    char *cmd = new char[50];
    strcpy(cmd, "rm -rf ");
    strcat(cmd, env.savefile.c_str());
    system(cmd);
    FILE *f;
    f = fopen(env.savefile.c_str(), "wb");
    if (f == NULL)
    {
        cout << "Err!" << endl;
        endwin();
        exit(1);
    }
    fwrite((void *)&env, sizeof(_environment), 1, f);
    fclose(f);
    unpause();*/
}
void restore(void)
{
    /*
     * Read the environment from disk and insert
     * it into the existing one, including all
     * maps, user data, etc.
     */
    pause();
    ifstream f(env.savefile.c_str(),ios::binary);
    if (!f)
    {
        clear();
        colorify(RED);
        cout << "ERROR! Savefile could not be read" << endl
             << "Press any key to continue your game" << endl;
        colorify(NORMAL);
        getch_();
    }
    f.read((char *)(&env), sizeof(_environment));
    f.close();
    unpause();
    //restore_slot();
}
string select_slot(int slot)
{
    /*
     * Games on older consoles used to have slots
     * that you could save to, so you could have
     * multiple (I think most used 5) games going
     * at the same time without affecting each
     * other.
     * Well, in SKS3 I decided to add this ability
     * to the game. You have 6 save slots and one
     * catchall null slot. Allowing you to go back
     * to the good 'ole days and be able to go back
     * if you were to say die on one level and needed
     * a new seed or something.
     */
    string saveslot = ".save-slot";
    switch (slot) 
    {
        case 0:
            saveslot += "0";
            break;
        case 1:
            saveslot += "1";
            break;
        case 2:
            saveslot += "2";
            break;
        case 3:
            saveslot += "3";
            break;
        case 4:
            saveslot += "4";
            break;
        case 5:
            saveslot += "5";
            break;
        default:
            saveslot += "-null";
            break;
    }
    saveslot += ".dat";
    return saveslot;
}
void restore_slot(void)
{
    /*
     * I know, this comment block is very much
     * shorter than the one above, but it is a 
     * simple function... All it does is restore
     * from a save slot :P
     */
    env.allow_refresh = false;
    pause();
    small_delay();
    clear();
    initscr();
    refresh();
    noecho();
    WINDOW *w;
    w = phyrrus9::nwin::wcreatewin(6, 35);
    setdisplay(w, " Please select a restore slot");
    wprintw(w, " slots range from 1 to 5\n");
    wprintw(w, " autosaves are in slot a\n");
    wprintw(w, " :");
    wrefresh(w);
    char c = getch_();
    if (c == 'a')
        c = '0';
    int slot = char_int(c);
    endwin();
    if (slot < 0 || slot > 5)
    {
        endwin();
        return;
    }
    string savefile = select_slot(slot);
    ifstream f(savefile.c_str(),ios::binary);
    if (!f)
        return;
    f.read((char *)(&env), sizeof(_environment));
    f.close();
    env.allow_refresh = true;
    unpause();
}
void save_slot(void)
{
    /*
     * Save to the selected slot...
     * yes, i know these are getting shorter.
     */
    env.allow_refresh = false;
    pause();
    clear();
    initscr();
    refresh();
    noecho();
    WINDOW *w;
    w = phyrrus9::nwin::wcreatewin(5, 35);
    setdisplay(w, " Please select a save slot");
    wprintw(w, " slots range from 1 to 5\n");
    wprintw(w, " :");
    wrefresh(w);
    char c = getch_();
    int slot = char_int(c);
    endwin();
    if (slot < 1 || slot > 5)
        return;
    string savefile = select_slot(slot);
    ofstream f(savefile.c_str(), ios::trunc | ios::binary);
    f.write((char *)(&env), sizeof(_environment));
    f.close();
    env.allow_refresh = true;
    unpause();
}
void small_delay(void)
{
    /*
     * Sometimes the refresh thread picks up too fast
     * and makes your allow_refresh = false; useless as
     * it has already overwritten the screen buffer. Call
     * this before writing to the screen to fix the problem
     */
    for (int i = 0 ; i < 1000; i++)
    { }
}

void settings_write(void)
{
    /*
     * Code to write the settings struct
     * to disk. Basically a binary file
     * overwrite of the structure.
     */
    
    ofstream out(".sks3settings", ios::binary | ios::trunc);
    out.write(reinterpret_cast<char *>(&env.settings), sizeof(_settings));
    out.close();
}

void settings_read(void)
{
    /*
     * Code to read the settings struct
     * from disk. Size and range checks
     * complete then the file is read
     * if it exists.
     */
    
    ifstream in(".sks3settings", ios::binary);
    if (!in) //file not exist
        return;
    in.seekg(ios::end);
    //if (in.tellg() != sizeof(_settings))
    //  return;
    in.seekg(ios::beg);
    in.read(reinterpret_cast<char *>(&env.settings), sizeof(_settings));
}

void autosave(void)
{
    string savefile = select_slot(0);
    if (env.competition)
    {
       savefile = env.competition.username;
    }
    ofstream f(savefile.c_str(), ios::trunc | ios::binary);
    if (!f)
        exit(-1);
    f.write((char *)(&env), sizeof(_environment));
    f.close();
}
