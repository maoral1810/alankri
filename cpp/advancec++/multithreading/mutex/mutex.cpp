#include <pthread.h> // pthread_mutex_t, pthread_mutex_lock, pthread_mutex_unlock
#include <errno.h>   // EINVAL
#include <assert.h>  // assert
#include "mutex.hpp"
#include "mutex_exceptions.hpp"

namespace experis {

MyMutex::MyMutex() {
    m_lock = PTHREAD_MUTEX_INITIALIZER;
}

MyMutex::~MyMutex() 
{

}

void MyMutex::Lock(){

    if(pthread_mutex_lock(&m_lock))
    {
        assert(!"mutex lock failed");
    }
}

void MyMutex::Unlock() {
    if(pthread_mutex_unlock(&m_lock))
    {
        assert(!"mutex unlock failed");
    }
}

}//namespace experis