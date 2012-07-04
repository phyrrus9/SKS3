/*
 * Super Key Seeker Version 3
 * Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 * This software is free, it may be customized, redistributed, blah blah blah...
 */
#include "filesystem.h"
extern _environment env; //global variable
void save(void)
{
    ofstream f(env.savefile.c_str(), ios::trunc | ios::binary);
    f.write((char *)(&env), sizeof(_environment));
    f.close();
}
void restore(void)
{
    ifstream f(env.savefile.c_str(),ios::binary);
    f.read((char *)(&env), sizeof(_environment));
    f.close();
}
void restore_slot(void)
{
    cout << "Please select a slot to restore," << endl
         << "note: all slots may not have data." << endl
         << "Slots range from 0 to 5" << endl
         << ">";
    int slot = -1;
    cin >> slot;
    if (slot < 0 || slot > 5)
        return;
    ostringstream t;
    t << ".save-slot" << t << ".dat";
    string savefile = t.str();
    ifstream f(savefile.c_str(),ios::binary);
    if (!f)
        return;
    f.read((char *)(&env), sizeof(_environment));
    f.close();
}
void save_slot(void)
{
    cout << "Please select a slot to save to," << endl
    << "note: all slots may not have data." << endl
    << "Slots range from 0 to 5" << endl
    << ">";
    int slot = -1;
    cin >> slot;
    if (slot < 0 || slot > 5)
        return;
    ostringstream t;
    t << ".save-slot" << t << ".dat";
    string savefile = t.str();
    ofstream f(savefile.c_str(), ios::trunc | ios::binary);
    f.write((char *)(&env), sizeof(_environment));
    f.close();
}