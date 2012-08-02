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
 *****************************************************************
 Super Key Seeker 4200, a simple text based game written for UNIX
 systems. This game is copyright © 2011 Ethan Laur (phyrrus9)
 This software is open source, meaning that any distribution of it
 must include this code along with the binary file or give access
 to it by a simple means. Any derivitive work of this software must
 carry this block of code to tell who the original authors are and
 also a list of changes made by the third party and contact details
 so that other parties may reach them for help about their code.
 Other people who significantly contributed to this project are
 listed below, and are required by this copyright to remain in
 this way as long as this code is distributed for public use.
 Dereck Wonnacott <dereck@gmail.com> for examples and snippets
 The GNU Project <http://gnu.org> for ncurses
 ****************************************************************/

/*
 * Super Key Seeker 4200
 * Copyright Ethan Laur 2011
 * Sequel will come sometime in the future ... nobody knows when
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <fstream>
#include <time.h>
#include <ncurses.h>

#define build "18a"


using namespace std;

string grid[2][400] = {{
"#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#",
"#"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","#",
"#","k","c"," "," "," "," "," "," "," "," "," "," "," "," ","b"," ","z"," ","#",
"#"," "," "," ","c"," ","c"," "," "," "," "," "," ","c"," "," "," "," "," ","#",
"#"," "," "," "," "," "," "," "," "," "," "," "," ","#","#","#","#","#","#","#",
"#","b","c"," "," ","z"," "," "," "," ","b"," "," ","#"," "," ","z"," ","#","#",
"#"," "," "," "," "," "," "," "," "," "," "," "," ","#"," ","#","#"," "," ","t",
"#"," "," "," "," "," "," "," ","c"," "," "," "," ","#"," "," ","#","#","#","#",
"#"," "," "," "," ","c"," "," ","#","#","#","#","#","#","#"," ","#","#"," ","#",
"#"," "," "," "," "," "," ","k","#","z","k","c"," "," ","z"," ","#"," "," ","#",
"#"," ","b"," "," "," "," "," ","#"," ","#","#","#","#","#","#","#"," "," ","#",
"#"," ","c"," "," "," ","c"," ","#","z"," ","z"," ","c","#"," ","z"," "," ","#",
"#"," "," "," "," "," "," "," ","#","#","#","#","#","z","#"," "," "," "," ","#",
"#"," "," ","c"," "," "," "," ","#"," "," "," ","#"," ","#"," "," "," "," ","#",
"#"," "," "," "," ","c"," "," ","#","k","#"," ","#"," ","#","c"," "," "," ","#",
"#","b"," "," "," "," "," ","c"," "," ","#"," ","#","z","#"," "," "," "," ","#",
"#"," "," "," "," ","k"," "," ","#","#","#","z"," "," ","#"," "," ","c"," ","#",
"#"," ","z"," "," "," "," "," "," "," ","#","#","#","#","#","k"," "," "," ","#",
"#"," "," "," "," "," "," "," "," "," "," ","c"," "," "," "," "," "," ","b","#",
"#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"}
};
string map[400];

int pos = 81, i = 1, coins = 0, keys = 0, health = 100, atk = 0, def = 0, score = 0, deadzombies = 0, lvl = 0, completedlevels = 0, awards = 0, t = 81, dzc = 0, walls = 0, start[] = {81, 250};
string zprev[400];
bool mysterybox = false, suicidal = false, easy = false, normal = false, hard = false, insane = false, peaceful = false, cheats = false, redeemed[] = {false, false, false, false, false};

string movest() //used to emiminate cin
{	string ch;
	string p_;
        string ac = "";

	initscr();			/* Start curses mode 		*/
	raw();				/* Line buffering disabled	*/
	noecho();			/* Don't echo() while we do getch */
	ch = getch();
	if (ch == "!")
	{
	  endwin();
          exit(1);
	}
	if (ch == "1")
	{
	  p_ = getch();
	  ch += p_;
	  endwin();
	  return ch;
	}
	if (ch == "2")
	{
	  p_ = getch();
	  if (p_ == "2")
	  {
	     endwin();
	     return p_;
	  }
	  ch += p_;
	}			
	refresh();
	endwin();			/* End curses mode		  */
	return ch;
}

