About
-----
This game is a simple, yet complex, single player and two player command line dungeon-like game.
I used c++ making it and my Tpool framework (on my github under tpool) in order to do some fancy stuff
like add colors, threading, music, sound effects, automatic screen refreshing, etc.

This project should build on most systems (you need ncurses). I have only tested it (current as of 7/30/2012)
on Mac OS X 10.8, though it should work on OSX 10.6-10.8 and most if not all linux systems.

If you cannot compile on a system, please email me! phyrrus9@gmail.com

Notes about version 3.0
------------------------
As of SKS3 engine 3.0, there are a few changes (besides the massive modifications to the environment). I
have now found a way to fix that pesky save issue (where saving only works once per game play on the same
filename, save.dat). This is good right? No, because it means that there are a few hooks that have been
broken and others that have changed. You now are required to use the save slot method (which I also fixed
for this version) for all saves and restores. The game now saves your progress every 60 seconds (meaning
up to 60 autosaves) into slot a(0). This is the good part. I now have implemented a lot of ncurses stuff
and most of the game uses nwin for windows. This library must be compiled seperate (like streamlib) for
any operating system other than OS 10. This will be the last major release of SKS3, sorry. After that we
will simply rename the game to SKS4 and start over.

Building
--------
I made building this beast fairly simple, using a makefile.

As of version 3.0, 'make osx' became a little bit more complicated to use, so if
you just run 'make' it will build in the 'make linux' fassion (which has now
been removed altogether. It is but a link now.

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
