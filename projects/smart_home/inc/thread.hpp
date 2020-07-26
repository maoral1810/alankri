#ifndef __THREAD_HPP__
#define __THREAD_HPP__

#include <pthread.h>
#include <unistd.h> /* sleep */
#include "runnable.hpp"
#include "common_utils.hpp"

namespace smart_home {

class Thread: private Uncopyable {

public:
    Thread(Runnable* a_runFunc);
    ~Thread();
    
    void Join();
    void Detach();
    bool TimeJoin(const timespec& timeUntilShutDown);
    void Cancel();
    void Exit();
    
private:
    void DoWork();
    static void* CallBackFunction(void* a_object);
    
    pthread_t m_id;
    Runnable* m_runFunc;
    bool m_isJoinable;
};

}// namespace smart_home

#endif //__THREAD_HPP__