#include <unistd.h> // sleep
#include <cassert>  // assert
#include <cerrno>  // 
#include <iostream>
#include "thread_exceptions.hpp"
#include "thread.hpp"


namespace experis{

void* Thread::StartWork(void* a_obj){

    Thread* thread = reinterpret_cast<Thread*>(a_obj);
    thread->DoWork();
}

Thread::Thread(Runnable* a_run):m_run(a_run){
    
   int sts = pthread_create(&m_id,NULL,StartWork,this);
     if(0 != sts){
        assert(EINVAL != sts); 
        switch (sts){
        case EPERM:
            throw ThreadPermissionException();
            break;
        case EAGAIN:
            throw ThreadResourcesException();
            break;
        default:
            assert(!"non documented error of pthread_create ");
            break;
        }
    }
}

Thread::~Thread(){
    int sts = pthread_join(m_id,NULL);
    assert(0 == sts);
}

void Thread::DoWork(){
    m_run->Run();
}


} // namespace experis