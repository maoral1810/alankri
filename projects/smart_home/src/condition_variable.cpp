#include <cassert>
#include <cerrno>

#include <pthread.h> // pthread_code_wait
#include <unistd.h> // usleep

#include "condition_variable.hpp"
#include "condition_variable_exceptions.hpp"

namespace smart_home {

static void ConditionVariableCreateErrors(int a_status);

CondVar::CondVar()
{
    int retval = InitTryAgain();
    
    ConditionVariableCreateErrors(retval);
}

CondVar::~CondVar() NOEXCEPTIONS
{
    int retval = pthread_cond_destroy(&m_condVar);
    switch (retval)
    {
        case EBUSY:
            NotifyAllAndDestroy();
            break;
        case EINVAL:
            assert(!"The value specified by cond is invalid");
            break;
        default:
            break;
    }
}

void CondVar::NotifyOne() NOEXCEPTIONS
{
    int retval = pthread_cond_signal(&m_condVar);
    if(0 != retval) {
        assert(!"The value cond does not refer to an initialized condition variable");
    }
}

void CondVar::NotifyAll() NOEXCEPTIONS 
{
    int retval = pthread_cond_broadcast(&m_condVar);
    if(0 != retval) {
        assert(!"The value cond does not refer to an initialized condition variable");
    }
}

int CondVar::InitTryAgain() 
{
    int numOfTrys = 3;
    unsigned int timeForTryAgain = MicroToMili(4);
    int retval = 1;

    while(0 != numOfTrys) 
    {
        retval = pthread_cond_init(&m_condVar, 0);
        if(0 == retval)
        {
            break;
        }
        usleep(timeForTryAgain);
        --numOfTrys;
        timeForTryAgain *= 2;
    }

    return retval;
}

void CondVar::NotifyAllAndDestroy()
{
    do
    {
        NotifyAll();
    }
    while (0 != pthread_cond_destroy(&m_condVar));
}

//--------------------- status functions ---------------

static void ConditionVariableCreateErrors(int a_status)
{
    switch (a_status)
    {
        case EAGAIN:
            throw ConditionVarInitEAGAIN();
            break;
        
        case ENOMEM:
            throw ConditionVarInitENOMEM();
            break;
        
        case EBUSY:
            assert(!"detected an attempt to reinitialize the object referenced by cond, a previously initialized, but not yet destroyed");
            break; 

        case EINVAL:
            assert(!"The system lacked the necessary resources (other than memory) to initialize another condition variable");
            break;
        
        default:
            break;
    }
}

//------------------------- condvar guard -----------------
CondVarGuard::CondVarGuard(CondVar& a_conditionVariable)
    : m_conditionVariable(a_conditionVariable)
{}

CondVarGuard::~CondVarGuard()
{
    m_conditionVariable.NotifyAll();
}

}// namespace smart_home