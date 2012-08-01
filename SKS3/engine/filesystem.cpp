/*
 * Super Key Seeker Version 3
 * Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 * This software is free, it may be customized, redistributed, blah blah blah...
 */
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
    pause();
    ofstream f(env.savefile.c_str(), ios::trunc | ios::binary);
    if (!f)
    {
        clear();
        colorify(RED);
        cout << "ERROR! Savefile could not be written" << endl
             << "Press any key to continue your game" << endl;
        colorify(NORMAL);
        getch_();
    }
    f.write((char *)(&env), sizeof(_environment));
    f.close();
    unpause();
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
    cout << "Please select a slot to restore," << endl
         << "note: all slots may not have data." << endl
         << "Slots range from 0 to 5" << endl
         << ">";
    int slot = -1;
    cin >> slot;
    if (slot < 0 || slot > 5)
        return;
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
    small_delay();
    clear();
    cout << "Please select a slot to save to," << endl
    << "note: all slots may not have data." << endl
    << "Slots range from 0 to 5" << endl
    << ">";
    int slot = -1;
    cin >> slot;
    if (slot < 0 || slot > 5)
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