#ifndef CONDISION_VARIABLE_HPP
#define CONDISION_VARIABLE_HPP

#include <cerrno>
#include <cassert>

#include <pthread.h>

#include "mutex.hpp"
#include "common_utils.hpp"
#include "condition_variable_exceptions.hpp"

namespace smart_home{

class CondVar : private Uncopyable {
public:
    CondVar();
    ~CondVar() NOEXCEPTIONS;

    template<class Predicate>
    void Wait(Mutex& a_mutex, Predicate a_pradicateFunc);
    void NotifyAll() NOEXCEPTIONS;
    void NotifyOne() NOEXCEPTIONS;

private:
    int InitTryAgain();
    void NotifyAllAndDestroy();
    
    pthread_cond_t m_condVar;
};

template<class Predicate>
void CondVar::Wait(Mutex& a_mutex, Predicate a_pradicateFunc)
{
    int retval;

    while(a_pradicateFunc() )
    {
        retval = pthread_cond_wait(&m_condVar, a_mutex.GetNativeMutex() );
        switch (retval)
        {
            case EINVAL:
                assert(!"The value specified by cond, mutex, or abstime is invalid");
                break;
            case EPERM:
                throw ConditionVarWaitEPERM();
                break;
            default:
                break;
        }
    }
}

//------------------CondVar Guard --------------------------

class CondVarGuard : private Uncopyable {
public:
    CondVarGuard(CondVar& a_conditionVariable);
    ~CondVarGuard();

private:
    CondVar& m_conditionVariable;
};

}// namespace smart_home


#endif //__CONDISION_VARIABLE_HPP__
