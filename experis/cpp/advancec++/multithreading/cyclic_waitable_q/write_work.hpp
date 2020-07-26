#ifndef __WRITE_WORK_HPP__
#define __WRITE_WORK_HPP__

#include "runnable.hpp"
#include "cyclic_waitable_q.hpp"

namespace experis {


class MyWrite : public Runnable {

public:
    MyWrite(unsigned int a_from , unsigned int a_to, WaitCycQ<int>* a_queue)throw();
    virtual ~MyWrite(){}
    
    // API functions
    virtual void Run();

private:
    MyWrite& operator= (const MyWrite& a_thread);// not assignable
    MyWrite(const MyWrite& a_thread);

    unsigned int m_from;
    unsigned int m_to;
    WaitCycQ<int>* m_queue;
};

}// namespace experis

#endif //__READ_WORK_HPP__