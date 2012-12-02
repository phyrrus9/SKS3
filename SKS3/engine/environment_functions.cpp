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
 File: environment_functions.cpp
 Description: Called in the main function of the program, sets up
 things to do with the environment structure, timer class, and
 other threadding stuff... Pretty basic but it is the single most
 important file in this whole program. If the init function were
 to break then you will end up corrupting the game and bad stuff
 will happen and you will probably be killed in your sleep by a
 pack of wile bigfoots.
 Authors: phyrrus9 <phyrrus9@gmail.com>
 *****************************************************************/
#include "environment_functions.h"
void environment_init(_environment &t)
{
    /*
     * This function just sets up the initial environment
     * variables in their default values. It needed to be
     * a function instead of static initializations because
     * it would not compile for any system other than mac os x
     * that way, and even then it threw a few hundred warnings.
     */
    /* BEGIN DEVELOPER STUFF */
    mod_init();
    /* END DEVELOPER STUFF */
    strcpy(t.version, VERSION_BUILD);
    t.zombies = 0;
    t.paused = false;
    t.music = true;
    t.socket_paused = false;
    t.multiplayer = false;
    t.time_up = false;
    t.number_of_songs = 0;
    strcpy(t.map, "\0");
    strcpy(t.grid, "\0");
    t.showmap = true;
    t.single = false;
    t.cheats = false;
    t.refresh_screen = true;
    t.allow_refresh = true;
    //weapons
    t.weapons[0] = true;
    for (int i = 1; i < 6; i++)
        t.weapons[i] = false;
    //integers
    t.health = 100;
    t.lives = 3;
    t.score = 0;
    t.position = 0;
    t.moves = 1;
    t.kills = 0;
    t.kills_needed = 0;
    t.total_enemies = 0;
    t.levels_completed = 0;
    t.attack = 1;
    t.totalscore = 0;
    t.selectedweapon = 0;
    t.keys = 0;
    //savedata
    t.savefile = "save.dat";
    //character stuff
    t.bgcolor = NORMAL;
    t.playercolor = RED;
    t.statuscolor = NORMAL;
    t.player = character::N;
    t.difficulty = character::NORMAL; //set it this for now
    //socket init
    strcpy(t.socket_message, "\251");
    //zombie globals
    t.min_zombie_does_damage_level = 5;
    t.zombies_do_damage = true;
    //game timer stuffs
    game_timer_init(t.timer);
    //high score stuff
    hiscore::get_scores();
    //settings stuff
    settings_init(t.settings);
    
    //devel mode
    t.developer_mode = false;
    //simple score mod
    t.score_multiplier = 1;
    //more devel mode stuff
    t.can_enable_developer_mode = false;
    //prevent competition cheating
    t.competition_mode = false;
    //autosaves
    t.allow_autosave = true;
    //3.0.1 modifications
    //t.modcount = 0;
}

void weapons_init(weapons::weaponlist &t)
{
    /*
     * This just initializes the strength array for weapons
     * its here because it cant be initialized in a header file
     */
    //{ 2, 4, 8, 16, 32, 64 }
    for (int i = 0, j = 2; i < weapons::num_of_weapons; i++, j *= 2) //all powers of two
        t.strength[i] = j; //its all easier this way for adding say 128 weapons :P
}

class timer_thread : public tpool::Thread
{
    /*
     * This thread runs CONSTANTLY in the background, NO exceptions
     * all it does is count, literally. This is a timer, we use it to
     * track how many points to take off a user's score every ten seconds
     */
    virtual void Entry(void)
    {
        int count = 0;
        while (true)
        {
            if (env.timer.clock >= time_limit) //1 hour of game play
                env.time_up = true;
            sleep(1);
            if (env.moves > 1)
            {
                if (!env.paused)
                {
                    //env.score -= env.timer.clock;
                    game_timer_increment(env.timer);
                    env.refresh_screen = true;
                }
            }
            else 
            {
                env.timer.second = env.timer.minute = 0;
                //env.timer.clock /= 5;
            }
            env.totalscore = (((((env.score * (env.levels_completed * 2)) + (env.health / 3)) + env.kills) + env.lives) - (env.moves / 30) - ((env.timer.clock / 10) * env.levels_completed)) + (env.keys * 2);
            //figured i would do this here
            if (env.totalscore < 0)
                env.totalscore = 0;
            count++;
            if (count == 2)
            {
                env.refresh_screen = true;
                count = 0;
            }
        }
    }
};

void game_timer_init(game_timer &t)
{
    /*
     * Initialize the game timer to 00:00/0
     */
    t.second = t.minute = t.clock = 0;
    timer_thread *env_timer_thread = new timer_thread;
    env_timer_thread->Run();
}

void game_timer_increment(game_timer & t)
{
    /*
     * Increment by 00:01/1
     * if the seconds is more than xx:59/x, add 1 to the minutes
     */
    t.second++;
    t.clock++;
    if (t.second >= 60)
    {
        t.minute++;
        autosave();
        t.second = t.second - 60;
    }
}

void settings_init(_settings & t)
{
    t.keys.attack = 'e';
    t.keys.pause = 'p';
    t.keys.quit = 'Q';
    t.keys.engine = '/';
    t.keys.w = 'w';
    t.keys.a = 'a';
    t.keys.s = 's';
    t.keys.d = 'd';
    t.keys.i = 'i';
    t.keys.j = 'j';
    t.keys.k = 'k';
    t.keys.l = 'l';
    t.keys.S = 'S';
    t.keys.R = 'R';
    t.keys.ss = '@';
    t.keys.rs = '#';
    t.keys.settings = '+';
    t.zombie.zombie_active = 4;
    settings_read();
}

void competition_init(_competition &t)
{
    t.number = 0;
    strcpy(t.password, "inactive");
}