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
upload += " ftp://ss14bouchaj:jared46562@student.eup.k12.mi.us/public_html/MUD/maps/";
//cout << upload.c_str() << endl; //debug
system(upload.c_str());
cout << endl << endl << "Map uploaded!" << endl;
}
