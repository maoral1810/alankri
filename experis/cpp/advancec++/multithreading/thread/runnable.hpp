#ifndef __RUNNABLE_HPP__
#define __RUNNABLE_HPP__

namespace experis {

class Runnable {
public:
    Runnable(){}
    virtual ~Runnable(){}
    
    // API functions
    virtual void Run() = 0;

private:
    Runnable& operator= (const Runnable& a_thread);// not assignable
    Runnable(const Runnable& a_thread);

};

}// namespace experis

#endif //__RUNNABLE_HPP__