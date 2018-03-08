//
//  dragon.cpp
//  SKS3
//
//  Created by Ethan Laur on 3/27/13.
//
//

#include "dragon.h"

/*
 class dragon
 {
 int position;
 int strength;
 int attack;
 int hits_taken;
 public:
 dragon(int position);
 dragon(int position, int strength);
 dragon(int position, int strength, int attack);
 void hit(void);
 void blowback(void);
 void die(void); //for developer stuff
 };
*/

dragon::dragon(void)
{
    // dragons broken atm... will fix this sh** someday..
    //dragon(rand() % 899 + 1);
}

dragon::dragon(int position)
{
    dragon(position, rand() % 32 + 1, rand() % 32 + 1);
}

dragon::dragon(int position, int strength)
{
    dragon(position, strength, rand() % 32 + 1);
}

dragon::dragon(int position, int strength, int attack)
{
    if (env.dragon_data.number_of_dragons > 9)
        return;
    internal_dragon_data.position = position;
    //internal_dragon_data.strength;
    internal_dragon_data.attack = attack;
    env.map[internal_dragon_data.position] = env.grid[internal_dragon_data.position] = 'd';
    env.dragon_data.number_of_dragons++;
    /*env.dragon_data.backup_db[env.dragon_data.number_of_dragons].attack = internal_dragon_data.attack;
    env.dragon_data.backup_db[env.dragon_data.number_of_dragons].position = internal_dragon_data.position;
    env.dragon_data.backup_db[env.dragon_data.number_of_dragons].strength = internal_dragon_data.strength;*/
}

/*dragon::dragon(dragon &old)
{
    internal_dragon_data.position   = old.internal_dragon_data.position;
    internal_dragon_data.strength   = old.internal_dragon_data.strength;
    internal_dragon_data.attack     = old.internal_dragon_data.attack;
    internal_dragon_data.hits_taken = old.internal_dragon_data.hits_taken;
}*/

void dragon::hit(void)
{
    user_status *s = new user_status("Hit a dragon!");
    internal_dragon_data.hits_taken++;
    internal_dragon_data.strength -= env.attack;
    if (internal_dragon_data.strength <= 0)
    {
        die();
        return;
    }
    //blowback();
}

void dragon::blowback(void)
{
    env.health -= internal_dragon_data.attack;
}

void dragon::die(void)
{
    env.map[internal_dragon_data.position] = env.grid[internal_dragon_data.position] = echar;
}

void dragon::eaten(void)
{
    env.score /= 3;
    env.health /= 3;
    env.lives /= 3;
    //yeah, big penalty
}

int dragon::getposition(void)
{
    return internal_dragon_data.position;
}

int find_dragon(int location) //find the dragon in the db
{
    for (int i = 0; i < 10; i++)
    {
        if (env.dragons[i].getposition() == location)
        {
            return i;
        }
    }
    return -1;
}
