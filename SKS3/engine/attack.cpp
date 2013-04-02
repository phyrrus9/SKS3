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
 File: attack.cpp
 Description: This stuff all relates to what happens when you press
 the attack key, including threads for changing the statusbar color
 when you take damage or gain life. Very important stuff here as it
 has complete control over the map.
 Authors: phyrrus9 <phyrrus9@gmail.com>
 *****************************************************************/
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
        env.score += targetnoms::SMALLBUG * env.score_multiplier;
        ate = true;
        attack_color_change();
    }
    if (env.map[p] == '&')
    {
        env.health -= 4;
        env.score += targetnoms::LARGEBUG * env.score_multiplier;
        ate = true;
        attack_color_change();
    }
    if (env.map[p] == '$')
    {
        env.health -= 3;
        env.score += targetnoms::WORM * env.score_multiplier;
        ate = true;
        attack_color_change();
    }
    if (env.map[p] == '!')
    {
        env.health -= 25;
        env.score += targetnoms::PITBULL * env.score_multiplier;
        ate = true;
        attack_color_change();
    }
    if (env.map[p] == 'z')
    {
        env.score += 5 * env.score_multiplier; //yes, I know its cheap
                        //but it has to be done
        attack_color_change();
        ate = true;
    }
    if (env.map[p] == 'g')
    {
        env.health -= 100; //take an entire life
        env.score += (targetnoms::GAURD * env.score_multiplier) / 3;
        attack_color_change();
        ate = true;
    }
    if (env.map[p] == 'b')
    {
        env.lives -= 2;
        env.score += (targetnoms::BOSS * env.score_multiplier) / 2;
        attack_color_change();
        ate = true;
    }
    if (env.map[p] == '-')
    {
        env.tapeworm_count++;
        ate = true;
        user_status *s = new user_status("Oh no, you got tapeworm!");
    }
    /*
     * The following statements are used for special characters
     * these do not have the standard effect as they do the
     * rest of attacks and eats
     */
    if (env.map[p] == '+')
    {
        env.lives += 1; //bug fix
        ate = true;
        clrthread_lif *clrchg = new clrthread_lif;
        clrchg->Run();
        if (env.tapeworm_count > 0)
        {
            env.tapeworm_count--;
            user_status *s = new user_status("Cleaned 1 tapeworm");
        }
    }
    if (env.map[p] == '@')
    {
        env.kills = env.kills_needed;
        ate = true;
    }
    if (env.map[p] == 'k')
    {
        env.keys++;
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
        attack_color_change();
    }
    if (env.view[location] == '&')
    {
        t = character::LARGEBUG;
        gain = targetnoms::LARGEBUG;
        attack_color_change();
    }
    if (env.view[location] == '$')
    {
        t = character::WORM;
        gain = targetnoms::WORM;
        attack_color_change();
    }
    if (env.view[location] == '!')
    {
        t = character::PITBULL;
        gain = targetnoms::PITBULL;
        attack_color_change();
    }
    if (env.view[location] == 'z')
    {
        t = character::ZOMBIE;
        gain = 0;
        attack_color_change();
    }
    if (env.view[location] == 'g')
    {
        t = character::GAURD;
        gain = targetnoms::GAURD;
        attack_color_change();
    }
    if (env.view[location] == 'b')
    {
        t = character::BOSS;
        gain = targetnoms::BOSS;
        attack_color_change();
    }
    if (env.view[location] == '@') //eat the teleport
    {
        t = character::TELEPORT; //they have a strength of 0
        gain = targetnoms::TELEPORT;
    }
    if (env.view[location] == 'k') //eat a key
    {
        t = character::TELEPORT; //strength of 0
        gain = 0;
        env.keys++;
    }
    if (env.view[location] == 'd')
    {
        if (find_dragon(location) == -1)
            user_status *s = new user_status("Error cannot find dragon!");
        else
            env.dragons[find_dragon(location)].hit();
    }
    if (env.view[location] == 'M')
    {
        env.map[location] = env.grid[location] = echar;
        //t = character::NIL;
        int key = rand() % question::question_count;
        env.allow_refresh = false;
        clear();
        printf("You have found a mystery box!\r\n"
               "Health: %d\tLives : %d\r\n"
               "Score : %d\tAttack: %d\r\n"
               "%s\n%s\n>",
               question::gains[key].health,
               question::gains[key].lives,
               question::gains[key].score,
               question::gains[key].attack,
               question::instructions[key],
               question::questions[key]);
        char q_answer[50];
        //cin.getline(q_answer, 49, '\n');
        cin.getline(q_answer, 49);
        //env.allow_refresh = true;
        if (strcmp(q_answer, question::answers[key]) == 0)
        {
            printf("You got it right! Here is your reward:\r\n");
            env.health += question::gains[key].health;
            env.lives += question::gains[key].lives;
            env.score += question::gains[key].score;
            env.attack += question::gains[key].attack;
        }
        else
        {
            printf("Sorry, you got it wrong!\n"
                   "Press any key to continue...");
        }
        //getch_();
        env.allow_refresh = true;
    }
    if (env.view[location] == echar || env.view[location] == '#')
        return;
    int strength = (env.levels_completed * t) * (env.difficulty);
    //FILE *f = fopen("_log.txt", "wa");
    //fprintf(f, "Strength: %d lc: %d t: %d diff: %d\n", strength, env.levels_completed, t, env.difficulty);
    //fclose(f);
    int attack = env.attack;
    weapons::weaponlist weapon;
    weapons_init(weapon);
    attack *= weapon.strength[env.selectedweapon]; //add a little boost
    if (attack >= strength)
    {
        kill(location);
        env.score += gain;
    }
    else
    {
        eat(location);
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
    if (env.weapons[6])
    {
        if (env.selectedweapon == 6)
            colorify(RED);
        cout << "√ ";
        colorify(NORMAL);
    }
    if (env.weapons[7])
    {
        if (env.selectedweapon == 7)
            colorify(RED);
        cout << "ø ";
        colorify(NORMAL);
    }
}
void showweaponsv3(uiwindow w)
{
    
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