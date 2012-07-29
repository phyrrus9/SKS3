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