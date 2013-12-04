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
 File: devmod.cpp
 Description: Function code for the developer mod system. See file
 devmod.h for information
 Authors: phyrrus9 <phyrrus9@gmail.com>
 *****************************************************************/
#include "devmod.h"
void mod_init(void)
{
    printf("mod_init called\n");
    readmods(env.modlist);
}

void readmods(developermod *modlist)
{
    char *filename = new char[50];
    char *modnameid = new char[30];
    char *modfilename = new char[75];
    int modtypeid;
    strcpy(filename, "/usr/share/sks3/mods.conf");
    FILE *modfile;
    modfile = fopen(MODFILE_LOCATION, "r");
    int loop = 0;
    int *modcount = &env.modcount; //make a local variable
    if (modfile == NULL)
    {
        //file does not exist, no developer mods
        *modcount = 0;
        modlist = new developermod;
        return;
    }
    env.developer_mode = true; //enable developer mode
    fscanf(modfile, "%d\n", modcount);
    printf("modcount: %d\n", *modcount);
    //modlist = new developermod[*modcount + 1];
    loop = 0;
    while (fscanf(modfile, "%d", &modtypeid) != EOF && loop < *modcount && *modcount != 0)
    {
        modlist[loop].type = (modtype)modtypeid;
        //printf("Type: %d\n", modlist[loop].type);
        fscanf(modfile, "%s", modnameid);
       // printf("Name: %s\n", modnameid);
        fscanf(modfile, "%s", modfilename);
        //printf("File: %s\n", modfilename);
        strcpy(modlist[loop].name, modnameid);
        strcpy(modlist[loop].filename, modfilename);
        modlist[loop].enabled = false;
        modlist[loop].constant = false;
        loop++;
    }
    fclose(modfile);
    
}

