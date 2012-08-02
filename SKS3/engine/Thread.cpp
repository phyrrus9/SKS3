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
#include "Thread.h"
#include <pthread.h>
#include <iostream>
#include <cstdlib>
using namespace std;
using namespace tpool;

void* Thread::thread_func(void* thisObj)
{
    Thread* obj = static_cast<Thread*>(thisObj);
    obj->Entry();
    return NULL;
}

Thread::ThreadId Thread::Run()
{
    //_open = true;
    if (pthread_create(&(m_threadId.id), NULL,
                       thread_func, (void*) this) != 0)
    {
        cerr << "pthread_create failed" << endl;
        exit(1);
    }
    
    m_threadId.isValid = true;
    return m_threadId;
}

void Thread::Stop()
{
    if (!m_threadId.isValid)
    {
        return;
    }
    
    pthread_cancel(m_threadId.id);
}

Thread::ThreadId Thread::GetId() const
{
    return m_threadId;
}

pthread_t Thread::GetPid() const
{
    return m_threadId.id; //used in checking the state of a thread
}