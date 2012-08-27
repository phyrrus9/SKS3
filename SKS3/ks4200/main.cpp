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
 ******************************************************************
 Key Seeker 4200, a simple text based game written for UNIX systems
 This game is copyright © 2011 Ethan Laur (phyrrus9)
 This software is open source, meaning that any distribution of it
 must include this code along with the binary file or give access
 to it by a simple means. Any derivitive work of this software must
 carry this block of code to tell who the original authors are and
 also a list of changes made by the third party and contact details
 so that other parties may reach them for help about their code.
 =================================================================
 File: ks4200/main.cpp
 Description: Full game code for key seeker 4200 including maps,
 engine, interface, all that jazz. I am working on making this into
 a human readable state but it isnt going too well as you will see
 if you proceed to read the below code.
 Authors: phyrrus9 <phyrrus9@gmail.com>
 *****************************************************************/
#include "ks4200.h"

int grid[6][100] = {
                //level 1
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
                //level 2
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
                //level 3
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
                //level 4
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
                //level 5
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
                //final level
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
bool static_map = true;
int file_level = 0, file_level_total = 1;

void win(void);

void read_map(const char * mapfile_base)
{
    //ifstream listfile(".kslistfile");
    //if (!listfile)
      //  return;
    //listfile >> file_level_total;
    //listfile.close();
    if (true)
    {
        ostringstream mapfile;
        mapfile << mapfile_base;
        mapfile << file_level;
        cout << mapfile.str().c_str() << endl;
        cin >> ws;
        ifstream inputfile(mapfile.str().c_str());
        if (!inputfile)
            win();
        for (int i = 0; i < 100; i++)
        {
            inputfile >> grid[0][i];
        }
    }
    else
        win();
}

void win()
{
    /*
     * Win function, this is called when you complete the
     * game, it will display all of the required information
     * that games usually print out to the screen along with
     * a code you can use to submit your score to the contest
     * board on my google docs spreadsheet
     */
    cout << "You won!" << endl << "Your score is: " << score * 2 << endl << "Your UIC is: " << lvl  <<  pos   << keys  << walls << (coins / 3) << (score * 2) / 3 << pos << endl << endl << "Please write down your score and submit it at http://goo.gl/bO7eB" << endl;
    sleep(5);
    exit(0);
}

void intermission(int lvl)
{
    /*
     * intermission function, this will simply display
     * the intermission text to make a dramatic effect
     * when you switch levels and fast forward into the
     * future.
     */
    
    switch (lvl)
    {
        case 1:
            cout << "You searched the area.." << endl;
            sleep(4);
            cout << "But you could not locate all of the keys ... " << endl;
            sleep(4);
            cout << "You found a door, well, a ladder" << endl;
            sleep(5);
            break;
        case 2:
            cout << "You searched the area.." << endl;
            sleep(4);
            cout << "But you STILL could not locate all of the keys ... " << endl;
            sleep(4);
            cout << "Searching harder, you found another ladder" << endl;
            sleep(4);
            cout << "Leading to a new world, unfriendly and confusing ... you pushed onward" << endl;
            sleep(6);
            break;
        case 3:
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
            break;
        case 4:
            cout << "Getting closer, you realise you are in another unfriendly, confusing environment..." << endl;
            sleep(4);
            cout << "You only need a few keys, so you push on harder" << endl;
            sleep(5);
            break;
        case 5:
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
            break;
    }
}

int ladder(int prev)
{
    /*
     * the ladder function is called when you walk
     * up to an object that is a ladder and press
     * the use key. This will transform you to the
     * next level up the chain
     */
    
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
    if (static_map)
    {
        lvl++;
        intermission(lvl);
    }
    else
    {
        file_level++;
        read_map(".ksmapfile");
    }
    pos = start[lvl];
  }
  if (level == 1)
  {
    null = lvl--;
    if (null <= leveltotal)
    if (static_map)
        lvl--;
    else
    {
        file_level--;
        read_map(".ksmapfile");
    }
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
    /*
     * Move function, takes one parameter, which
     * probably shouldnt be a std::string but it
     * is because I sucked at programming when I
     * wrote this game. Anyways this updates the
     * character position by writing your character
     * physically to the map.
     */
    
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
    /*
     * look function, just prints to the screen
     * what you see (if you were actually in this
     * scary map).
     */
    
  int view;
  if (param1 == "up")
    view = pos - 10;
  if (param1 == "down")
    view = pos + 10;   
  if (param1 == "right")
    view = pos + 1;
  if (param1 == "left")
    view = pos - 1;

    switch (grid[lvl][view])
    {
        case WALL:
            return "You see a wall";
        case OPEN:
            return "You see nothing";
        case COIN:
            return "You see a coin!";
        case CHG:
            return "You see a ladder!";
        case KEY:
            return "You see a key!";
        case 6:
            return "You see a crate!";
        default:
            return "Error";
    }
}

string grab(string param1)
{
    /*
     * grab function, picks up whatever you point it at
     */
    
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

    switch (grid[lvl][get])
    {
        case COIN:
            coins++;
            grid[lvl][get] = 1;
            return "Coin added to inventory!";
            break;
        case KEY:
            keys++;
            grid[lvl][get] = 1;
            return "Key added to inventory!";
            break;
        case WALL:
            walls++;
            cout << "You grabbed a wall ..." << endl;
            return "You dropped a wall";
            break;
        default:
            return "Error!";
            break;
    }
}

int ks4200(const char* argv)
{
    /*
     * ks4200 function main, runs the ks4200 game
     */
    ifstream maptest(".ksmapfile");
    if (maptest)
    {
        maptest >> file_level_total;
        maptest.close();
        read_map(".ksmapfile");
    }
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

    while (i == 1)
    {
        if (cli == "debug")
        {
            //sorry, debug stripped after SKS3 release
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
