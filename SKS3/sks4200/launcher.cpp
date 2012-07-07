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
