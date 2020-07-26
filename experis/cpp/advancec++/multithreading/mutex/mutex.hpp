#ifndef __MUTEX_HPP__
#define __MUTEX_HPP__

#include <pthread.h> // pthread_mutex_t

namespace experis {
class CondVar;

class MyMutex {

public:
    MyMutex();
    ~MyMutex();

    //API Function

    void Lock();
    void Unlock();

    pthread_mutex_t* GetMutex(){ return &m_lock; }

private:
    MyMutex(const MyMutex& a_other);
    MyMutex& operator=(const MyMutex& a_other);

    pthread_mutex_t m_lock;
};

}// namespace experis


#endif //__MUTEX_HPP__
