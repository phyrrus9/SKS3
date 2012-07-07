/*
 * Simple text-based game
 * Copyright Ethan Laur 2011
 *
 */
#include "ks4200.h"

#define WALL (0)
#define OPEN (1)
#define COIN (3)
#define CHG (4)
#define KEY (5)
#define WINCOINS (24)
#define CRATE (81)

using namespace std;

int grid[6][100] = {
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                 0, 5, 1, 1, 3, 1, 1, 5, 1, 0,
                 0, 3, 1, 1, 1, 1, 1, 1, 1, 0,
                 0, 1, 1, 1, 1, 5, 0, 1, 0, 0,
                 0, 3, 1, 3, 1, 1, 0, 1, 1, 0,
                 0, 1, 1, 1, 1, 3, 0, 0, 1, 0,
                 0, 5, 1, 1, 5, 1, 0, 1, 1, 0,
                 0, 1, 1, 3, 1, 1, 0, 1, 0, 0,
                 0, 2, 1, 1, 1, 1, 5, 3, 1, 4,
                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
                {0, 4, 0, 0, 0, 0, 0, 0, 0, 0,
                 0, 1, 1, 0, 1, 0, 1, 3, 1, 0,
                 0, 3, 0, 1, 1, 1, 1, 1, 1, 0,
                 0, 1, 1, 1, 3, 1, 1, 1, 5, 0,
                 0, 5, 1, 1, 5, 1, 1, 0, 1, 0,
                 0, 0, 1, 1, 0, 0, 1, 1, 1, 0,
                 0, 1, 1, 3, 1, 1, 3, 1, 3, 0,
                 0, 1, 1, 1, 1, 0, 1, 1, 1, 0,
                 0, 2, 0, 3, 1, 1, 1, 1, 1, 0,
                 0, 4, 0, 0, 0, 0, 0, 0, 0, 0,},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                 0, 1, 0, 1, 1, 1, 0, 1, 5, 0,
                 4, 1, 1, 1, 3, 1, 0, 1, 1, 0,
                 0, 0, 1, 1, 0, 1, 0, 1, 1, 0,
                 0, 1, 1, 5, 1, 1, 1, 1, 1, 0,
                 0, 1, 0, 1, 0, 1, 0, 1, 0, 0,
                 0, 1, 3, 1, 1, 1, 1, 3, 1, 0,
                 0, 0, 1, 1, 1, 1, 1, 0, 0, 0,
                 0, 2, 1, 0, 1, 3, 3, 1, 1, 0,
                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                 0, 1, 1, 0, 1, 1, 1, 5, 0, 0,
                 0, 1, 1, 3, 1, 0, 1, 1, 2, 4,
                 0, 0, 1, 1, 1, 1, 0, 1, 0, 0,
                 0, 1, 1, 1, 1, 1, 0, 1, 5, 0,
                 0, 1, 3, 5, 1, 1, 0, 0, 1, 0,
                 0, 0, 1, 0, 0, 0, 0, 1, 3, 0,
                 0, 0, 1, 0, 3, 1, 1, 1, 1, 0,
                 4, 1, 1, 1, 1, 1, 0, 3, 1, 4,
                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                 0, 1, 1, 1, 1, 1, 1, 0, 3, 0,
                 0, 1, 0, 0, 1, 0, 1, 0, 1, 0,
                 0, 1, 1, 1, 3, 0, 1, 0, 1, 0,
                 0, 1, 0, 1, 0, 0, 1, 1, 1, 0,
                 0, 1, 0, 5, 0, 0, 0, 0, 1, 0,
                 0, 1, 0, 0, 1, 1, 1, 0, 3, 0,
                 0, 1, 1, 1, 1, 0, 1, 0, 0, 0,
                 0, 0, 1, 0, 1, 0, 1, 1, 2, 4,
                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                 0, 6, 1, 0, 1, 1, 0, 0, 6, 0,
                 0, 1, 0, 1, 1, 1, 1, 0, 1, 0,
                 0, 1, 0, 0, 0, 0, 1, 0, 1, 0,
                 0, 1, 0, 0, 2, 1, 1, 1, 1, 0,
                 0, 1, 0, 0, 0, 0, 1, 0, 1, 0,
                 0, 1, 0, 1, 1, 1, 1, 0, 1, 0,
                 0, 1, 1, 0, 0, 0, 0, 0, 1, 0,
                 0, 6, 1, 1, 1, 1, 1, 1, 6, 0,
                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,} };


