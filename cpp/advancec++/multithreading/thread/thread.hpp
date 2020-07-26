#ifndef __THREAD_HPP__
#define __THREAD_HPP__

#include "runnable.hpp"
#include <pthread.h>
#include <unistd.h> /* sleep */

namespace experis{

class Thread {

public:
    Thread(Runnable* a_runFunc);
    ~Thread();

private:
    void DoWork();
    static void* CallBackFunction(void* a_object);
    Thread& operator= (const Thread& a_thread);// not assignable
    Thread(const Thread& a_thread);// not copyable
    
    pthread_t m_id;
    Runnable* m_runFunc;
};

}// namespace experis

#endif //__THREAD_HPP__