void enablemod(int modnum, bool override)
{
    FILE *modfile;
    modfile = fopen(env.modlist[modnum].filename, "r");
    if (modfile == NULL)
    {
        printf("MOD ERROR!\n");
        //file does not exist like it is supposed to
        return;
    }
    bool execute = true;
    switch (env.modlist[modnum].type)
    {
        case NOMOD:
            return;
            break;
        case ENVMOD:
        case GAMEMOD:
            char *field = new char[30];
            while (fscanf(modfile, "%s :", field) != EOF)
            {
                //printf("field: %s\n", field);
                int *booltmp;
                //parse the field
#define fieldparse(a) if (strcmp(field, a) == 0)
#define readbool(a, b) booltmp = new int; \
                       fscanf(a, "%d", booltmp);\
                       b = *booltmp == 1 ? 1 : 0;\
                       delete booltmp;
                if (strcmp(field, "endif") == 0)
                {
                    execute = true;
                }
                if (execute == false)
                {
                    continue;
                }
                fieldparse("developer_mode")
                {
                    //printf("developer_mode\n");
                    readbool(modfile, env.developer_mode);
                }
                fieldparse("cheats")
                {
                    //printf("cheats\n");
                    readbool(modfile, env.cheats);
                }
                fieldparse("health")
                {
                    //printf("health\n");
                    fscanf(modfile, "%d", &env.health);
                }
                fieldparse("lives")
                {
                    //printf("lives\n");
                    fscanf(modfile, "%d", &env.lives);
                }
                fieldparse("enginecmd")
                {
                    std::string command;
                    std::string parameter;
                    char command_c[30], parameter_c[30];
                    fscanf(modfile, "%s %s", command_c, parameter_c);
                    command = command_c;
                    parameter = parameter_c;
                    enginecmd(command, parameter, true);
                }
                if (strcmp(field, "increment") == 0 || strcmp(field, "decrement") == 0)
                {
                    /*
                     * ++ or -- operators for health, lives, attack, and needed kills
                     */
                    int inc_level = 1;
                    if (strcmp(field, "decrement") == 0)
                    {
                        inc_level = -1;
                    }
                    char inc_field[30];
                    fscanf(modfile, "%s", inc_field);
                    int *ptr;
#define increment(a,b); if (strcmp(inc_field, a) == 0) { ptr = &b; }
                    increment("env->health", env.health);
                    increment("env->lives", env.lives);
                    increment("env->attack", env.attack);
                    increment("env->kills_needed", env.kills_needed);
                    *ptr = *ptr + inc_level;
                }
                //below are the map management functions
                fieldparse("zombie")
                {
                    int spawn_location;
                    fscanf(modfile, "%d", &spawn_location);
                    if (spawn_location <= 0)
                    {
                        srand((unsigned int)time(0));
                        spawn_location = rand() % 890 + 3;
                    }
                    env.map[spawn_location] = env.grid[spawn_location] = 'z';
                    env.map[0] = env.grid[0] = '~'; //bigfix?
                    zombie z(spawn_location);
                }
                fieldparse("map") //set a location of the map
                {
                    int map_location;
                    char map_display;
                    fscanf(modfile, "%d %c", &map_location, &map_display); // map <location> <display>
                    env.map[map_location] = env.grid[map_location] = map_display;
                }
                fieldparse("maprange") //set a large range of map data
                {
                    int map_start = 0, map_end = 0;
                    char map_display;
                    fscanf(modfile, "%d-%d %c", &map_start, &map_end, &map_display); // map <range> <value>
                    for (int i = map_start; i <= map_end; i++)
                    {
                        env.map[i] = env.grid[i] = map_display;
                    }
                }
                //misc below
                fieldparse("//") //comment
                {
                    char comment_tmp = 0;
                    while (fscanf(modfile, "%c", &comment_tmp) != EOF && comment_tmp != '\n') {}
                }
                fieldparse("global")
                {
                    char global[15];
                    fscanf(modfile, "%s", global);
                    if (strcmp(global, "noblock") == 0)
                    {
                        env.modlist[modnum].enabled = false; //allow enabling again
                    }
                    if (strcmp(global, "constant") == 0)
                    {
                        env.modlist[modnum].constant = true; //auto-enable
                    }
                    if (strcmp(global, "gamemode") == 0)
                    {
                        fscanf(modfile, "%s", env.modification_settings.game_mode); //allow the developer to set the game mode
                                                                                    //found in the highscore list
                    }
                }
                fieldparse("endgame")
                {
                    env.health = -1;
                    env.lives = -1;
                }
                if (!override) //basically, require only works on first try
                fieldparse("require")
                {
                    /*
                     * "require" allows you to set depends on mods. This is very useful
                     * for defining custom game modes (that will rewrite the entire map)
                     * currently, the format is as follows:
                     * require <field> <operator> <value>
                     * fields are as follows:
                     * env->position (the location of the player)
                     * env->cheats (1=on, 0=off [status])
                     * operators are as follows:
                     * = (equals)
                     * < (less than, not equal to)
                     * > (greater than, not equal to)
                     * values are integers
                     */
                    char depend[15], dep_op;
                    fscanf(modfile, "%s %c", depend, &dep_op);
                    /*FILE *f = fopen("log_.txt", "w");
                    fprintf(f, "Require: %s \n", depend);
                    fclose(f);*/
                    /* checkdepends, failure condition */
#define checkdepends(a, b, c)\
if  (\
        (a != c && b == '=') ||\
        (a < c && b == '>') ||\
        (a > c && b == '<')\
    )
                    if (strcmp(depend, "env->position") == 0)
                    {
                        int tmp_value = 0;
                        fscanf(modfile, "%d", &tmp_value);

                        checkdepends(env.position, dep_op, tmp_value)
                        {
                            printf("DEPEND ERROR\n");
                            env.modlist[modnum].enabled = false;
                            return;
                        }
                    }
                    if (strcmp(depend, "env->cheats") == 0)
                    {
                        int tmp_value = 0;
                        fscanf(modfile, "%d", &tmp_value);
                        
                        checkdepends(env.cheats, dep_op, tmp_value)
                        {
                            printf("DEPEND ERROR\n");
                            env.modlist[modnum].enabled = false;
                            return;
                        }
                    }
                }
                fieldparse("if")
                {
                    // stub (future completion)
#define checkif(a,b,c) checkdepends(a,b,c)
                    char condition[15], if_op;
                    int if_value = 0;
                    fscanf(modfile, "%s %c %d", condition, &if_op, &if_value);
                    if (strcmp(condition, "env->lc") == 0)
                    {
                        checkif(env.levels_completed, if_op, if_value) { execute = false; }
                        else { execute = true; }
                    }
					if (strcmp(condition, "env->cheats") == 0)
					{
						checkif(env.cheats, if_op, if_value) { execute = false; }
						else { execute = true; }
					}
					if (strcmp(condition, "env->health") == 0)
					{
						checkif(env.cheats, if_op, if_value) { execute = false; }
						else { execute = true; }
					}
					if (strcmp(condition, "env->lives") == 0)
					{
						checkif(env.cheats, if_op, if_value) { execute = false; }
						else { execute = true; }
					}
					if (strcmp(condition, "env->attack") == 0)
					{
						checkif(env.cheats, if_op, if_value) { execute = false; }
						else { execute = true; }
					}
                }
            }
            break;
    }
}

void rerunmods(developermod *modlist)
{
    /*
     * Simple function to run through the list of mods and
     * re run those that are static (like custom game modes)
     * First appear in version 3.0.2
     */
    for (int i = 0; i < 10; i++)
    {
        if (modlist[i].constant)
        {
            enablemod(i, true);
        }
    }
}