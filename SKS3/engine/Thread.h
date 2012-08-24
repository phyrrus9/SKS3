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
 =================================================================
 File: Thread.h
 Description: Thread class functions, most of them are preserved
 from the original Tpool for osx port by airekans (found on his
 github at https://github.com/airekans/Tpool ) but there are a
 few modifications made for better handling.
 Authors: phyrrus9 <phyrrus9@gmail.com>
 airekans (Yaolong Huang) airekans@gmail.com
 *****************************************************************/
///////////////////////////////////////////////////////////////
//Tpool-iPhone project. I don't know really how much of this //
//will be kept up-to-date but it is worth while to mess with //
//it a little bit if you want to. This must be build from the//
//command-line using 'make' because otherwise it will build a//
//non-signed .app GUI file (which will crash due to lack of a//
//appdelegate). I just fetch the binary file and chmod it ...//
//This code is distributed in the hope that it will be useful//
//to somebody, this code comes with no warranty, it is uo to //
//the programmer to ensure the safety of the user for whom he//
//is writing code using this library for This library is open//
//source in all ways, meaning there is absolutely no lisence //
//agreement accompanied with it, though I would be happy if  //
//this comment block was left in the code. Feel free to add  //
//your name under mine if you like but please leave my coment//
//block intact (with any modifications you wish to perform)..//
//original code by Ethan Laur (phyrrus9) <phyrrus9@gmail.com>//
///////////////////////////////////////////////////////////////
#ifndef _TPOOL_THREAD_H_
#define _TPOOL_THREAD_H_

#include <pthread.h>
#include <cstdlib>
namespace tpool {
    
    class Thread {
    private:
        static void* thread_func(void* thisObj);
        
        struct Tid {
            bool isValid;
            pthread_t id;
            
            Tid() : isValid(false)
            {
            }
        };
        
    public:
        typedef Tid ThreadId;
        
        virtual ~Thread() {}
        
        ThreadId Run();
        void Stop();
        ThreadId GetId() const;
        pthread_t GetPid() const;
        //bool _open; //don't use this please
        //bool isrunning() const; //returns true if task is running
    protected:
        virtual void Entry() = 0;
        
    private:
        ThreadId m_threadId;
    };
    
}

#endif