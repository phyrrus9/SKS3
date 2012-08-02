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
#include <fstream>
#define TEL "\033[22;31mt\e[m"

using namespace std;

string grid[2][25][400]; //so we don't need to include the maps file

#include "engine.cpp"

string menu[] =
{
"#", "#",
" ", "Key Seeker 4200",
" ", "Super Key Seeker 4200 (Story Mode)",
" ", "Super key Seeker 4200 (Infinite Mode)",
" ", "Super Key Seeker 4200 (Zombie Survival)",
" ", "Super Key Seeker 4200 (Boss Rush [beta 2])",
" ", "Super Key Seeker 3 (Story Mode [Alpha])",
" ", "Super Key Seeker Map Creator",
" ", "Update",
"#"
};

int main(int argc, char** argv)
{
    int i;
    ifstream infile(".sks4200");
    infile >> i;
    if (i < 0 || i > 15)
    {
      ofstream make;
      make.open (".sks4200");
      make << "0";
      make.close();
      cout << "First run, initialized please run again" << endl;
      exit(1);
    }
    i += 1;
    ofstream outfile;
    outfile.open (".sks4200");
    outfile << i;
    outfile.close();
string cli;
if (argc != 1)
  cli = argv[1];
else
  cli = "1";

if (i >= 10) //auto-update every 10 runs
{
  cli = "0";
  ofstream outfile;
  outfile.open(".sks4200");
  outfile << "0";
  outfile.close();
}

cout << cli << endl;

if (cli == "1")
{

pos = 2;
system("clear");
string temp = movest();
bool i = true;
while (i)
{
menu[pos] = "@";
cout << "Welcome to Super Key Seeker 4200(Engine: " << engine << ")! Please use <w a s d> then hit enter to navigate menu." << endl << "(move to the right (d) to select). (during game, press ! to exit)." << endl << endl;
cout << menu[0] << menu[1] << "##############################################" << endl;
cout << menu[2] << " " << menu[3] << endl;
cout << menu[4] << " " << menu[5] << endl;
cout << menu[6] << " " << menu[7] << endl;
cout << menu[8] << " " << menu[9] << endl;
cout << menu[10] << " " << menu[11] << endl;
cout << menu[12] << " " << menu[13] << endl;
cout << menu[14] << " " << menu[15] << endl;
cout << menu[16] << " " << menu[17] << endl;
cout << menu[18] << "##############################################" << endl << ">";
string null = movest();
int prev = pos;
if (null == "w")
pos = pos - 2;
if (null == "a")
pos = pos - 1;
if (null == "s")
pos = pos + 2;
if (null == "d")
pos = pos + 1;
menu[prev] = " ";

if (menu[pos] == "#")
pos = prev;

system("clear");

if (pos == 3)
{
system("/usr/bin/ks4200.unix");
exit(0);
}

if (pos == 5)
{
system("/usr/bin/sks4200-single.unix 1");
exit(0);
}

if (pos == 7)
{
system("/usr/bin/sks4200-rand.unix");
exit(0);
}

if (pos == 9)
{
system("/usr/bin/sks4200-zom.unix");
exit(0);
}

if (pos == 11)
{
system("/usr/bin/sks4200-boss.unix");
exit(0);
}

if (pos == 13)
{
system("/usr/bin/sks4200-single.unix 2");
exit(0);
}

if (pos == 15)
{
system("/usr/bin/sks4200-mapcreator.unix");
exit(0);
}

if (pos == 17)
{
system("/usr/bin/sks4200-update");
system("clear");
system("/usr/bin/sks4200");
exit(0);
}

} // end while
} // end if cli

if (cli == "0")
{
system("/usr/bin/sks4200-update");
system("clear");
system("/usr/bin/sks4200 1");
exit(0);
} // end updater if
} // end function main
