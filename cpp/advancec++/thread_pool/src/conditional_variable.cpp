
#include "conditional_variable.hpp"

namespace experis{

ConditionalVariable::ConditionalVariable(Mutex& a_mutex)
: m_mutex(a_mutex)
{
    int sts = pthread_cond_init(&m_condition,0);
    if(0!=sts){
        if(sts == EBUSY){
            throw InitPrevException();
        }
        else if (sts == EINVAL){
            throw InvalidException();
        }
        else if(sts == EPERM){
            throw InitPrivilegeException();
        }
        else if (sts== EAGAIN || sts==ENOMEM){
           throw InitNoResourcesException();
        }
        else {
            assert(!"pthread_cond_init invalid error option");
        }
    }
}

ConditionalVariable::~ConditionalVariable() {
	int sts= pthread_cond_destroy(&m_condition);
    if (0 != sts){
        if (sts == EBUSY){
            throw DestroyLockOrRefException();
        }
        else if (sts == EINVAL){
            throw InvalidException();
        }
        else{
            assert(!"pthread_cond_destroy invalid error option");
        }
    }
}

// mutex is block and thread enter himself to waiting queue wait for signal or broadcast
void ConditionalVariable::Wait() {
    
    int sts= pthread_cond_wait( &m_condition,&(m_mutex.GetMutex()));
     if (0 != sts){
        if (sts == EINVAL){
            throw WaitInvalidException();
        }
        else if (sts == EPERM){
            throw WaitNotOwnException();
        }
        else{
            assert(!"pthread_cond_wait invalid error option");
        }
    }
}


 //wake up one thread waiting for signal in condition queue
void ConditionalVariable::Signal() {

    int sts = pthread_cond_signal(&m_condition);
    if(0!= sts){
        if (sts == EINVAL){
            throw SignalInvalidException();
        }
        else{
            assert(!"pthread_cond_signal invalid error option");
        }
    }
}

 // wake up all threads that wait for signal
void ConditionalVariable::Broadcast() {

  int sts =  pthread_cond_broadcast(&m_condition);
    if(0!= sts){
        if (sts == EINVAL){
            throw BRlInvalidException();
        }
        else{
              assert(!"pthread_cond_broadcast invalid error option");
        }
    }
}

}//namespace experis