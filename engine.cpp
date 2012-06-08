/*
 * Super Key Seeker Version 3
 * Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 * This software is free, it may be customized, redistributed, blah blah blah...
 */
#ifndef SKS3_engine_h
#include "engine.h"
#endif
_environment env; //global var

void terminate(int param) //segmentation fault on clean exit (unalloc from restore bug tempfix)
{
    kill(getpid(), SIGTERM);
}
char getch_()
{
    char c;
    initscr();
    cbreak();
    c = getch();
    endwin();
    return c;
}
void colorify(void)
{
    color c = env.bgcolor;
    if (c == RED)
        cout << "\33[31m";
    if (c == BLUE)
        cout << "\33[34m";
    if (c == GREEN)
        cout << "\33[32m";
    if (c == NORMAL)
        cout << "\33[0m";
}
void colorify(color c)
{

        if (c == RED)
            cout << "\33[31m";
        if (c == BLUE)
            cout << "\33[34m";
        if (c == GREEN)
            cout << "\33[32m";
        if (c == NORMAL)
            cout << "\33[0m";
}
void enginecmd(string c, string d)
{
    if (c == "env->health")
        env.health = atoi(d.c_str());
    if (c == "env->lives")
        env.lives = atoi(d.c_str());
    if (c == "env->score")
        env.score = atoi(d.c_str());
    if (c == "env->position")
        env.position = atoi(d.c_str());
    if (c == "env->moves")
        env.moves = atoi(d.c_str());
    if (c == "env->kills")
        env.kills = atoi(d.c_str());
    if (c == "env->kills_needed")
        env.kills_needed = atoi(d.c_str());
    if (c == "env->lc")
        env.levels_completed = atoi(d.c_str());
    if (c == "gam->savefile")
        env.savefile = d;
    if (c == "env->foggy")
        env.showmap = atoi(d.c_str());;

    if (c == "colorify")
    {
        if (d == "red")
            env.bgcolor = RED;
        if (d == "green")
            env.bgcolor = GREEN;
        if (d == "blue")
            env.bgcolor = BLUE;
        if (d == "normal")
            env.bgcolor = NORMAL;
        move(NIL);
    }
    if (c == "env->pcolor")
    {
        if (d == "red")
            env.playercolor = RED;
        if (d == "green")
            env.playercolor = GREEN;
        if (d == "blue")
            env.playercolor = BLUE;
        if (d == "normal")
            env.playercolor = RED;
    }
    if (c == "gam")
    {
        if (d == "save")
            save();
        if (d == "restore")
            restore();
    }
    if (c == "get")
    {
        if (d == "env->health")
            cout << env.health << endl;
        if (d == "env->lives")
            cout << env.lives << endl;
        if (d == "env->score")
            cout << env.score << endl;
        if (d == "env->position")
            cout << env.position << endl;
        if (d == "env->moves")
            cout << env.moves << endl;
        if (d == "env->kills")
            cout << env.kills << endl;
        if (d == "env->kills_needed")
            cout << env.kills_needed << endl;
        if (d == "env->lc")
            cout << env.levels_completed << endl;
        if (d == "gam->savefile")
            cout << env.savefile << endl;
        if (d == "env->size")
            cout << sizeof(_environment) << endl;
        cout << "Press any key to continue..." << endl;
        getch_(); //char c = ...
    }
}
void showhelp(void)
{
    clear();
    cout << "Super Key Seeker 3 - Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>" << endl
         << "This game is copyright to Ethan laur(phyrrus9) under modtech LLC" << endl
         << "To use:" << endl
         << "Run the game from the terminal or SSH." << endl
         << "Your player will be the @ character on the screen, you may move by pressing:" << endl
         << "w - Up" << endl
         << "a - Left" << endl
         << "s - Down" << endl
         << "d - Right" << endl
         << "Movement is automatic, no need to press enter." << endl
         << "Other commands used in the game are:" << endl
         << "S - Save game" << endl
         << "R - Restore game" << endl
         << "Q - Quit game" << endl
         << "N - New game" << endl
         << "H - Show help" << endl
         << "Characters in the game are:" << endl
         << "~ - Neutral (empty)" << endl
         << "% - Large bug" << endl
         << "& - Small bug" << endl
         << "$ - Worm" << endl
         << "! - Vicious pitbull" << endl
         << "You can change the color of the text (if your terminal does not support it)" << endl
         << "To do so, type /colorify and then one of the following colors:" << endl
         << "red, blue, green, yellow, normal" << endl
         << "You can change the player (@) color with the same colors by using /env->pcolor "
         << "<color>" << endl
         << "You can disable the fog by typing /env->foggy 0 and turn it on by using 1" << endl
         << "Good luck! Press any key to exit help.." << endl;
    getch_(); //just got rid of char c = to fix the err below
    //delete &c; //gets rid of unused var warning //nevermind: SKS3(19240) malloc: *** error for object 0x7fff655e69f7: pointer being freed was not allocated
}
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
void display(void)
{
    colorify(NORMAL);
    cout << left << setw(12) << "SKS3 (PR1)" << setw(7) << "Health:" << setw(5) << env.health << setw(7) << "Lives:" << setw(4) << env.lives <<  setw(7) << "Kills:" << setw(3) << env.kills << setw(14) << "Kills needed:" << setw(5) << env.kills_needed << setw(20) << "Levels completed:" << setw(5) << env.levels_completed << setw(7) << "Score:" << setw(9) << (((((env.score * (env.levels_completed * 2)) + (env.health / 3)) + env.kills) + env.lives) - (env.moves / 3)) << endl;
    colorify();
}
void eat(int p)
{
    if (env.map[p] == '%')
    {
        env.kills++;
        env.health -= 5;
        env.score += 50;
        env.map[p] = echar;
    }
    if (env.map[p] == '&')
    {
        env.kills++;
        env.health -= 4;
        env.score += 25;
        env.map[p] = echar;
    }
    if (env.map[p] == '$')
    {
        env.kills++;
        env.health -= 3;
        env.score += 20;
        env.map[p] = echar;
    }
    if (env.map[p] == '!')
    {
        env.kills++;
        env.health -= 25;
        env.score += 55;
        env.map[p] = echar;
    }
    if (env.map[p] == '+')
    {
        env.lives++;
        env.map[p] = echar;
    }
}
void populate(void)
{
    int health_i = 0;
    env.map[0] = env.grid[0] = '@';
    if (!env.single)
    {
        env.kills_needed = env.kills = 0;
        for (int i = 1; i < 900; i++)
        {
            env.grid[i] = '?';
            int r = rand() % 32;
            env.map[i] = echar;
            if (r == 1)
            {
                env.kills_needed++;
                env.map[i] = '%';
            }
            if (r == 2)
            {
                env.kills_needed++;
                env.map[i] = '&';
            }
            if (r == 3)
            {
                env.kills_needed++;
                env.map[i] = '$';
            }
            if (r == 4)
            {
                health_i++;
                if (health_i % 7 == 0)
                    env.map[i] = '+';
            }
            if (r == 5)
            {
                env.kills_needed++;
                env.map[i] = '!';
            }
            if (r >= 6 && r <= 11)
                env.map[i] = '#';
        }
    }
    else 
    {
        //??
    }
    env.kills_needed /= 3;
}
void move(direction d)
{
    void (*prev_fn)(int);
    prev_fn = signal (SIGSEGV,terminate); //bugfix
    int prev = env.position;
    bool moved = false;
    if (d == N)
        if (env.map[env.position - 30] != '#' && (env.position - 30 > 0))
        {
            eat(env.position - 30);
            env.position -= 30;
            moved = true;
        }
    if (d == S)
        if (env.map[env.position + 30] != '#' && (env.position + 30 < 900))
        {
            eat(env.position + 30);
            env.position += 30;
            moved = true;
        }
    if (d == E)
        if (env.map[env.position - 1] != '#' && (env.position - 1 > 0))
        {
            eat(env.position - 1);
            env.position -= 1;
            moved = true;
        }
    if (d == W)
        if (env.map[env.position + 1] != '#' && (env.position + 1 < 900))
        {
            eat(env.position+ 1);
            env.position += 1;
            moved = true;
        }
    if (d == SAV)
        save();
    if (d == RES)
        restore();
    if (d == QUI)
    {
        colorify(NORMAL); //un-colorify
        exit(EXIT_SUCCESS);
    }
    if (d == HLP)
        showhelp();
    if (moved)
    {
        env.map[prev] = env.grid[prev] = echar;
        env.view[env.position] = '@';
        light(env.position);
        env.moves += 1;
    }
}
void showmap(void)
{
    colorify();
    cout << "#  ";
    for (int i = 0; i < 46; i++)
        cout << "# ";
    cout << endl;
    for (int i = 0, j = 1; i < 900; i++, j++)
    {
        if (i % 30 == 0)
            cout << "#  ";
        if (i != env.position)
        {
            if (env.view[i] != '~' && env.view[i] != '#' && env.view[i] != '?')
                if (env.view[i] != '+')
                    colorify(GREEN);
            cout << env.view[i] << "  ";
            colorify();
        }
        else
        {
            colorify(env.playercolor);
            cout <<  "@";
            colorify();
            cout << "  ";
        }
        if (j == 30)
        {
            cout << '#' << endl;
            j = 0;
        }
    }
    cout << "#  ";
    for (int i = 0; i < 46; i++)
        cout << "# ";
    cout << endl;
    colorify();
}
void light(int p)
{
    if ((p - 29) >= 0)
        env.grid[p - 29] = env.map[p - 29];
    if ((p - 30) >= 0)
        env.grid[p - 30] = env.map[p - 30];
    if ((p - 31) >= 0)
        env.grid[p - 31] = env.map[p - 31];
    if ((p - 1) >= 0)
        env.grid[p - 1] = env.map[p - 1];
    if ((p + 1) < 900)
        env.grid[p + 1] = env.map[p + 1];
    if ((p + 29) < 900)
        env.grid[p + 29] = env.map[p + 29];
    if ((p + 30) < 900)
        env.grid[p + 30] = env.map[p + 30];
    if ((p + 31) < 900)
        env.grid[p + 31] = env.map[p + 31];
}
