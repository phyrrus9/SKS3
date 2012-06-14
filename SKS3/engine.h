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
#include <string.h>
#include <signal.h>
#define clear() system("clear")
const char echar = '~';
using namespace std;
enum direction { N, S, E, W, SAV, RES, QUI, HLP, NIL };
enum color { RED, GREEN, BLUE, NORMAL };
namespace character
{
    enum player { N, S, E, W};
}
char getch_(void);
void enginecmd(string, string);
void showhelp(void);
void save(void);
void restore(void);
void display(void);
void eat(int p);
void populate(void);
void move(direction);
void turn(direction);
void showmap(void);
void showplayer(void);
void light(int);
void colorify(void);
void colorify(color);
void terminate(int);
struct _environment
{
    char map[900] = "\0", grid[900] = "/0";
    char * view;
    bool showmap = true, single = false;
    int health = 100, lives = 3, score = 30, position = 0, moves = 1, kills = 0, kills_needed = 0,
    levels_completed = 0;
    string savefile = "save.dat";
    color bgcolor = NORMAL, playercolor = RED;
    character::player player = character::N;
};
#endif