int mapseed() {
int y = 0;
srand ( time(NULL) );
int mseed, c = 1, b = 0;
string progress[42] = {"["," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","]"};
while (y <= 399)
{
mseed = rand() % 20 + 0;
string z;
//keys walls coins zombies open stores
if (mseed == 0)
  z = "k"; // k
if (mseed == 1)
  z = "b"; // b
if (mseed == 2 || mseed == 3)
  z = "#"; // #
if (mseed == 4)
  z = "z"; // z
if (mseed == 5)
  z = "c"; // c
if (mseed == 6)
{
  int special = rand() % 15 + 0;
  if (special == 3)
    z = "?";
  else
    z = " ";
}
if (mseed >= 7)
  z = " ";
grid[1][y] = z;
b++;
if (b == 10)
{
  progress[c] = "#";
  b = 0;
  c++;
}
system("clear");
cout << "Seeding new map " << progress[0] << progress[1] << progress[2] << progress[3] << progress[4] << progress[5] << progress[6] << progress[7] << progress[8] << progress[9] << progress[10] << progress[11] << progress[12] << progress[13] << progress[14] << progress[15] << progress[16] << progress[17] << progress[18] << progress[19] << progress[20] << progress[21] << progress[22] << progress[23] << progress[24] << progress[25] << progress[26] << progress[27] << progress[28] << progress[29] << progress[30] << progress[31] << progress[32] << progress[33] << progress[34] << progress[35] << progress[36] << progress[37] << progress[38] << progress[39] << progress[40] << progress[41] << "[" << y / 4 << "%]" << endl;
y++;
}
completedlevels++;
if (suicidal != true)
  health += 5;
mseed = rand() % 400 + 20;
grid[1][0] = grid[1][1] = grid[1][2] = grid[1][3] = grid[1][4] = grid[1][5] = grid[1][6] = grid[1][7] = grid[1][8] = grid[1][9] = grid[1][10] = grid[1][11] = grid[1][12] = grid[1][13] = grid[1][14] = grid[1][15] = grid[1][16] = grid[1][17] = grid[1][18] = grid[1][19] = grid[1][20] = grid[1][40] = grid[1][60] = grid[1][80] = grid[1][100] = grid[1][120] = grid[1][140] = grid[1][160] = grid[1][180] = grid[1][200] = grid[1][220] = grid[1][240] = grid[1][260] = grid[1][280] = grid[1][300] = grid[1][320] = grid[1][340] = grid[1][39] = grid[1][59] = grid[1][79] = grid[1][99] = grid[1][119] = grid[1][139] = grid[1][159] = grid[1][179] = grid[1][199] = grid[1][219] = grid[1][239] = grid[1][259] = grid[1][279] = grid[1][299] = grid[1][319] = grid[1][339] = grid[1][359] = grid[1][360] = grid[1][379] = grid[1][380] = grid[1][381] = grid[1][382] = grid[1][383] = grid[1][384] = grid[1][385] = grid[1][386] = grid[1][387] = grid[1][388] = grid[1][389] = grid[1][390] = grid[1][391] = grid[1][392] = grid[1][393] = grid[1][394] = grid[1][395] = grid[1][396] = grid[1][397] = grid[1][398] = grid[1][399] = "#";

int tseed = rand() % 369 + 21;
grid[1][tseed] = "t";
t = tseed;
while (t >= 379)
{
int tseed = rand() % 369 + 21;
grid[1][tseed] = "t";
t = tseed;
}
grid[1][t+1] = " ";
}
int resetmap(string text) {
int x = 0;
int c = 1, b = 0;
string progress[42] = {"["," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","]"};
pos = start[lvl]; //place yourself in the right spot
while (x != 400) {
map[x] = "#";
b++;
if (b == 10)
{
  progress[c] = "#";
  b = 0;
  c++;
}
system("clear");
cout << text << " " << progress[0] << progress[1] << progress[2] << progress[3] << progress[4] << progress[5] << progress[6] << progress[7] << progress[8] << progress[9] << progress[10] << progress[11] << progress[12] << progress[13] << progress[14] << progress[15] << progress[16] << progress[17] << progress[18] << progress[19] << progress[20] << progress[21] << progress[22] << progress[23] << progress[24] << progress[25] << progress[26] << progress[27] << progress[28] << progress[29] << progress[30] << progress[31] << progress[32] << progress[33] << progress[34] << progress[35] << progress[36] << progress[37] << progress[38] << progress[39] << progress[40] << progress[41] << "[" << x / 4 << "%]" << endl;
x++;
}
map[start[lvl]] = "@"; //make sure you know where your at...
}

