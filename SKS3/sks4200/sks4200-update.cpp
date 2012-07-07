#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

main()
{
  cout << "Downloading new package" << endl;
  system("wget http://207.75.208.4/~ss14bouchaj/MUD/sks4200.deb");
  cout << "Running DPKG" << endl;
  system("sudo dpkg -i sks4200.deb");
  cout << "Cleaning up" << endl;
  system("rm sks4200.deb");
  cout << "Upgrade complete!" << endl;
}
