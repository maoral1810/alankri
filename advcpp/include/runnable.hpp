#ifndef __RUNNABLE_HPP__
#define __RUNNABLE_HPP__

#include "common_utils.hpp"

namespace advcpp {

class Runnable : private Uncopyable {
public:
    Runnable(){}
    virtual ~Runnable(){}
    
    // API functions
    virtual void Run() = 0;
};

}// namespace advcpp

#endif //__RUNNABLE_HPP__