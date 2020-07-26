#ifndef UNIT_TEST_FUNCTIONS
#define UNIT_TEST_FUNCTIONS

#include "runnable.hpp"
#include "common_utils.hpp"
#include "mutex.hpp"

namespace smart_home
{
class MyMutex;

class SafeIncrement : public Runnable
{
public:
    SafeIncrement(MyMutex& a_mutex, int* a_num, int a_numOfItr) NOEXCEPTIONS
    : Runnable()
    , m_mutex(a_mutex) 
    , m_num(a_num)
    , m_numOfItr(a_numOfItr)
    {
    }

    virtual ~SafeIncrement() NOEXCEPTIONS {}

    virtual void Run() NOEXCEPTIONS
    {
        m_mutex.Lock();
        for(int i = 0; i < m_numOfItr; ++i)
        {
            ++*m_num;   
        }
        m_mutex.Unlock();
    }

private:
    Mutex& m_mutex;
    int* m_num;
    int m_numOfItr;
};

class UnsafeIncrement : public Runnable
{
public:
    UnsafeIncrement(int* a_num, int a_numOfItr) NOEXCEPTIONS
    : Runnable()
    , m_num(a_num)
    , m_numOfItr(a_numOfItr) 
    {
    }
    virtual ~UnsafeIncrement() NOEXCEPTIONS {}

    virtual void Run() NOEXCEPTIONS
    {
        for(int i = 0; i < m_numOfItr; ++i)
        {
            ++*m_num;
        }
    }

private:
    int* m_num;
    int m_numOfItr;
};

} //namespace smart_home

#endif //UNIT_TEST_FUNCTIONS