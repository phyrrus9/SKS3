/*
 * Super Key Seeker Version 3
 * Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 * This software is free, it may be customized, redistributed, blah blah blah...
 */
#include "user.h"
extern _environment env; //global variable
extern bool game_initialized;
void showhelp(void)
{
    clear();
    cout << "Super Key Seeker 3 - Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>" << endl
    << "This game is copyright to Ethan laur(phyrrus9) under modtech LLC" << endl
    << "To use:" << endl
    << "Run the game from the terminal or SSH." << endl
    << "Your player will show up as the following characters, and it is an arrow:" << endl
    << "^ - You are looking up" << endl
    << "> - You are looking to the right" << endl
    << "v - You are looking down" << endl
    << "< - You are looking to the left" << endl
    << "Your player will be the red character on the screen, you may move by pressing:" << endl
    << "w - Move Up                    i - Look Up" << endl
    << "a - Move Left                  j - Look Left" << endl
    << "s - Move Down                  k - Look Down" << endl
    << "d - Move Right                 l - Look Right" << endl
    << "No need to press enter, character icon will update automatically" << endl
    << "You do not need to run into a target to attack it, you may use the following:" << endl
    << "e - Attack target facing arrow" << endl
    << "E - Increment your attack points" << endl
    << "Weapons are available in the game and will be added to your view when earned" << endl
    << "The current selection will show up in red in the weapons selector." << endl
    << "Here is a list of weapons:" << endl
    << "D - Your fist (default)        x - Throwing star (level 2)" << endl
    << "| - Sword (level 5)            © - Gun (level 10)" << endl
    << "{}- Canon (level 25)           ~ - Laser (level 50)" << endl
    << "To select a weapon, just use the keypad number of your choice" << endl
    << "Other commands used in the game are:" << endl
    << "S - Save game                  R - Restore game" << endl
    << "Q - Quit game                  N - New game" << endl
    << "H - Show help" << endl
    << "Characters in the game are:" << endl
    << "~ - Neutral (empty)            % - Large bug" << endl
    << "& - Small bug                  $ - Worm" << endl
    << "! - Vicious pitbull" << endl
    << "You can change the color of the text (if your terminal does not support it)" << endl
    << "To do so, type /colorify (or /env->pcolor) and then one of the following colors:" << endl
    << "red, blue, green, yellow, normal" << endl
    << "You can disable the fog by typing /env->foggy 0 and turn it on by using 1" << endl;
    if (game_initialized)
    {
        cout << "Good luck! Press any key to exit help.." << endl;
        getch_(); //just got rid of char c = to fix the err below
    }
    else
    {
        colorify(RED);
        cout << "This dialog will close in 15 seconds." << endl
        << "To disable this, just add a file named .sksfastboot to this directory" << endl;
        ifstream sksfastboot(".sksfastboot");
        if (!sksfastboot)
            sleep(15);
        colorify();
    }
    //delete &c; //gets rid of unused var warning //nevermind: SKS3(19240) malloc: *** error for object 0x7fff655e69f7: pointer being freed was not allocated
}
void display(void)
{
    weapons::weaponlist t;
    colorify(NORMAL);
    env.totalscore = (((((env.score * (env.levels_completed * 2)) + (env.health / 3)) + env.kills) + env.lives) - (env.moves / 3));
    cout << left << setw(13) << VERSION_BUILD << setw(7) << "Health:" << setw(5) << env.health << setw(7) << "Lives:" << setw(4) << env.lives <<  setw(7) << "Kills:" << setw(3) << env.kills << setw(14) << "Kills needed:" << setw(5) << env.kills_needed << setw(20) << "Levels completed:" << setw(5) << env.levels_completed << setw(7) << "Attack:" << setw(3) << env.attack << setw(8) << "Weapon:" << setw(5) << (env.attack * (t.strength[env.selectedweapon])) << setw(7) << setprecision(6) << fixed << "Score:" << setw(9) << env.totalscore;
    showweapons();
    cout << endl;
    multidisplay();
    colorify();
}
void multidisplay(void)
{
    if (strcmp(env.socket_message, "\251") != 0)
        cout << "[player 2] " << env.socket_message << endl;
}