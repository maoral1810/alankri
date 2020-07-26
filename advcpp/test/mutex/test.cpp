#include "mu_test.h"

#include<cstddef> // size_t

#include "runnable.hpp"
#include "thread.hpp"
#include "mutex.hpp"


using advcpp::Mutex;

class ForwardDataWithoutMutex : public advcpp::Runnable {
public:
    ForwardDataWithoutMutex(size_t& a_data, size_t a_iterations); 
    // ~ForwardDataWithoutMutex = defualt;
    //ForwardDataWithoutMutex(const ForwardDataWithoutMutex& a_other) = defualt;
    //ForwardDataWithoutMutex& operator=(const ForwardDataWithoutMutex& a_other) = defualt;
    
    virtual void Run();

private:
    size_t& m_data;
    size_t m_iterations;
};

ForwardDataWithoutMutex::ForwardDataWithoutMutex(size_t& a_data, size_t a_iterations)
    : m_data(a_data)
    , m_iterations(a_iterations)
{}

void ForwardDataWithoutMutex::Run()
{
    while(m_iterations)
    {
        ++m_data;
        --m_iterations;
    }
}


class ForwardDataWithMutex : public advcpp::Runnable {
public:
    ForwardDataWithMutex(size_t& a_data, size_t a_iterations); 
    // ~ForwardDataWithMutex = defualt;
    //ForwardDataWithMutex(const ForwardDataWithMutex& a_other) = defualt;
    //ForwardDataWithMutex& operator=(const ForwardDataWithMutex& a_other) = defualt;
    
    virtual void Run();

private:
    size_t& m_data;
    size_t m_iterations;
    Mutex& m_lhock;
};

ForwardDataWithMutex::ForwardDataWithMutex(size_t& a_data, size_t a_iterations)
    : m_data(a_data)
    , m_iterations(a_iterations)
{}

void ForwardDataWithMutex::Run()
{
    while(m_iterations)
    {
        ++m_data;
        --m_iterations;
    }
}


//----------------------------------------
UNIT(Two_Threads_Forward_Int_Without_Mutex)
    size_t data = 0;
    size_t numOfIterations = 10000;
    ForwardData threadFunc (data, numOfIterations);
    advcpp::Thread t1(&threadFunc);
    advcpp::Thread t2(&threadFunc);

    ASSERT_EQUAL(data,numOfIterations * 2);

END_UNIT

UNIT(Two_Threads_Forward_Int_With_Mutex)
    size_t data = 0;
    size_t numOfIterations = 10000;
    ForwardData threadFunc (data, numOfIterations);
    advcpp::Thread t1(&threadFunc);
    advcpp::Thread t2(&threadFunc);



    ASSERT_EQUAL(data,numOfIterations * 2);
END_UNIT

TEST_SUITE(Mutex) 
    TEST(Two_Threads_Forward_Int_Without_Mutex)
    //TEST(Two_Threads_Forward_Int_With_Mutex)
END_SUITE 