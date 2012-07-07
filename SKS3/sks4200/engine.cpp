/*
 * SKS 4200 Engine (will be used hopefully for all)
 * Copyright Ethan Laur 2011
 * Used to make the main code a little smaller
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
#include "sks4200-sp-defines.cpp"
#define engine "3.1.5"

void radius()
{
if (gam == 2)
{
  if (mapview[lvl])
  {
    for (int x = 0; x != 400; x++)
      map[x] = grid[gam - 1][lvl][x];
  }
}
  
int show[8] = {pos + 20, pos - 20, pos + 1, pos - 1, pos + 21, pos + 19, pos - 21, pos - 19};
map[show[0]] = grid[gam - 1][lvl][show[0]];
map[show[1]] = grid[gam - 1][lvl][show[1]];
map[show[2]] = grid[gam - 1][lvl][show[2]];
map[show[3]] = grid[gam - 1][lvl][show[3]];
map[show[4]] = grid[gam - 1][lvl][show[4]];
map[show[5]] = grid[gam - 1][lvl][show[5]];
map[show[6]] = grid[gam - 1][lvl][show[6]];
map[show[7]] = grid[gam - 1][lvl][show[7]];
}

int AI()
{
//some intelligence will go here someday ... but these zombies are so STUPID!!!
}

int resetmap(string text) //used in resetting the map to all '#'
{
int c = 1, b = 0;
string progress[42] = {"["," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","]"};
pos = start[gam - 1][lvl]; //place yourself in the right spot
for (int x = 0; x != 400; x++){
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
}
map[start[gam - 1][lvl]] = "@"; //make sure you know where your at...
}

void save()
{
endwin(); //sometimes it breaks the terminal
system("clear"); //endwin will spit out old shit
cout << "Save Code: " << ss[0] << " " << ss[1] << " " << ss[2] << " " << ss[3] << " " << ss[4] << " " << ss[5] << " " << ss[6] << " " << ss[7] << " " << ss[8] << " " << ss[9] << " " << easy << " " << normal << " " << hard << " " << suicidal << " " << peaceful << " " << cheats << " " << health << " " << redeemed[0] << " " << redeemed[1] << " " << redeemed[2] << " " << redeemed[3] << " " << redeemed[4] << endl << endl << endl;
sleep(5); //give time to react
exit(0);
}

void restore()
{
system("clear");
endwin(); //needs to be HERE
cout << "Please enter your restore code EXACTLY how it was" << endl;
cin >> lvl >> coins >> keys >> atk >> def >> score >> deadzombies >> awards >> dzc >> walls >> easy >> normal >> hard >> suicidal >> peaceful >> cheats >> health >> redeemed[0] >> redeemed[1] >> redeemed[2] >> redeemed[3] >> redeemed[4];
resetmap("Restoring your game...");
}

string movest() //Uses curses to get the char without enter
{	
        string ch;
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
          endwin();
	  ch += p_;
          return ch;
	}
	if (ch == "3")
	  save();
	if (ch == "4")
	  restore();			
	refresh();
	endwin();			/* End curses mode		  */
	return ch;
}

void viewmap()
{
int ix = 1;
int i = 1;
cout << "# ";
while (ix < 400)
{
if (i == 20)
{
  cout << endl;
  i = 0;
  map[pos] = "\033[22;31m@\e[m"; //make you show up RED
  printf("%s ", map[ix].c_str());
}
else
  cout << map[ix] << " ";
i++;
ix++;
}
cout << endl << endl;
}

void stats()
{
if (atk <= 0)
  atk = 0;
string lvltxt = "";
string lname = "";
string dev = "";
if (gam == 2)
{
lname = "Level: ";
lname += names[lvl];
dev = " Developer: ";
dev += developer[lvl];
}

if (peaceful == true)
  cout << "[Peaceful] Coins: " << coins << " Keys: " << keys << " ATK: " << atk << " DEF: " << def << " Score: " << score << " LVL: " << lvl << " POS: " << pos << " DZC: " << dzc << endl;
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
  cout << lvltxt << " " << "Health: " << health * 4 << "% Coins: " << coins << " Keys: " << keys << " ATK: " << atk << " DEF: " << def << " Score: " << score << " " << lname << dev << endl;
if (peaceful != true && suicidal == false)
  cout << lvltxt << " " << "Health: " << health << " Coins: " << coins << " Keys: " << keys << " ATK: " << atk << " DEF: " << def << " Score: " << score << " " << lname << dev << endl;
}

