#ifndef __READ_WORK_HPP__
#define __READ_WORK_HPP__

#include "runnable.hpp"
#include "cyclic_waitable_q.hpp"

namespace experis {

class MyRead : public Runnable {
public:
    MyRead(int a_iteration , WaitCycQ<int>* a_queue)throw();
    virtual ~MyRead()throw(){}
    
    // API functions
    virtual void Run();

private:
    MyRead& operator= (const MyRead& a_thread);// not assignable
    MyRead(const MyRead& a_thread);

    int m_iteration;
    WaitCycQ<int>* m_queue;
};

}// namespace experis

#endif //__READ_WORK_HPP__