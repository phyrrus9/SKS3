/*
 * Super Key Seeker Version 3
 * Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 * This software is free, it may be customized, redistributed, blah blah blah...
 */
#include "movement.h"
#include "attack.h"
extern _environment env; //global variable
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
void turn(direction d)
{
    env.player = (character::player)(d);
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
        env.player = (character::player)(d);
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
            //cout <<  "@";
            showplayer();
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
void showplayer(void)
{
    if (env.player == character::N)
        cout << '^';
    if (env.player == character::S)
        cout << 'v';
    if (env.player == character::E)
        cout << '<';
    if (env.player == character::W)
        cout << '>';
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
