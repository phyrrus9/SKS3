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
        loop++;
    }
    fclose(modfile);
    
}

void enablemod(int modnum)
{
    FILE *modfile;
    modfile = fopen(env.modlist[modnum].filename, "r");
    if (modfile == NULL)
    {
        printf("MOD ERROR!\n");
        //file does not exist like it is supposed to
        return;
    }
    switch (env.modlist[modnum].type)
    {
        case NOMOD:
            return;
            break;
        case ENVMOD:
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
            }
            break;
    }
}