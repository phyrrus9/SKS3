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

/*
struct _internal_dragon_data
{
    int position;
    int strength;
    int attack;
    int hits_taken;
};
*/

//don't judge me here
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


dragon::dragon(void)
{
    // dragons broken atm... will fix this sh** someday..
    dragon(rand() % 899 + 1);
}

dragon::dragon(dragon &old)
{
	internal_dragon_data.position = old.internal_dragon_data.position;
	internal_dragon_data.strength = old.internal_dragon_data.strength;
	internal_dragon_data.attack = old.internal_dragon_data.attack;
	internal_dragon_data.hits_taken = old.internal_dragon_data.hits_taken;
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
    internal_dragon_data.strength;
    internal_dragon_data.attack = attack;
    //env.map[internal_dragon_data.position] = env.grid[internal_dragon_data.position] = 'd';
    env.dragon_data.backup_db[env.dragon_data.number_of_dragons].attack = internal_dragon_data.attack;
    env.dragon_data.backup_db[env.dragon_data.number_of_dragons].position = internal_dragon_data.position;
    env.dragon_data.backup_db[env.dragon_data.number_of_dragons].strength = internal_dragon_data.strength;
    env.dragon_data.number_of_dragons++;
}

void dragon::init(int position, int strength, int attack)
{
    if (position == 0 && strength == 0 && attack == 0)
    {
	position = rand() % 899 + 1;
	strength = rand() % 32 + 1;
	attack = rand() % 32 + 1;
    }
    internal_dragon_data.position = position;
    internal_dragon_data.strength = strength;
    internal_dragon_data.attack = attack;
    env.map[internal_dragon_data.position] = env.grid[internal_dragon_data.position] = 'd';
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
    clrthread_atk *clrchg = new clrthread_atk;
    clrchg->Run();
    user_status *s = new user_status("Hit a dragon!");
    internal_dragon_data.hits_taken++;
    internal_dragon_data.strength -= env.attack;
    if (internal_dragon_data.strength <= 0)
    {
        die();
        return;
    }
    blowback();
}

void dragon::blowback(void)
{
    env.health -= internal_dragon_data.attack;
}

void dragon::die(void)
{
    user_status *s = new user_status("Killed a dragon!");
    clrthread_lif *clrchg = new clrthread_lif;
    clrchg->Run();
    env.score += 20000;
    env.health += internal_dragon_data.position + internal_dragon_data.attack;
    env.map[internal_dragon_data.position] = env.grid[internal_dragon_data.position] = echar;
}

void dragon::eaten(void)
{
    user_status *s = new user_status("That fucking hurts!");
    clrthread_atk *clrchg = new clrthread_atk;
    clrchg->Run();
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
