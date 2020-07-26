#include <pthread.h> // pthread create
#include <iostream> // runtime_error
#include <assert.h> // assert
#include <errno.h>
#include "thread.hpp"
#include "runnable.hpp"
#include "thread_exceptions.hpp"

namespace experis{

Thread::Thread(Runnable* a_runFunc) 
    : m_runFunc(a_runFunc)
    
{
    int threadStatus = pthread_create(&m_id, 0, CallBackFunction, this);
    switch(threadStatus){
        case EPERM:
            throw EPERMExeption;
            break;
        
        case EAGAIN:
            throw EAGAINExeption;
            break;
            
        default:  
            assert("failed in pthread create");
            break;
    }
}

Thread::~Thread() {
    int joinStatus  = pthread_join(m_id, 0);
    if(joinStatus)
    {
switch (joinStatus)
    {
    case EDEADLK:
        throw(std::runtime_error("A deadlock was detected"));
        break;
/*     case EINVAL:
        assert(!"EINVAL was detected");
        break;
    case ESRCH:
        assert(!"ESRCH was detected");
        break; */
    default: assert(!"non doucument pthread join error");
        break;
    }
    }
    
}

void* Thread::CallBackFunction(void* a_object)
{
    Thread* thread = reinterpret_cast<Thread*>(a_object);
    thread->DoWork();
    return 0;
}

void Thread::DoWork() {

    m_runFunc->Run();
}

}// namespace experis