int pos = 81;
int coins = 0;
int keys = 0;
int lvl = 0;
int leveltotal = 5;
int start[6] = {81, 81, 81, 28, 88, 44};
int walls = 0;
int score;

void win()
{
  cout << "You won!" << endl << "Your score is: " << score * 2 << endl << "Your UIC is: " << lvl  <<  pos  << keys  << walls << (coins / 3) << (score * 2) / 3 << pos << endl << endl << "Please write down your score and submit it at http://goo.gl/bO7eB" << endl;
  sleep(5);
  exit(0);
}

void intermission(int lvl)
{
  if (lvl == 1)
  {
    cout << "You searched the area.." << endl;
    sleep(4);
    cout << "But you could not locate all of the keys ... " << endl;
    sleep(4);
    cout << "You found a door, well, a ladder" << endl;
    sleep(5);
  }
  if (lvl == 2)
  {
    cout << "You searched the area.." << endl;
    sleep(4);
    cout << "But you STILL could not locate all of the keys ... " << endl;
    sleep(4);
    cout << "Searching harder, you found another ladder" << endl;
    sleep(4);
    cout << "Leading to a new world, unfriendly and confusing ... you pushed onward" << endl;
    sleep(6);
  }
  if (lvl == 3)
  {
    cout << "You searched again" << endl;
    sleep(4);
    cout << "But but still, you came up short..." << endl;
    sleep(4);
    cout << "You were about to complete the process of moving to the new world" << endl;
    sleep(5);
    cout << "When it happened!!!" << endl;
    sleep(5);
    cout << "There was a heavy solar storm, that grabbed a few of your keys!" << endl;
    sleep(4);
    keys += -2;
  }
  if (lvl == 4)
  {
    cout << "Getting closer, you realise you are in another unfriendly, confusing environment..." << endl;
    sleep(4);
    cout << "You only need a few keys, so you push on harder" << endl;
    sleep(5);
  }
  if (lvl == 5)
  {
    cout << "You now have all of the keys again!" << endl;
    sleep(4);
    cout << "All that needs to be done now ..." << endl;
    sleep(4);
    cout << "Is ..." << endl;
    sleep(5);
    cout << "Get the ONE key to the universe ... " << endl;
    sleep(4);
    cout << "You have been dumped into a chamber, with multiple chests...";
    sleep(3);
    cout << "You don't have much time anymore before it happens all over again";
    sleep(2);
    cout << "But you may only have one shot! And, you cant see where your going!!!";
    sleep(6);
  }
}

int ladder(int prev)
{
  int level = 0;
  int null;
  //int prev;
  if (keys == 0)
  {
    cout << "Sorry, you do not have enough keys!" << endl;
    pos = prev;
    return 0;
  }
  cout << "What level would you like to go to?" << endl << "0 or 1 (forward or backward)" << endl << ">";
  cin >> level;
  keys--;
  if (level == 0)
  {
    null = lvl + 1;
    if (null <= leveltotal)
    lvl++;
    intermission(lvl);
    pos = start[lvl];
  }
  if (level == 1)
  {
    null = lvl--;
    if (null <= leveltotal)
    lvl--;
    pos = start[lvl];
  }
  if (level == 1337)
  {
    cin >> null;
    lvl = null;
    pos = start[lvl];
  }
  cout << "You just moved to level " << lvl << endl;
    return 0;
}

