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

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
string cli;
if (argc != 1)
  cli = "0";
else
  cli = "0";

if (cli == "1")
{
  cout << "Welcome, which game do you wish to launch?" << endl;
  cout << "NOTE: To end the game, press '!'" << endl;
  cout << "1. Key Seeker 4200 (final)" << endl;
  cout << "2. Super Key Seeker 4200 (Story Mode)" << endl;
  cout << "3. Super Key Seeker 4200 (Infinite Mode)" << endl;
  cout << "4. Super Key Seeker 4200 (Zombie Survival)" << endl;
  cout << "5. Update" << endl;
  int blarg;
  cin >> blarg;
  if (blarg == 1)
    system("/usr/bin/ks4200.unix");
  if (blarg == 2)
    system("/usr/bin/sks4200-single.unix");
  if (blarg == 3)
    system("/usr/bin/sks4200-rand.unix");
  if (blarg == 4)
    system("/usr/bin/sks4200-zom.unix");
  if (blarg == 5)
    system("/usr/bin/sks4200-update");
}
}
