#ifndef __CONDISION_VARIABLE_HPP__
#define __CONDISION_VARIABLE_HPP__

#include "mutex.hpp"

namespace experis {

class CondVar {
public:
    CondVar(MyMutex& a_mutex)throw();
    ~CondVar()throw();

    //API Function
    void Wait() throw();
    void notifyAll()throw();
    void notifyOne()throw();

    pthread_mutex_t C_Mutex()const{ m_mutex.GetMutex(); }
    // add getMutex C_Mutex

private:
    CondVar(const CondVar& a_other);
    CondVar& operator=(const CondVar& a_other);
    
    MyMutex& m_mutex;
    pthread_cond_t m_condVar;
};



}// namespace experis


#endif //__CONDISION_VARIABLE_HPP__
