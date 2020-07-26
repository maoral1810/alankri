#ifndef MUTEX_HPP
#define MUTEX_HPP

#include <pthread.h> // pthread_mutex_t

#include "common_utils.hpp"

namespace smart_home {
class CondVar;

class Mutex : private Uncopyable {
public:
    Mutex();
    ~Mutex() NOEXCEPTIONS;

    void Lock();
    void Unlock();
    
protected:
    friend class CondVar; // friend void CondVar::Wait
    pthread_mutex_t* GetNativeMutex() NOEXCEPTIONS;

private:
    int InitTryAgain();
private: 
    pthread_mutex_t m_lock;
};


class MutexGuard : private Uncopyable {
public:
    MutexGuard(Mutex& a_mutex);
    ~MutexGuard();

private:
    Mutex& m_lock;
};

}// namespace smart_home

#endif // MUTEX_HPP
