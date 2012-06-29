/*
 * Super Key Seeker Version 3
 * Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 * This software is free, it may be customized, redistributed, blah blah blah...
 */
#include "engine.h"
#include "attack.h"
extern _environment env; //global var
void kill(int p)
{
    env.map[p] = env.grid[p] = echar;
    env.kills++;
}
void eat(int p)
{
    bool ate = false;
    if (env.map[p] == '%')
    {
        env.health -= 5;
        env.score += targetnoms::SMALLBUG;
        ate = true;
    }
    if (env.map[p] == '&')
    {
        env.health -= 4;
        env.score += targetnoms::LARGEBUG;
        ate = true;
    }
    if (env.map[p] == '$')
    {
        env.health -= 3;
        env.score += targetnoms::WORM;
        ate = true;
    }
    if (env.map[p] == '!')
    {
        env.health -= 25;
        env.score += targetnoms::PITBULL;
        ate = true;
    }
    if (env.map[p] == '+')
    {
        env.lives++;
        ate = true;
    }
    if (ate)
        kill(p);
}
void attack(void)
{
    int location = -1, gain = 0, pos = env.position;
    character::target t;
    if (env.player == character::N)
        if (pos - 30 > 0)
            location = pos - 30;
    if (env.player == character::S)
        if (pos + 30 < 900)
            location = pos + 30;
    if (env.player == character::E)
        if (pos - 1 > 0)
            location = pos - 1;
    if (env.player == character::W)
        if (pos + 1 < 900)
            location = pos + 1;
    if (location < 0)
        return;
    if (env.view[location] == '%')
    {
        t = character::SMALLBUG;
        gain = targetnoms::SMALLBUG;
    }
    if (env.view[location] == '&')
    {
        t = character::LARGEBUG;
        gain = targetnoms::LARGEBUG;
    }
    if (env.view[location] == '$')
    {
        t = character::WORM;
        gain = targetnoms::WORM;
    }
    if (env.view[location] == '!')
    {
        t = character::PITBULL;
        gain = targetnoms::PITBULL;
    }
    int strength = env.levels_completed * t;
    //cout << strength << endl; //debug
    int attack = env.attack;
    weapons::weaponlist weapon;
    attack *= weapon.strength[env.selectedweapon]; //add a little boost
    if (attack >= strength)
    {
        kill(location);
        env.score += gain;
    }
}
void increment_attack(void)
{
    int divisor = 1 + env.attack, increment = 1, total = env.health * env.lives;
    const int multiplier = 5;
    if (total / divisor > 1) //kgood
    {
        env.attack += increment;
        env.health -= env.score / divisor;
    }
}
void showweapons(void)
{
    //D(fist) x(throwing star) |(sword) ©(gun) {}(cannon) ~(laser)
    if (env.weapons[0])
    {
        if (env.selectedweapon == 0)
            colorify(RED);
        cout << "D ";
        colorify();
    }
    if (env.weapons[1])
    {
        if (env.selectedweapon == 1)
            colorify(RED);
        cout << "x ";
        colorify();
    }
    if (env.weapons[2])
    {
        if (env.selectedweapon == 2)
            colorify(RED);
        cout << "| ";
        colorify();
    }
    if (env.weapons[3])
    {
        if (env.selectedweapon == 3)
            colorify(RED);
        cout << "© ";
        colorify();
    }
    if (env.weapons[4])
    {
        if (env.selectedweapon == 4)
            colorify(RED);
        cout << "{} ";
        colorify();
    }
    if (env.weapons[5])
    {
        if (env.selectedweapon == 5)
            colorify(RED);
        cout << "~ ";
        colorify();
    }
}
void setselectedweapon(int w)
{
    if (env.weapons[w])
        env.selectedweapon = w;
}