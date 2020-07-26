#include "mu_test.h"
#include <unistd.h> // sleep
#include <iostream> // cout
#include "condition_variable.hpp"
#include "mutex.hpp"
#include "runnable.hpp"
#include "thread.hpp"


static int g_int = 0;
static bool g_bool = true;

struct Condition {
    bool operator()() {
        return g_bool;
    }
};

class WaitFunc : public advcpp::Runnable {
public:    
    WaitFunc(advcpp::Mutex& a_mutex) :m_mutex(a_mutex) {}
    void Run() { m_mutex.Lock(); sleep(1);  m_mutex.Unlock();}
private:
    advcpp::Mutex& m_mutex;
};

struct PredicateToggler : public advcpp::Runnable {

    PredicateToggler(int a_numOfIts, advcpp::CondVar& a_condVar)
        : m_numOfIts(a_numOfIts)
        , m_condVar(a_condVar)
    { }

    void Run()
    {
        for (int i = 0; i < m_numOfIts; ++i)
        {
            m_condVar.NotifyOne();
        }
        g_bool = false;
        m_condVar.NotifyAll();
    }
    int m_numOfIts;
    advcpp:: CondVar& m_condVar;
};

struct IncGlobalVar : public advcpp::Runnable
{
    IncGlobalVar(int a_numOfIts, advcpp::Mutex& a_mutex, advcpp::CondVar& a_condVar)
        : m_numOfIts(a_numOfIts)
        , m_mutex(a_mutex)
        , m_condVar(a_condVar)
    { }
    
    void Run()
    {
        Condition cond;
        for (int i = 0; i < m_numOfIts; ++i)
        {   
            m_mutex.Lock();
            m_condVar.Wait(m_mutex, &cond);
            ++g_int;
            m_mutex.Unlock();
        }
    }

    int m_numOfIts;
    advcpp::Mutex& m_mutex;
    advcpp:: CondVar& m_condVar;
};

UNIT(TestCondVar)
    advcpp::Mutex m;
    advcpp:: CondVar cv;
    advcpp::Runnable* rpt = new PredicateToggler(100000, cv);
    advcpp::Runnable* ri = new IncGlobalVar(100000, m, cv);
    advcpp::Thread t0(rpt);
    advcpp::Thread t1(ri);
    advcpp::Thread t2(ri);

    sleep(10);
    ASSERT_EQUAL(g_int, 100000*2);
END_UNIT


TEST_SUITE(ConditionVariableTest) 
    TEST(TestCondVar)
END_SUITE 