int showmap(int show, string text) {
if (cheats == false)
{
  cout << "You cannot do this!" << endl;
  sleep(3);
  system("clear");
  return 0;
}
int x = 0;
int c = 1, b = 0;
string progress[42] = {"["," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","]"};
while (x != 400) {
if (show == 1)
  map[x] = grid[lvl][x];
if (show == 0)
  map[x] = "#";
b++;
if (b == 10)
{
  progress[c] = "#";
  b = 0;
  c++;
}
system("clear");
cout << text << progress[0] << progress[1] << progress[2] << progress[3] << progress[4] << progress[5] << progress[6] << progress[7] << progress[8] << progress[9] << progress[10] << progress[11] << progress[12] << progress[13] << progress[14] << progress[15] << progress[16] << progress[17] << progress[18] << progress[19] << progress[20] << progress[21] << progress[22] << progress[23] << progress[24] << progress[25] << progress[26] << progress[27] << progress[28] << progress[29] << progress[30] << progress[31] << progress[32] << progress[33] << progress[34] << progress[35] << progress[36] << progress[37] << progress[38] << progress[39] << progress[40] << progress[41] << "[" << x / 4 << "%]" << endl;
x++;
}
map[pos] = "@"; //make sure you know where your at...
system("clear");
}

void teleport() {
system("clear");
mapseed();
resetmap("Loading");
lvl = 1;
}

void stats()
{
string lvltxt = "";
if (peaceful == true)
  cout << "[Peaceful] Coins: " << coins << " Keys: " << keys << " ATK: " << atk << " DEF: " << def << " Score: " << score << " CL: " << completedlevels << " POS: " << pos << " DZC: " << dzc << endl;
if (suicidal)
  lvltxt += "[suicidal]";
if (easy)
  lvltxt += "[easy]";
if (normal)
  lvltxt += "[normal]";
if (hard)
  lvltxt += "[hard]";
if (insane)
  lvltxt += "[insane]";
if (cheats)
  lvltxt += "[cheats]";
if (suicidal)
  cout << lvltxt << " " << "Health: " << health * 4 << "% Coins: " << coins << " Keys: " << keys << " ATK: " << atk << " DEF: " << def << " Score: " << score << " CL: " << completedlevels << " POS: " << pos << endl;
if (peaceful != true && suicidal == false)
  cout << lvltxt << " " << "Health: " << health << " Coins: " << coins << " Keys: " << keys << " ATK: " << atk << " DEF: " << def << " Score: " << score << " CL: " << completedlevels << " POS: " << pos << endl;
}

int mystery()
{
int qseed = rand() % 9 + 1;
return qseed;
}

string move(string null)
{
int prev = pos;
if (null == "w")
  pos += -20;
if (null == "s")
  pos += 20;
if (null == "a")
  pos --;
if (null == "d")
  pos ++;

if (grid[lvl][pos] == "#")
{
  cout << endl << "Sorry you can't do that" << endl;
  pos = prev;
}

if (grid[lvl][pos] == "z")
{
  int difficulty = completedlevels * 3;
if (completedlevels == 0)
  difficulty = 1;
if (completedlevels == 1)
  difficulty = 2;
int atkseed = rand() % difficulty + 1;
  int zomatk = (pos / 18) * atkseed;
int healthnew;
healthnew = zomatk - atk - (def * 2);
  health -= healthnew;
}

map[pos] = "@";
system("clear");
stats();
int show[8] = {pos + 20, pos - 20, pos + 1, pos - 1, pos + 21, pos + 19, pos - 21, pos - 19};
map[show[0]] = grid[lvl][show[0]];
map[show[1]] = grid[lvl][show[1]];
map[show[2]] = grid[lvl][show[2]];
map[show[3]] = grid[lvl][show[3]];
map[show[4]] = grid[lvl][show[4]];
map[show[5]] = grid[lvl][show[5]];
map[show[6]] = grid[lvl][show[6]];
map[show[7]] = grid[lvl][show[7]];

return "Move successful";
}

