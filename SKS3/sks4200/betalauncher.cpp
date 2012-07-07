/*
 * SKS4200 GUI Launcher
 * Copyright 2011 Ethan Laur
 *
 */

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
