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
 *****************************************************************/
#include "zombie.h"
bool zombiecheck(int p)
{
    /*
     * This function just checks to see if there
     * is a zombie at location p, if there is, it
     * returns that there is one and it is processed
     * in some other function.
     */
    if (env.map[p] == 'z')
        return true;
    return false;
}
void do_zombie_damage(void)
{
    /*
     * This function does the damage a zombie would
     * do to you if you were to
     * 1.) run on top of it
     * 2.) eat it without killing it
     * 3.) run away from it
     * 4.) run by it
     */
    if (env.zombies_do_damage)
        if (env.levels_completed >= env.min_zombie_does_damage_level)
            env.health = env.health - ((env.position / 3) - (env.levels_completed + env.attack));
}

void zombie_thread::Entry(void)
{
    /*
     * This is a set of threads that will
     * control the AI of the zombies which
     * are actually not that intelligent
     * but do their job just fine... if
     * I was you I would stay out of this
     * thread
     */
    sleep(2); //make sure the user moves out of the way first
    while (true)
    {
        if (env.map[location] == echar)
            return;
        bool moved = false;
        while (!moved)
        {
            if (env.paused)
                break;
            int seed = (env.timer.clock % 4) + 1;
            int offset = 0;
            switch (seed)
            {
                case 1:
                    offset = -30;
                    break;
                case 2:
                    offset = 30;
                    break;
                case 3:
                    offset = -1;
                    break;
                case 4:
                    offset = 1;
                    break;
            }
            if (env.view[location + offset] == echar)
            {
                env.map[location] = env.grid[location] = echar;
                location += offset;
                env.map[location] = env.grid[location] = 'z';
                //env.refresh_screen = true;
                moved = true;
            }
            if (env.view[location + offset] == env.position)
            {
                do_zombie_damage();
                moved = true;
            }
        }
        sleep(2); //a small delay
    }
}
zombie::zombie(int t)
{
    /*
     * Constructor for a new active
     * zombie, will set up a thread
     * at that location and start it
     * see the threadcode above for
     * the whole code
     */
    zthread = new zombie_thread;
    zthread->location = t;
    zthread->Run();
}