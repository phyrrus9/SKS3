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
 File: hiscore.cpp
 Description: Functions to display fetch save and sort high scores
 Authors: phyrrus9 <phyrrus9@gmail.com>
 *****************************************************************/
#include "hiscore.h"
namespace hiscore
{
    /*
     * The reason I want to use this in another
     * namespace is because I will be using a
     * lot of the same function names with
     * almost no difference and while the
     * compiler would be able to tell the difference
     * you probably wouldn't be, so this just
     * makes it a little bit better on you.
     */
    void get_scores(void)
    {
        /*
         * This function will read the high scores
         * savefile, and create a new initialized
         * one if it does not exist and load the
         * names and scores into the environment
         * so they can be shown on screen.
         */
        ifstream hs_fstream(".sks3-hiscores", ios::binary); //open the high score file
        if (!hs_fstream) //file not there
        {
            ofstream hs_ofstream(".sks3-hiscores", ios::binary | ios::trunc); //create a blank file
            if (!hs_ofstream)
                exit(-1);
            for (int i = 0; i < hiscore::num_scores; i++)
            {
                strcpy(env.hiscorelist[i].name, "NAME");
                env.hiscorelist[i].score = 50;
                hs_ofstream.write((char *)(&env.hiscorelist[i]), sizeof(hiscore::score)); //binary write
            }
            hs_ofstream.close();
            hs_fstream.seekg(ios::beg); //so we can re-read the file if the pointer changed
        }
        for (int i = 0; i < hiscore::num_scores; i++) //loop through all scores
        {
            hs_fstream.read((char *)&env.hiscorelist[i], sizeof(hiscore::score)); //read it into env
        }
        hiscore::bobble_sort(); //sort them
    }
    void bobble_sort(void)
    {
        /*
         * You will find this function in a lot
         * of places in c++ programming, it is
         * the bubble sort algorithm, meaning
         * that it will run through the list
         * and sort it into ascending order for
         * us so we dont need to do it manually
         * There are many other faster ways to
         * do the same thing (binary sort) but
         * this was just the fastest thing I
         * could write given the ammount of time
         * that I actually spent writing the
         * algorithm vs the ammount of bugs the
         * high score system added that I needed
         * to fix before I could release 1.7
         */
        
        for(int i = 0; i < num_scores; i++)
        {
            for(int j = 0; j < i; j++)
            {
                if(env.hiscorelist[i].score > env.hiscorelist[j].score)
                {
                    int temp = env.hiscorelist[i].score; //swap
                    env.hiscorelist[i].score = env.hiscorelist[j].score;
                    env.hiscorelist[j].score = temp;
                    char temp_c[15];
                    strcpy(temp_c, env.hiscorelist[i].name); //swap
                    strcpy(env.hiscorelist[i].name, env.hiscorelist[j].name);
                    strcpy(env.hiscorelist[j].name, temp_c);
                }
                
            }
            
        }
    }
    void save(void)
    {
        /*
         * Simpler function than the rest, but
         * very useful in purpose. This will
         * binary write all of the data in the
         * current environment to the high score
         * savefile. This can be used in a few
         * ways but I wont spoil the suprise
         */
         
        ofstream f(".sks3-hiscores", ios::trunc | ios::binary);
        for (int i = 0; i < num_scores; i++) //loop through all data in env
            f.write((char *)(&env.hiscorelist[i]), sizeof(hiscore::score)); //binary write
    }
    void display(void)
    {
        /*
         * Function to display the high scores on
         * the user's screen. Pretty basic but for
         * the longest period of time I could not
         * for the life of me figure out how to
         * use the setw(), right, and setfil()
         * functions so if you are a beginner I
         * suggest you stay away from this func.
         */
        
        get_scores(); //re-read in case of a bad save
        env.allow_refresh = false;
        //clear();
        cout << setw(7) << "Name" << setw(9) << right << "Score" << endl << left
        << setw(18) << setfill('#') << "" << endl << setfill(' ');
        for (int i = 0; i < num_scores; i++)
        {
            cout << setw(7) << env.hiscorelist[i].name << setw(9) << right << env.hiscorelist[i].score << endl << left;
        }
        cout << "Press any key to continue..." << endl;
        getch_();
        env.allow_refresh = true;
    }
    void user_save(void)
    {
        /*
         * Ask the user for his name and
         * add him to the list in the
         * environment so we can save
         */
        
        env.allow_refresh = false;
        small_delay();
        endwin(); //because it wont read if we dont
        //clear();
        cout << "Please enter your name: ";
        char name[15];
        cin >> name;
        env.allow_refresh = true;
        //cin.getline(name, 10, '\n'); //prevent an overflow
        int location = -1;
        for (int i = 0; i < hiscore::num_scores; i++)
        {
            if (env.totalscore > env.hiscorelist[i].score)
                location = i;
        }
        if (location != -1)
        {
            strcpy(env.hiscorelist[location].name, name);
            env.hiscorelist[location].score = env.totalscore;
            hiscore::save();
        }
    }
}