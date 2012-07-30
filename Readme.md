About
-----
This game is a simple, yet complex, single player and two player command line dungeon-like game.
I used c++ making it and my Tpool framework (on my github under tpool) in order to do some fancy stuff
like add colors, threading, music, sound effects, automatic screen refreshing, etc.

This project should build on most systems (you need ncurses). I have only tested it (current as of 7/30/2012)
on Mac OS X 10.8, though it should work on OSX 10.6-10.8 and most if not all linux systems.

If you cannot compile on a system, please email me! phyrrus9@gmail.com

Building
--------
I made building this beast fairly simple, using a makefile.

If you have ncurses and pthread libraries installed, you can just type 'make linux'
and it will build fine, this works on osx as well. I also made a special version that
uses xcode (in case your g++ isnt working), just type 'make osx'.

SKS4200 is a large compile (about 5 minutes on my 2.4ghz dual core), so it got its
own build rule. Type 'make sks4200'.

Cleaning up:
Cleaning is just as you would normally 'make clean'

Installing:
To install (copy all the files and such), just 'make install'

Building .pkg:
The pkg builder requires all the files to be built, so in order to be able to do it,
you will need to 'make clean osx sks4200' and then run the package build, then do a
'make clean'
