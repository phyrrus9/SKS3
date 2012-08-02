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
 * Super Key Seeker 3 map creator
 * Copyright Ethan Laur 2011
 * Open source without ftp details
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

using namespace std;

main() {
system("clear");
string devname, title, filename;
bool visible;
cout << "Welcome to the sks3 map creator!" << endl << "You may use the following items (limit in ())" << endl;
cout << "t: teleport (1)\n@: start position (1)\nb: buy station (5)\nz: zombie (100)\nB: boss (1)\nc: coin (50)\nk: key (15)\ns: supercoin (2)\n#: wall (none)\n";
sleep(10);
system("clear");
cout << "Please enter your name (one word no spaces, periods, etc only _" << endl;
cin >> devname;
cout << "Please enter the title of your map" << endl;
cin >> title;
cout << "Do you want your map to be visible by default (do not need to explore)? use 1/0" << endl;
cin >> visible;
filename = devname + "-" + title + ".sks";

ofstream outfile;
outfile.open (filename.c_str());
outfile << "Developer: " << devname << " Title: " << title << " Visible " << visible << "\n";
outfile << "#,#,#,#,#,#,#,#,#,#,#,#,#,#,#,#,#,#,#,#,\n";
outfile << "#,@, , , , , , , , , , , , , , , , , ,#,\n";
outfile << "#, , , , , , , , , , , , , , , , , , ,#,\n";
outfile << "#, , , , , , , , , , , , , , , , , , ,#,\n";
outfile << "#, , , , , , , , , , , , , , , , , , ,#,\n";
outfile << "#, , , , , , , , , , , , , , , , , , ,#,\n";
outfile << "#, , , , , , , , , , , , , , , , , , ,#,\n";
outfile << "#, , , , , , , , , , , , , , , , , , ,#,\n";
outfile << "#, , , , , , , , , , , , , , , , , , ,#,\n";
outfile << "#, , , , , , , , , , , , , , , , , , ,#,\n";
outfile << "#, , , , , , , , , , , , , , , , , , ,#,\n";
outfile << "#, , , , , , , , , , , , , , , , , , ,#,\n";
outfile << "#, , , , , , , , , , , , , , , , , , ,#,\n";
outfile << "#, , , , , , , , , , , , , , , , , , ,#,\n";
outfile << "#, , , , , , , , , , , , , , , , , , ,#,\n";
outfile << "#, , , , , , , , , , , , , , , , , , ,#,\n";
outfile << "#, , , , , , , , , , , , , , , , , , ,#,\n";
outfile << "#, , , , , , , , , , , , , , , , , , ,#,\n";
outfile << "#, , , , , , , , , , , , , , , , , ,t,#,\n";
outfile << "#,#,#,#,#,#,#,#,#,#,#,#,#,#,#,#,#,#,#,#}\n";
outfile.close();
string edit = "nano ";
edit += filename.c_str();
system(edit.c_str());
system("clear");
cout << "Uploading map to server" << endl;
sleep(3);
string upload = "curl --upload-file ./";
upload += filename.c_str();
upload += " ftp://user:password@server/public_html/MUD/maps/";
//cout << upload.c_str() << endl; //debug
system(upload.c_str());
cout << endl << endl << "Map uploaded!" << endl;
}