string store()
{
int difficulty = completedlevels * 3;
if (completedlevels == 0)
  difficulty = 3;
if (completedlevels == 1)
  difficulty = 6;
system("clear");
int null;
cout << "Welcome to the store, items cost " << difficulty << " coins. here are your options:" << endl << "1/2 Buy an ATK/DEF point" << endl << "3. 5 Health points (keys)" << endl << "4 Exit the store" << endl << ">";
cin >> null;
if (null == 1)
{
  if (coins >= difficulty)
  {
    coins -= difficulty;
    atk++;
    return "Success!";
  }

  else
    return "Not enough monies!!!";
}

if (null == 2)
{
  if (coins >= difficulty)
  {
    coins -= difficulty;
    def++;
    return "Success!";
  }

  else
    return "Not enough monies!!!";
}

if (null == 3)
{
  if (keys >= difficulty)
  {
    keys -= difficulty;
      health += 5;
    return "Success!";
  }

  else
    return "Not enough monies!!!";
}

return "Error";
}


string use(string null)
{

int prev = pos;
if (null == "2w")
  prev += -20;
if (null == "2s")
  prev += 20;
if (null == "2a")
  prev --;
if (null == "2d")
  prev ++;
if (null == "2")
  prev = pos;

if (grid[lvl][prev] == "b")
  store();

if (grid[lvl][prev] == "t" || grid[1][prev] == "\033[22;31mt\e[m")
  teleport();

if (grid[lvl][prev] == "c")
{
  cout << endl << "Coin collected!" << endl;
  coins++;
  grid[lvl][prev] = map[prev] = " ";
}

if (grid[lvl][prev] == "k")
{
  cout << endl << "Key collected!" << endl;
  keys++;
  grid[lvl][prev] = map[prev] = " ";
}

if (grid[lvl][prev] == "?")
{
if (mysterybox == false)
{
  cout << "You found a mystery box..." << endl << "These are a suprise category item that will generate a new item at random" << endl;
  sleep(2);
  mysterybox = true;
}
if (mystery() == 1)
 grid[1][prev] = map[prev] = "k";
if (mystery() == 2)
 grid[1][prev] = map[prev] = "c";
if (mystery() == 3 && mystery() == 4)
 grid[1][prev] = map[prev] = "z";
if (mystery() == 5 && mystery() == 6)
 grid[1][prev] = map[prev] = "#";
if (mystery() == 7)
 grid[1][prev] = map[prev] = " ";
if (mystery() == 8)
 grid[1][prev] = map[prev] = "b";
if (mystery() == 9)
 grid[1][prev] = map[prev] = "\033[22;31mt\e[m";
}

system("clear");
stats();
return "Use successful";
}

