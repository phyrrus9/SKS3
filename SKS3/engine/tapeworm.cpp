/*****************************************************************
 Super Key Seeker Version 3
 Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 This software is free, it may be customized, redistributed
 or used in any way that suits your needs. This software is
 open source, meaning that it MUST be distributed along with
 its source code or have provisions to recieve the source code
 if desired. This program, though it is free and open source
 is still copyright © the following names and companies:
 Ethan Laur (phyrrus9) <phyrrus9@gmail.com> 2012
 MOD Technologies LLC <http:modtech.co> 2012
 This program source code MUST be distributed with this comment
 block intact as a reference to users who would actually like
 to follow the rules. Please do not be a jerk and take credit
 for a program you did not write. This code for the most part
 was written by the following people and companies:
 Ethan Laur (phyrrus9) <phyrrus9@gmail.com>
 Dereck Wonnacott <dereck@gmail.com>
 GNU Project (for ncurses which we all so dearly love)
 All third party lisencing by the above authors is transmitted
 with the source code of this program to its new author, who
 may add his or her name to this block for the works they did
 It is greatly appreciated if any work you do on the program
 is reported back to the original authors (copyright section)
 so that we can incorporate your features into the game as a
 public release. We thank you for reading this file.
 If you want to know how many lines of code are in this project,
 you can just cd into the source directory and run the following
 find . -type f -print0 | xargs -0 cat | wc -l
 =================================================================
 File: tapeworm.h
 Description: Function prototypes for checking tapeworm locations,
 doing damage to players.
 Authors: phyrrus9 <phyrrus9@gmail.com>
 *****************************************************************/
#include "tapeworm.h"
void tapeworm(int position)
{
    /*
     * This function will eventually be used for something
     */
    env.grid[position] = env.map[position] = '-';
}

void do_disease_damage(void)
{
    long t = time(0);
    switch (env.disease_level)
    {
        case weapons::NONE:
            return;
            break;
        case weapons::STAGE1:
            if (t % 2 == 0) //every 2 mins
            {
                env.health--;
            }
            break;
        case weapons::STAGE2:
            if (t % 59 == 0) //~ 1 min
            {
                env.health--;
            }
            break;
        case weapons::STAGE3:
            if (t % 30 == 0) //every 30 secs
            {
                env.health -= 2;
            }
            break;
        case weapons::STAGE4:
            if (t % 30 == 0) //same
            {
                env.health -= 5;
            }
            break;
        case weapons::TERMINAL:
            if (t % 15 == 0) //every 15 secs
            {
                env.health -= 5;
            }
            break;
        case weapons::DEATH:
            env.health -= 5; //every second
            env.statuscolor = RED;
            break;
    }
    if (env.health < 0)
    {
        if (env.lives > 0)
        {
            env.health = 100;
            env.lives--;
        }
        else
        {
            move(NIL);
        }
    }
}

void increment_disease(weapons::_disease_level *t)
{
    //user_status *s = new user_status("Your disease has advanced!");
    if (env.disease_level == weapons::NONE)
        *t = weapons::STAGE1;
    else if (env.disease_level == weapons::STAGE1)
        *t = weapons::STAGE2;
    else if (env.disease_level == weapons::STAGE2)
        *t = weapons::STAGE3;
    else if (env.disease_level == weapons::STAGE3)
        *t = weapons::STAGE4;
    else if (env.disease_level == weapons::STAGE4)
        *t = weapons::TERMINAL;
    else
        return;
}
