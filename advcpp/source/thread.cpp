#include <pthread.h> // pthread create
#include <iostream> // runtime_error

#include <cassert> // assert
#include <cerrno>

#include "thread.hpp"
#include "runnable.hpp"
#include "thread_exceptions.hpp"

namespace advcpp{

static void ThreadCreateErrors(int a_status);
static bool TimeJoinError(int a_status);

Thread::Thread(Runnable* a_runFunc) 
    : m_runFunc(a_runFunc)
    , m_isJoinable(true)
{
    int threadStatus = pthread_create(&m_id, 0, CallBackFunction, this);
    if(threadStatus)
    {
        ThreadCreateErrors(threadStatus);
    }
}

Thread::~Thread() 
{
    if(m_isJoinable)
    {
        this->Join();
        //assert(!"thread was not join or detach");
    }
}

void Thread::Join()
{
    if(m_isJoinable)
    {
        int Status = pthread_join(m_id, 0);
    
        if(Status)
        {
            switch (Status)
            {
                case EDEADLK:
                    throw(std::runtime_error("A deadlock was detected"));
                    break;

                default: assert(!"non doucument pthread join error");
                    break;
            }
        }
        else
        {
            m_isJoinable = false;
        }
    }
}

bool Thread::TimeJoin(const timespec& timeUntilShutDown)
{
    bool status = false;
    if (!m_isJoinable)
    {
        int retval = pthread_timedjoin_np(m_id, 0, &timeUntilShutDown);
        
        status = TimeJoinError(retval);   
        if(status) {
            m_isJoinable = false;
        }
    }
    
    return status;
}

void Thread::Cancel()
{
    int retval = pthread_cancel(m_id);
    switch (retval)
    {
        case ESRCH:
            assert(!"No thread with the ID thread could be found");
            break;
        default: /* m_isJoinable = true; */break;
    }
}

void Thread::Exit()
{
    //pthread_exit()
}

void Thread::Detach()
{
    if(m_isJoinable) {
        int detachStatus  = pthread_detach(m_id);
        
        if(detachStatus)
        {
            switch (detachStatus)
            {
            case ESRCH:
                assert(!"No thread with the ID thread could be found");
                break;
            case EINVAL:
                assert(!"thread is not a joinable thread");
                break;
            default: assert(!"non doucument pthread join error");
                break;
            }
        }  
        else {
            m_isJoinable = false;
        }
    }
}

void* Thread::CallBackFunction(void* a_object)
{
    assert(a_object);

    Thread* thread = reinterpret_cast<Thread*>(a_object);
    thread->DoWork();
    return 0;
}

void Thread::DoWork() 
{
    try {
        m_runFunc->Run();
    }
    catch(std::exception const& x)
    {
        std::cerr << x.what();
        assert(!"Rum thread fail");
    } catch(...) {
        assert(false);
    }
}

// ---------------------- error functions ---------------------
static void ThreadCreateErrors(int a_status)
{
    switch(a_status) {
        case EPERM:
            throw ThreadCreateEPERM();
            break;
        
        case EAGAIN:
            throw ThreadCreateEAGAIN();
            break;
            
        default:  
            assert(!"failed in pthread create");
            break;
    }
}

static bool TimeJoinError(int a_status)
{
    switch (a_status)
    {
        case ETIMEDOUT:
            //The call timed out before thread terminated.
            return false;
        case EDEADLK:
            throw ThreadTimeJoinEDEADLK();
            break;
        case EINVAL:
            assert(!"Another thread is already waiting to join with this thread");
            break;
        case ESRCH:
            assert(!"No thread with the ID thread could be found");
            break;
        default: break;
    }

    return true;
}


}// namespace advcpp