string move(string param1)
{
  if (param1 == "up")
  {
    int prev = pos;
    pos += -10;
      if (grid[lvl][pos] == 4)
      {
        ladder(prev);
        return "Ladder";
      }
      if (grid[lvl][pos] == 6)
      {
	if (pos == CRATE)
	win();
	return "Crate";
      }
    if (grid[lvl][pos] == 0 || grid[lvl][pos] >=3)
    {
      pos = prev;
      return "There is something here!";
    }
    grid[lvl][prev] = 1;
    grid[lvl][pos] = 2;
  }
  if (param1 == "down")
  {
    int prev = pos;
    pos += 10;
      if (grid[lvl][pos] == 4)
      {
        ladder(prev);
        return "Ladder";
      }
      if (grid[lvl][pos] == 6)
      {
	if (pos == CRATE)
	win();
	return "Crate";
      }
    if (grid[lvl][pos] == 0 || grid[lvl][pos] >=3)
    {
      pos = prev;
      return "There is something here!";
    }
    grid[lvl][prev] = 1;
    grid[lvl][pos] = 2;
  }
  if (param1 == "right")
  {
    int prev = pos;
    pos += 1;
      if (grid[lvl][pos] == 4)
      {
        ladder(prev);
        return "Ladder";
      }
      if (grid[lvl][pos] == 6)
      {
	if (pos == CRATE)
	win();
	return "Crate";
      }
    if (grid[lvl][pos] == 0 || grid[lvl][pos] >= 3)
    {
      pos = prev;
      return "There is something here!";
    }
    grid[lvl][prev] = 1;
    grid[lvl][pos] = 2;
  }
  if (param1 == "left")
  {
    int prev = pos;
    pos += -1;
      if (grid[lvl][pos] == 4)
      {
        ladder(prev);
        return "Ladder";
      }
      if (grid[lvl][pos] == 6)
      {
	if (pos == CRATE)
	win();
	return "Crate";
      }
    if (grid[lvl][pos] == 0 || grid[lvl][pos] >= 3)
    {
      pos = prev;
      return "There is something here!";
    }
    grid[lvl][prev] = 1;
    grid[lvl][pos] = 2;
  }
  return "";
}

string look(string param1)
{
  int view;
  if (param1 == "up")
    view = pos - 10;
  if (param1 == "down")
    view = pos + 10;   
  if (param1 == "right")
    view = pos + 1;
  if (param1 == "left")
    view = pos - 1;

  if (grid[lvl][view] == WALL)
    return "You see a wall";
  if (grid[lvl][view] == OPEN)
    return "You see nothing";
  if (grid[lvl][view] == COIN)
    return "You see a coin!";
  if (grid[lvl][view] == CHG)
    return "You see a ladder!";
  if (grid[lvl][view] == KEY)
    return "You see a key!";
  if (grid[lvl][view] == 6)
    return "You see a crate!";
  else
    return "Error";
}

string grab(string param1)
{
  int get;
  string null;
  if (param1 == "up")
    get = pos - 10;
  if (param1 == "down")
    get = pos + 10;   
  if (param1 == "right")
    get = pos + 1;
  if (param1 == "left")
    get = pos - 1;

  if (grid[lvl][get] == COIN)
  {
    coins++;
    grid[lvl][get] = 1;
    return "Coin added to inventory!";
  }
  if (grid[lvl][get] == KEY)
  {
    keys++;
    grid[lvl][get] = 1;
    return "Key added to inventory!";
  }
  if (grid[lvl][get] == WALL)
  {
    walls++;
    cout << "You grabbed a wall ..." << endl;
    return "You dropped a wall";
  }

    return "Error";
}

