#ifndef __RUNNABLE_HPP__
#define __RUNNABLE_HPP__

#include "common_utils.hpp"

namespace smart_home {

class Runnable : private Uncopyable {
public:
    Runnable(){}
    virtual ~Runnable(){}
    
    // API functions
    virtual void Run() = 0;
};

}// namespace smart_home

#endif //__RUNNABLE_HPP__