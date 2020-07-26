#ifndef __MY_WORK_HPP__
#define __MY_WORK_HPP__

#include "runnable.hpp"
namespace experis {

class MyWork : public Runnable {
public:
    MyWork(){}
    virtual ~MyWork(){}
    
    // API functions
    virtual void Run();

private:
    MyWork& operator= (const MyWork& a_thread);// not assignable
    MyWork(const MyWork& a_thread);

};

}// namespace experis

#endif //__MY_WORK_HPP__