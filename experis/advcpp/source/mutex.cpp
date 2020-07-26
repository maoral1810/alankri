#include <cerrno> 
#include <iostream>  //cout for debug     
#include <cassert>      // assert

#include <pthread.h>    // pthread_mutex_t, pthread_mutex_lock, pthread_mutex_unlock
#include <unistd.h>     // usleep

#include "mutex.hpp"
#include "mutex_exceptions.hpp"

namespace advcpp {

Mutex::Mutex()
{
    int retval = InitTryAgain();
    switch (retval)
    {
        case ENOMEM:
            throw MutexInitENOMEM();
            break;
        
        case EAGAIN:
            if(InitTryAgain() == false) 
            {
                throw MutexInitEAGAIN();
            }
            break;
        
        case EPERM:
            assert(!"Mutex init error, check your attributes");
            break;
        
        case EINVAL:
            assert(!"Mutex init error, attributes are invalid");
        
        case EBUSY:
            assert(!"detected an attempt to re-initialise the object referenced by mutex, a previously initialised");
            break;

        default:
            break;
    }
}

Mutex::~Mutex() NOEXCEPTIONS
{
    int retval = pthread_mutex_destroy(&m_lock);
    switch (retval) {
        case EBUSY:
            assert(!"mutex dtor error. try to destory mutex in use by another thread");
            break;
        case EINVAL:
            assert(!"mutex dtor error. check the initiliztion in ctor");
        break;
    }
}

void Mutex::Lock() 
{
    int retval = pthread_mutex_lock(&m_lock);
    switch (retval)
    {
        case EINVAL:
            assert(!"Mutex lock error, check your attributes in initilization");
            break;
        case EAGAIN:
            throw MutexUnlockEAGAIN();
            break;

        case EDEADLK:
            throw MutexlockEDEADLK();
            break;
        
        default:
            break;
    }
}

void Mutex::Unlock() 
{
    int retval = pthread_mutex_unlock(&m_lock);
    switch (retval)
    {
        case EPERM:
            throw MutexUnlockEPERM();
            break;
        
        case EAGAIN:
            throw MutexUnlockEAGAIN();

        case EINVAL:
            assert(!"Mutex unlock error, check your attributes in initilization");
            break;

        default:
            break;
    }
}

int Mutex::InitTryAgain() 
{
    int numOfTrys = 3;
    unsigned int timeForTryAgain = MicroToMili(4);
    int retval = 1;

    while(0 != numOfTrys) 
    {
        retval = pthread_mutex_init(&m_lock, 0);
        if(0 == retval)
        {
            break;
        }
        usleep(timeForTryAgain);
        --numOfTrys;
        timeForTryAgain *= 2;
    }

    return retval;
}

pthread_mutex_t* Mutex::GetNativeMutex() NOEXCEPTIONS
{
     return &m_lock; 
}


//----------------------mutex guard -------------
MutexGuard::MutexGuard(Mutex& a_mutex)
    : m_lock(a_mutex)
{
    m_lock.Lock();
}

MutexGuard::~MutexGuard()
{
    try{
        m_lock.Unlock();
    }
    catch(std::exception &ex)
    {
        assert(!ex.what());
    }
}



}// advcpp