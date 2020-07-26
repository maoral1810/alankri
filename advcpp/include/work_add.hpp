#ifndef __WORK_ADD_HPP__
#define __WORK_ADD_HPP__

#include "runnable.hpp"

namespace advcpp {

class WorkAdd : public Runnable {
public:
    WorkAdd(int *g_num)
    :m_gNum(g_num)
    {

    }
    virtual ~WorkAdd(){}
    
    // API functions
    virtual void Run();

private:
    WorkAdd& operator= (const WorkAdd& a_thread);// not assignable
    WorkAdd(const WorkAdd& a_thread);

    int *m_gNum;
};

}// namespace advcpp

#endif //__WORK_ADD_HPP__