string move(string null)
{
AI();
int prev = pos;
if (null == "w")
  pos += -20;
if (null == "s")
  pos += 20;
if (null == "a")
  pos --;
if (null == "d")
  pos ++;

if (grid[gam - 1][lvl][pos] == "#")
{
  cout << endl << "Sorry you can't do that" << endl;
  pos = prev;
}

if (grid[gam - 1][lvl][pos] == "D")
{
  system("clear");
  cout << endl << endl << "YOU ARE DEAD!!!" << endl << endl;
  int dead = score + health;
  if (dead <= 0)
    dead = 0;
  cout << "Your score was: " << dead << " Thank you for playing!" << endl;
  exit(0);
}

if (grid[gam - 1][lvl][pos] == "z")
{
  if (lvl >= 3 && gam == 2)
    atk -= 5;
  int difficulty = lvl * 3;
if (lvl == 0)
  difficulty = 1;
if (lvl == 1)
  difficulty = 2;
int atkseed = rand() % difficulty + 1;
  int zomatk = (pos / 18) * atkseed;
int healthnew;
healthnew = zomatk - atk - (def * 2);
if (healthnew <= 0)
  healthnew = healthnew * -1;

health -= healthnew;
}

map[pos] = "@";
system("clear");
stats();
radius();

moveup[0]++;
if (moveup[0] >= 500)
{
  coins += 1000;
  moveup[0] = 0;
}

return "Move successful";
}

string attack(string null)
{
if (lvl >= 3)
  atk--;
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
if (grid[gam - 1][lvl][prev] == "#")
{
  if (atk >= 25){
    grid[gam - 1][lvl][prev] = " ";
    walls++;
    cout << "This is VERY dangerous!!! Do not EVER to this on the top or bottom of the map!!" << endl;
    sleep(1);
  }
  return "You just killed a wall!";
}
if (grid[gam - 1][lvl][prev] != "z" && grid[gam - 1][lvl][prev] != "D")
  return "Not a zombie or boss";

if (grid[gam - 1][lvl][prev] == "D")
{
  int key = 0;
  if (prev == 21)
    key = 0;
  if (prev == 38)
    key = 1;
  if (prev == 361)
    key = 2;
  if (prev == 169)
    key = 3;
  if (prev == 170)
    key = 4;
  if (prev == 171)
    key = 5;
  if (prev == 189)
    key = 6;
  if (prev == 191)
    key = 7;
  if (prev == 209)
    key = 8;
  if (prev == 210)
    key = 9;
  if (prev == 211)
    key = 10;
  int damage = atk - hits;
  boss[key] -= damage;
  health -= (damage / 3);
  hits++;
  if (boss[key] <= 0)
  {
    coins += 50;
    keys += 25;
    hits = 0;
    health = health * 2;
    grid[gam - 1][lvl][prev] = map[prev] = "$";
  }
  return "Attacked a boss!";
}
srand ( time(NULL) );
int difficulty = lvl * 3;
if (lvl == 0)
  difficulty = 1;
if (lvl == 1)
  difficulty = 2;
int zombiehealth = rand() % difficulty + 1;
zombiehealth -= atk;

if (zombiehealth <= 0)
{
  grid[gam - 1][lvl][prev] = map[prev] = "x";
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

moveup[1]++;
if (moveup[1] >= 100)
{
  coins += 1000;
  moveup[1] = 0;
}

return "Function complete";
}

void teleport() {
system("clear");
lvl++;
ss[0] = lvl;
ss[1] = coins;
ss[2] = keys;
ss[3] = atk;
ss[4] = def;
ss[5] = score;
ss[6] = deadzombies;
ss[7] = awards;
ss[8] = dzc;
ss[9] = walls;
if (lvl >= levels)
{
  if (lvl == 25)
  {
    awards += 500;
  }
  cout << "You win!!!" << endl << "Your score was " << score << endl << "Just in case we release another update, " << endl;
  save();
  exit(0);
}
if (suicidal == false && cheats == false)
  health += 10;
resetmap("Loading new level...");
}

string store()
{
int difficulty = lvl * 3;
if (lvl == 0)
  difficulty = 3;
if (lvl == 1)
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

if (null == 4)
  return "Store closed";

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

if (grid[gam - 1][lvl][prev] == "b")
  store();

if (grid[gam][lvl - 1][prev] == "t" || grid[gam - 1][lvl][prev] == TEL)
  teleport();

if (grid[gam - 1][lvl][prev] == "c")
{
  cout << endl << "Coin collected!" << endl;
  coins++;
  grid[gam - 1][lvl][prev] = map[prev] = " ";
}

if (grid[gam - 1][lvl][prev] == "s")
{
  cout << endl << "SpuerCoin collected!" << endl;
  coins += 50;
  grid[gam - 1][lvl][prev] = map[prev] = " ";
}

if (grid[gam - 1][lvl][prev] == "B")
{
  cout << endl << "Translated!" << endl;
  int translate = lvl * 3;
  if (keys >= translate)
  {
    awards += (translate * 3);
    keys -= translate;
  }
  grid[gam - 1][lvl][prev] = map[prev] = " ";
}

if (grid[gam - 1][lvl][prev] == "k")
{
  cout << endl << "Key collected!" << endl;
  keys++;
  grid[gam - 1][lvl][prev] = map[prev] = " ";
}

system("clear");
stats();
return "Use successful";
}
