/*
 * Super Key Seeker Version 3
 * Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 * This software is free, it may be customized, redistributed, blah blah blah...
 */
#ifndef SKS3_engine_h
#define SKS3_engine_h
#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <iomanip>
#include <signal.h>
#include <string.h>
#include <sstream>
#include "socket.h"
#include "enumerations.h"
#include "environment.h"
#include "environment_functions.h"
#include "filesystem.h"
#include "movement.h"
#include "attack.h"
#include "zombie.h"
#include "Thread.h"
#ifdef __APPLE__
#define play_music(a) system(a)
#define kill_music(b) system(b)
#endif
#ifndef __APPLE__
#define play_music(a) //hello world
#define kill_music(b) //hello world
#endif
//#define endl "\n\r"
#define clear() system("clear")
#define pause() env.paused = true
#define unpause() env.paused = false
#define VERSION_BUILD "SKS3 (1.4b)"
const int portnum = 5102;
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
#endif
