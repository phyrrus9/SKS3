/*
 * Super Key Seeker 4200 (Story Mode)
 * Copyright Ethan Laur 2011
 * Sequel will come sometime in the future ... nobody knows when ... but I know it wont be for a long time
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <fstream>
#define TEL "\033[22;31mt\e[m"
#include "maps.cpp"
#include <time.h>

#define builda "12d4"
#define buildb "2m6"
#define TEL "\033[22;31mt\e[m"
#define gametype "single"


using namespace std;

#include "engine.cpp"

int game(int blarg)
{
lvl = blarg;
system("clear");
  int ins = 1, yy = 1, xx = 10;
  string is[12] = {"[","      ","      ","      ","      ","      ","      ","      ","      ","      ","      ","]"};
  while (ins != 12)
  {
  system("clear");
  cout << "Time " << is[0] << is[1] << is[2] << is[3] << is[4] << is[5] << is[6] << is[7] << is[8] << is[9] << is[10] << is[11] << "[" << xx << "]" << endl << endl;
  cout << "Instructions!!!" << endl << "Use W A S D (lowercase) to move (you need to hit enter)" << endl << "To puck up/use something (k, c, s, b, B, ?), press 2 and then W A S D and press enter" << endl << "To attack (zombies, and one other secret thing) press 1 and then W A S D <enter>" << endl << "At any point in the game, you may use the 'save' command (press 3), which will give you a save code and exit  or the 'restore' command (press 4) to restore an old save" << endl << "GOOD LUCK!!!!!!" << endl;
  ins++;
  sleep(1);
  is[yy] = "######";
  yy++;
  xx--;
  }
sleep(0.9);
resetmap("Loading data");
system("clear");
stats();
radius();
while (i = 1) {
score = coins + (keys * 2) + deadzombies + (atk / 3 + def / 3) + (lvl * 3) + (awards * 2) + (walls / 15) * gam;
  if (atk >= 25 && redeemed[0] == false) {
    awards += 5;
    redeemed[0] = true;
    cout << "You just got an award!" << endl;
    sleep(3);
  }
  if (atk >= 30 && redeemed[1] == false) {
    awards += 10;
    redeemed[1] = true;
    cout << "You just got an award!" << endl;
    sleep(3);
  }
  if (atk >= 50 && redeemed[2] == false) {
    awards += 15;
    redeemed[2] = true;
    cout << "You just got an award!" << endl;
    sleep(3);
  }
  if (lvl >= 15 && redeemed[3] == false) {
    awards += 50;
    redeemed[3] = true;
    cout << "You just got an award!" << endl;
    sleep(3);
  }
  if (lvl >= 24 && redeemed[4] == false) {
    awards += 50;
    redeemed[4] = true;
    system("clear");
    cout << "You just got an award!" << endl;
    sleep(3);
  }
int i = 0;
string null;
if (health <= 0 && peaceful == false)
{
  system("clear");
  cout << endl << endl << "YOU ARE DEAD!!!" << endl << endl;
  int dead = score + health;
  if (dead <= 0)
    dead = 0;
  cout << "Your score was: " << dead << " Thank you for playing!" << endl;
  exit(0);
}

viewmap();
null = movest();
if ((null == "w") || (null == "a") || (null == "s") || (null == "d"))
  move(null);
if ((null == "2w") || (null == "2a") || (null == "2s") || (null == "2d") || (null == "2"))
  use(null);
if ((null == "1w") || (null == "1a") || (null == "1s") || (null == "1d"))
  attack(null);

} }

int main(int argc, char** argv)
{
bool repeat = true;
string cli;
if (argc != 1)
  cli = argv[1];
else
  cli = "0";
gam = atoi(cli.c_str());
printf("\e[m");
resetmap("Loading");
while (repeat)
{
repeat = false;
system("clear");
if (gam == 1)
printf("Welcome to Super Key Seeker 4200 (Story Mode) (build: [Engine: %s] [Game:  %s])\nYou are at the main menu, please select a difficulty:\n1. Easy\n2. Normal\n3. Hard\n4. Insane\n5. Suicidal\n6. Restore your old game (will work after updates)\n>", engine, builda);
if (gam == 2)
printf("Welcome to Super Key Seeker 3 alpha (build: [Engine: %s] [Game:  %s])\nYou are at the main menu, please select a difficulty:\n1. Easy\n2. Normal\n3. Hard\n4. Insane\n5. Suicidal\n6. Restore your old game (will work after updates)\n>", engine, buildb);
int null = 1;
cout << endl;
cin >> null;
if (null == 1)
{
  easy = true;
  health = 1000;
}
if (null == 2)
{
  normal = true;
  health = 100;
}
if (null == 3)
{
  hard = true;
  health = 75;
}
if (null == 4)
{
  insane = true;
  health = 50;
}
if (null == 5)
{
  health = 25;
  suicidal = true;
}
if (null == 6)
{
  restore();
  game(lvl);
}
system("clear");
if (null <= 6)
{
shealth = health;
game(0);
}
else
//main(cli.c_str());
repeat = true;
}
}
