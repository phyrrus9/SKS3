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