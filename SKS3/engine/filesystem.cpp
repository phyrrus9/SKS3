/*
 * Super Key Seeker Version 3
 * Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 * This software is free, it may be customized, redistributed, blah blah blah...
 */
#include "filesystem.h"
extern _environment env; //global variable
void save(void)
{
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
    pause();
    env.allow_refresh = false;
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
    pause();
    env.allow_refresh = false;
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