#ifndef __R_THREAD_HPP__
#define __R_THREAD_HPP__

#include "thread.hpp"
#include "runnable.hpp"

namespace experis{

class RThread : public Thread {
public:
    RThread(Runnable* a_runFunc)
    :m_runFunc(a_runFunc)
    {

    }
    virtual ~RThread(){}
    
    virtual void DoWork();
private:

    RThread& operator= (const RThread& a_other);// not assignable
    RThread(const RThread& a_other);
    
    Runnable* m_runFunc;
};

}// namespace experis

#endif //__R_THREAD_HPP__