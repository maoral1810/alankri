#include <pthread.h>
#include <exception>
#include <errno.h> //value return from mutex
#include <cassert>
#include "mutex.hpp"
#include "mutex_exception.hpp"

namespace experis{

Mutex::Mutex(){
    mutexInit();
}

pthread_mutex_t& Mutex::GetMutex(){

    return m_mutex;
}

void Mutex::mutexInit(){

    int sts = pthread_mutex_init(&m_mutex, 0);
    if (0 != sts)
    {
        if (sts == EBUSY){
            throw InitPrevException();
        }
        else if (sts == EINVAL){
            throw InvalidException();
        }
        else if (sts == EPERM){
            throw InitPrivilegeException();
        }
        else if (sts == EAGAIN || sts == ENOMEM){
            throw InitNoResourcesException();
        }
        else{
            assert(!"pthread_mutex_init invalid error option");
        }
    }
}

Mutex::~Mutex(){

    int sts = pthread_mutex_destroy(&m_mutex);
    if (0 != sts){
        if (sts == EBUSY){
            throw MUDestroyLockOrRefException();
        }
        else if (sts == EINVAL){
            throw MUDestroyInvalidException();
        }
        else{
            assert(!"pthread_mutex_delete invalid error option");
        }
    }
}

void Mutex::Lock(){
    int sts = pthread_mutex_lock(&m_mutex);
    if (0 != sts){
        if (sts == EINVAL){
            throw InvalidException();
        }
        else if (sts == EDEADLK){
            throw AlreadyOwnException();
        }
        else if (sts == EPERM){
            throw NotOwnException();
        }
        else{
            assert(!"pthread_mutex_lock invalid error option");
        }
    }
}

void Mutex::UnLock(){
    int sts = pthread_mutex_unlock(&m_mutex);
    if (0 != sts){
        if (sts == EINVAL){
            throw InvalidException();
        }
        else if (sts == EDEADLK){
            throw AlreadyOwnException();
        }
        else if (sts == ENOMEM){
            throw LimitException();
        }
        else if (sts == EPERM){
            throw NotOwnException();
        }
        else{
            assert(!"pthread_mutex_unlock invalid error option");
        }
    }
}

} //namespace experis