int ks4200(const char* argv)
{
int i = 1;
string cli;
cli = argv;
if (cli == "restore")
{
  cout << "Please enter your restore code"  << endl;
  cin >> lvl  >> pos  >> keys >> walls >> coins;
  cout << "Game restored!" << endl;
  cli = "quickstart";
}

if (cli == "help")
{
  cout << "Welcome to Key Seeker 4200!!!" << endl << "Commands are simple: " << endl;
  cout << "====================================================================================" << endl;
  cout << "Command			parameters			Use			       " << endl;
  cout << "====================================================================================" << endl;
  cout << "move			up, down, left, right		Move somewhere                 " << endl;
  cout << "look			up, down, left, right		Look at something              " << endl;
  cout << "grab			up, down, left, right		Pick something up              " << endl;
  cout << "save			game				Print your save code           " << endl;
  cout << "restore			game				Restore a saved game           " << endl << endl;
  cout << "Just press control and C to exit the game." << endl;
  //exit(0);
}
if (cli != "quickstart")
{
cout << "Once, a very very long time ago, there was a guy..." << endl;
sleep(2);
cout << "Questing for the key to the universe...." << endl;
sleep(2);
cout << "He had all of the keys stored in a crate only he could open" << endl;
sleep(2);
cout << "At least he thought ..." << endl;
sleep(2);
cout << "They were stolen, and scattered about the universe again" << endl;
sleep(2);
cout << "They have been located in a small, 64x64 lightyear square" << endl;
sleep(1);
cout << "You are that guy.. your name is John Jacob Jingle-Heimer-Smith" << endl;
sleep(3);
}

while (i == 1) {
if (cli == "debug")
{
cout << grid[lvl][0] << grid[lvl][1] << grid[lvl][2] << grid[lvl][3] << grid[lvl][4] << grid[lvl][5] << grid[lvl][6] << grid[lvl][7] << grid[lvl][8] << grid[lvl][9] << endl;
cout << grid[lvl][10] << grid[lvl][11] << grid[lvl][12] << grid[lvl][13] << grid[lvl][14] << grid[lvl][15] << grid[lvl][16] << grid[lvl][17] << grid[lvl][18] << grid[lvl][19] << endl;
cout << grid[lvl][20] << grid[lvl][21] << grid[lvl][22] << grid[lvl][23] << grid[lvl][24] << grid[lvl][25] << grid[lvl][26] << grid[lvl][27] << grid[lvl][28] << grid[lvl][29] << endl;
cout << grid[lvl][30] << grid[lvl][31] << grid[lvl][32] << grid[lvl][33] << grid[lvl][34] << grid[lvl][35] << grid[lvl][36] << grid[lvl][37] << grid[lvl][38] << grid[lvl][39] << endl;
cout << grid[lvl][40] << grid[lvl][41] << grid[lvl][42] << grid[lvl][43] << grid[lvl][44] << grid[lvl][45] << grid[lvl][46] << grid[lvl][47] << grid[lvl][48] << grid[lvl][49] << endl;
cout << grid[lvl][50] << grid[lvl][51] << grid[lvl][52] << grid[lvl][53] << grid[lvl][54] << grid[lvl][55] << grid[lvl][56] << grid[lvl][57] << grid[lvl][58] << grid[lvl][59] << endl;
cout << grid[lvl][60] << grid[lvl][61] << grid[lvl][62] << grid[lvl][63] << grid[lvl][64] << grid[lvl][65] << grid[lvl][66] << grid[lvl][67] << grid[lvl][68] << grid[lvl][69] << endl;
cout << grid[lvl][70] << grid[lvl][71] << grid[lvl][72] << grid[lvl][73] << grid[lvl][74] << grid[lvl][75] << grid[lvl][76] << grid[lvl][77] << grid[lvl][78] << grid[lvl][79] << endl;
cout << grid[lvl][80] << grid[lvl][81] << grid[lvl][82] << grid[lvl][83] << grid[lvl][84] << grid[lvl][85] << grid[lvl][86] << grid[lvl][87] << grid[lvl][88] << grid[lvl][89] << endl;
cout << grid[lvl][90] << grid[lvl][91] << grid[lvl][92] << grid[lvl][93] << grid[lvl][94] << grid[lvl][95] << grid[lvl][96] << grid[lvl][87] << grid[lvl][98] << grid[lvl][99] << endl; 
}
string null;
score = (coins * 2) + keys + (walls / 3);
if (coins >= WINCOINS)
  cout << "At any time, you may type end game to end the game" << endl;
cout /*<< "Your location: " << pos */<< "Level: " << lvl << " Coins: " << coins << " Keys: " << keys << " Score: " << score << " SC: " << lvl << " " <<  pos << " " << keys << " " << walls << " " << coins << endl << ">";
string action;
string param1;
if (walls == 25)
{
  coins++;
  walls = 0;
  cout << "You just got a free coin!" << endl;
}
else
  cin >> action >> param1;
if (action == "end")
{
  cout << "Your score is: " << score << "Please submit it at http://goo.gl/bO7eB" <<  endl;
  return 0;
}
if (action == "move" || action == "m")
cout << move(param1) << endl;
if (action == "look" || action == "l")
cout << look(param1) << endl;
if (action == "grab" || action == "g")
cout << grab(param1) << endl;
if (action == "save" || action == "s")
{
cout << "Your save code is " << lvl << " " <<  pos << " " << keys << " " << walls << " " << coins << endl;
return 0;
}
if (action == "restore")
{
  cout << "Please enter your restore code"  << endl;
  cin >> lvl  >> pos  >> keys >> walls >> coins;
  cout << "Your game has been restored!" << endl;
}
}
    return 0;
}