string attack(string null)
{
int prev = pos;
system("clear");
stats();
if (null == "1w")
  prev += -20;
if (null == "1s")
  prev += 20;
if (null == "1a")
  prev --;
if (null == "1d")
  prev ++;
if (grid[lvl][prev] == "#")
{
  if (atk >= 25){
    grid[lvl][prev] = " ";
    walls++;
    cout << "This is VERY dangerous!!! Do not EVER to this on the top or bottom of the map!!" << endl;
    sleep(1);
  }
  return "You just killed a wall!";
}
if (grid[lvl][prev] != "z")
  return "Not a zombie";
srand ( time(NULL) );
int difficulty = completedlevels * 3;
if (completedlevels == 0)
  difficulty = 1;
if (completedlevels == 1)
  difficulty = 2;
int zombiehealth = rand() % difficulty + 1;
zombiehealth -= atk;

if (zombiehealth <= 0)
{
  grid[lvl][prev] = map[prev] = "x";
  deadzombies++;
  dzc++;
  if (dzc >= 10)
  {
    coins += 5;
    dzc = 0;
  }
}
else
{
int healthnew;
healthnew = zombiehealth - def;
if (healthnew >= 0)
  health -= healthnew;
return "You were hit";
}

return "Function complete";
}
  

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
  cout << "Instructions!!!" << endl << "Use W A S D (lowercase) to move (you need to hit enter)" << endl << "To puck up/use something (k, c, b, ?), press 2 and then W A S D and press enter" << endl << "To attack (zombies, and one other secret thing) press 1 and then W A S D <enter>" << endl << "GOOD LUCK!!!!!!" << endl;
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
while (i = 1) {
score = coins + (keys * 2) + deadzombies + (atk / 3 + def / 3) + (completedlevels * 3) + (awards * 2) + (walls / 15);
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
  if (keys >= 100 && redeemed[3] == false) {
    awards += 25;
    redeemed[3] = true;
    cout << "You just got an award!" << endl;
    sleep(3);
  }
  if (completedlevels >= 25 && redeemed[4] == false) {
    awards += 50;
    redeemed[4] = true;
    system("clear");
    cout << "You just got an award!" << endl;
    sleep(3);
  }
int i = 0;
int ix = 0;
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

/*
#define RED  "\033[22;31m" //red for printf
#define RESET "\e[m" //set the color back to normal
#define BLUE "\e[34m" //blue for printf
#define YELLOW "\e[35m" //not yellow
#define GREEN "\e[32m" //green for printf
#define BLINK "\e[7;32m" //switch colors for debug
*/

while (ix < 400)
{
if (i == 20)
{
  cout << endl;
  i = 0;
  map[pos] = "\033[22;31m@\e[m"; //make you show up RED
  grid[1][t] = "\033[22;31mt\e[m"; //make the teleport RED
  printf("%s ", map[ix].c_str());
}
else
  cout << map[ix] << " ";
i++;
ix++;
}
//cout << endl << ">";
null = movest();
//cin >> null;/*removed for NCURSES*/
if ((null == "w") || (null == "a") || (null == "s") || (null == "d"))
  move(null);
if ((null == "2w") || (null == "2a") || (null == "2s") || (null == "2d") || (null == "2"))
  use(null);
if ((null == "1w") || (null == "1a") || (null == "1s") || (null == "1d"))
  attack(null);
if (null == "reset")
  resetmap("Resetting...");
if (null == "show")
  showmap(1, "Showing map... ");
if (null == "hide")
  showmap(0, "Hiding map ... ");
/*{
  int tseed = rand() % 369 + 21;
  grid[lvl][tseed] = "t";
  t = tseed;
  grid[1][t+1] = " ";
  system("clear");
  cout << "I just placed another teleport on the map" << endl;
  sleep(3);
}*/
if (null == "cheats.on")
{
  cheats = true;
  int cheat = 1, yy = 0;
  string ch[10] = {"  ","  ","  ","  ","  ","  ","  ","  ","  ","  "};
  while (cheat != 11)
  {
  system("clear");
  cout << "Enabling cheats ... " << "[" << ch[0] << ch[1] << ch[2] << ch[3] << ch[4] << ch[5] << ch[6] << ch[7] << ch[8] << ch[9] << "]" << endl;
  sleep(1);
  ch[yy] = "##";
  yy++;
  cheat++;
  }
  system("clear");
  cout << "Enabling cheats ... " << "[" << ch[0] << ch[1] << ch[2] << ch[3] << ch[4] << ch[5] << ch[6] << ch[7] << ch[8] << ch[9] << "]" << endl;
  sleep(1);
  system("clear");
  stats();
}
if (null == "t")
{
  cout << "The teleport is at " << t << endl;
  sleep(3);
}
if (null == "quit")
{
  cout << "Your score was: " << score << " Thank you for playing!" << endl;
  exit(0);
}

} }

main() {
printf("\e[m");
resetmap("Loading");
system("clear");
printf("Welcome to Super Key Seeker 4200 (build %s)\nYou are at the main menu, please select a difficulty:\n1. Easy\n2. Normal\n3. Hard\n4. Insane\n5. Suicidal\n6. Peaceful (no life counter)\n>", build);
int null = 1;
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
  peaceful = true;
  cheats = true;
}
system("clear");
game(0);
}
