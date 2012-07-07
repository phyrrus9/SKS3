/*
 * SKS 4200 Defines list
 * Copyright Ethan Laur 2011
 * This is where all of the GLOBAL vars are defined
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

string map[400];

int pos = 81, i = 1, coins = 0, keys = 0, health = 100, atk = 0, def = 0, score = 0, deadzombies = 0, lvl = 0, completedlevels = 0, awards = 0, dzc = 0, walls = 0, levels = 25, ss[10], hits = 0, boss[11] = {250, 250, 250, 500, 500, 500, 500, 500, 500, 500, 500}, gam, moveup[2] = {0, 0}, shealth;
string zprev[400], savecode, names[25] = {"Beginner", "Nazi Fun", "Triangles", "Dead", "America", "X marks the spot"};
string developer[25] = {"phyrrus9", "phyrrus9", "phyrrus9", "phyrrus9", "phyrrus9", "phyrrus9"};
bool suicidal = false, easy = false, normal = false, hard = false, insane = false, peaceful = false, cheats = false, redeemed[] = {false, false, false, false, false}, mysterybox = false, mapview[25] = {false, false, false, false, true, false};

int start[][25] = {
{81, 21, 378, 21, 210, 21, 378, 21, 21, 81, 21, 81, 21, 21, 81, 21, 38, 21, 21, 21, 81, 41, 21, 41, 378},
{65, 21, 81, 378, 21, 210, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21} //6 currently
};
