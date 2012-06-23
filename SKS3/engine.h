/*
 * Super Key Seeker Version 3
 * Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 * This software is free, it may be customized, redistributed, blah blah blah...
 */
#ifndef SKS3_engine_h
#define SKS3_engine_h
#include <iostream>
#include <fstream>
#include <curses.h>
#include <iomanip>
#include <signal.h>
#include "enumerations.h"
#include "environment.h"
#define clear() system("clear")
const char echar = '~';
using namespace std;
char getch_(void);
void enginecmd(string, string);
void showhelp(void);
void save(void);
void restore(void);
void display(void);
void colorify(void);
void colorify(color);
void terminate(int);
#include "movement.h"
#include "attack.h"
#endif
