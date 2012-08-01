/*
 * Super Key Seeker Version 3
 * Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 * This software is free, it may be customized, redistributed, blah blah blah...
 */
#include "attack.h"
extern _environment env; //global var
class clrthread_atk : public tpool::Thread
{
    /*
     * Pretty simple, when you attack, this will turn the
     * statusbar red for one second
     */
    virtual void Entry(void)
    {
        env.statuscolor = RED; //make the whole bar red
        sleep(1); //wait a few moves
        env.statuscolor = NORMAL; //put it back
    }
};
class clrthread_lif : public tpool::Thread
{
    /*
     * This thread runs pretty much the same as the attack
     * thread does, but instead of red, it turns the status
     * bar blue when you obtain a life point.
     */
    virtual void Entry(void)
    {
        env.statuscolor = BLUE; //make the whole bar blue
        sleep(1); //wait a few moves
        env.statuscolor = NORMAL; //put it back
    }
};
void attack_color_change(void)
{
    clrthread_atk *clrchg = new clrthread_atk;
    clrchg->Run();
}
void kill(int p)
{
    /*
     * This will increment your kills, start the attack thread,
     * and then it will return so the engine can call the eat function
     */
    if (env.map[p] != echar || env.map[p] != '#')
    {
        env.map[p] = env.grid[p] = echar;
        env.kills++;
    }
}
void eat(int p)
{
    /*
     * This function, will figure out how much health to take away,
     * take that from you, and do the stuff to add to your score,
     * then remove the object from the game. if the object is a life,
     * it wills start the thread to turn blue
     */
    bool ate = false;
    if (env.map[p] == '%')
    {
        env.health -= 5;
        env.score += targetnoms::SMALLBUG;
        ate = true;
        attack_color_change();
    }
    if (env.map[p] == '&')
    {
        env.health -= 4;
        env.score += targetnoms::LARGEBUG;
        ate = true;
        attack_color_change();
    }
    if (env.map[p] == '$')
    {
        env.health -= 3;
        env.score += targetnoms::WORM;
        ate = true;
        attack_color_change();
    }
    if (env.map[p] == '!')
    {
        env.health -= 25;
        env.score += targetnoms::PITBULL;
        ate = true;
        attack_color_change();
    }
    if (env.map[p] == '+')
    {
        env.lives++;
        ate = true;
        clrthread_lif *clrchg = new clrthread_lif;
        clrchg->Run();
    }
    if (env.map[p] == '@')
    {
        env.kills = env.kills_needed;
        ate = true;
    }
    if (ate)
        kill(p);
}
void attack(void)
{
    /*
     * This will attack an object that you point it at.
     * most of the work is done in the eat and kill functions
     * but this will figure every piece of math and stuff out
     * like where the object is, how much damage you do to it
     * how much damage it does to you, and if it is a zombie
     * it will call the respctive function (look in zombie.h)
     */
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
    if (env.view[location] == 'z')
    {
        t = character::ZOMBIE;
        gain = 0;
    }
    if (env.view[location] == '@') //eat the teleport
    {
        t = character::TELEPORT; //they have a strength of 0
        gain = targetnoms::TELEPORT;
        //env.score += gain;
    }
    if (env.view[location] == echar || env.view[location] == '#')
        return;
    int strength = (env.levels_completed * t) * env.difficulty;
    //cout << strength << endl; //debug
    int attack = env.attack;
    weapons::weaponlist weapon;
    weapons_init(weapon);
    attack *= weapon.strength[env.selectedweapon]; //add a little boost
    if (attack >= strength)
    {
        kill(location);
        env.score += gain;
    }
}
void increment_attack(void)
{
    /*
     * Called when you press 'E', it will figure out if you are
     * allowed to add to your attack, and if you are, it will take
     * from your health and add to your attack.
     */
    const int multiplier = 5;
    int divisor = ((1 + env.attack) * multiplier) + env.lives + env.health, increment = 1, total = env.health * env.lives;
    if (total / divisor > 1) //kgood
    {
        env.attack += increment;
        env.health -= total / divisor;
    }
}
void showweapons(void)
{
    /*
     * Weapons display function, weapons list is in the comment below this one
     * What this does is show the list of available weapons and which one is
     * selected will show up in red instead of your statusbar color.
     */
    //D(fist) x(throwing star) |(sword) ©(gun) {}(cannon) ~(laser)
    if (env.weapons[0])
    {
        if (env.selectedweapon == 0)
            colorify(RED);
        cout << "D ";
        colorify(NORMAL);
    }
    if (env.weapons[1])
    {
        if (env.selectedweapon == 1)
            colorify(RED);
        cout << "x ";
        colorify(NORMAL);
    }
    if (env.weapons[2])
    {
        if (env.selectedweapon == 2)
            colorify(RED);
        cout << "| ";
        colorify(NORMAL);
    }
    if (env.weapons[3])
    {
        if (env.selectedweapon == 3)
            colorify(RED);
        cout << "© ";
        colorify(NORMAL);
    }
    if (env.weapons[4])
    {
        if (env.selectedweapon == 4)
            colorify(RED);
        cout << "{} ";
        colorify(NORMAL);
    }
    if (env.weapons[5])
    {
        if (env.selectedweapon == 5)
            colorify(RED);
        cout << "~ ";
        colorify(NORMAL);
    }
}
void setselectedweapon(int w)
{
    /*
     * This will just select your weapon, but it is done in main.cpp
     * in the function game.
     */
    if (env.weapons[w])
        env.selectedweapon = w;
}