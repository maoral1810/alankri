#include "mu_test.h"

#include<cstddef> // size_t
#include <cmath> // pow

#include "runnable.hpp"
#include "thread.hpp"
#include "mutex.hpp"
#include "thread_pool.hpp"

using advcpp::ThreadPool;
using advcpp::Runnable;

//-------------------- Thread Runnable ------------------
class Cat {
public:    
    Cat();
    Cat(size_t a_id, size_t a_color);
    //~Cat() = defualt;
    //Cat(const Cat& a_other) = defualt;
    //Cat& operator=(const Cat& a_other) = defualt;

    size_t GetCatId() const NOEXCEPTIONS;
    size_t GetCatColor() const NOEXCEPTIONS;
private:
    size_t m_id; 
    size_t m_color;
};


Cat::Cat()
    : m_id(0)
    , m_color(0)
{}

Cat::Cat(size_t a_id, size_t a_color)
    : m_id(a_id)
    , m_color(a_color)
{}

size_t Cat::GetCatId() const NOEXCEPTIONS 
{
    return m_id;
}

size_t Cat::GetCatColor() const NOEXCEPTIONS
{
    return m_color;
}


class CatProducer : public Runnable {
public:
    CatProducer(std::vector<Cat>& a_vec, size_t a_fromId, size_t a_numOfCats, size_t a_producerId);
    //~CatProducer() = default;
    //CatProducer(const CatProducer& a_other) = default;
    //CatProducer& operator=(const CatProducer& a_other) = default;

    virtual void Run();
private:
    std::vector<Cat>& m_vec;
    size_t m_fromId;
    size_t m_numOfCats;
    size_t m_producerId;
};

CatProducer::CatProducer(std::vector<Cat>& a_vec, size_t a_fromId, size_t a_numOfCats, size_t a_producerId)
    : m_vec(a_vec)
    , m_fromId(a_fromId)
    , m_numOfCats(a_numOfCats)
    , m_producerId(a_producerId)
{}

void CatProducer::Run()
{
    m_vec.reserve(m_vec.size() + m_numOfCats);

    for(; m_fromId != m_fromId + m_numOfCats; ++m_fromId)
    {
        Cat newCat(m_fromId, m_producerId);
        m_vec.push_back(newCat);
    }
}
// -----------------------------------------------------

//----------------------------------------
UNIT(CreatePool)
    const size_t queueSize = 10;
    const size_t numOfThreads = 5;

    ThreadPool pool(queueSize, numOfThreads);

    ASSERT_THAT(1);
END_UNIT


UNIT(CreatePoolByDefault)
    ThreadPool pool();

    ASSERT_THAT(1);
END_UNIT

UNIT(Create_10_Threads_With_10_Tasks_Check_Size_And_Remove)
    const size_t queueSize = 10;
    const size_t numOfThreads = 10;

    ThreadPool pool(queueSize, numOfThreads);
    for(size_t i = 0; i < numOfThreads; ++i)
    {
        pool.AddTask(advcpp::SharedPtr<Runnable>(new CountTo(pow(3,i))));
    }

    ASSERT_EQUAL( numOfThreads , pool.Size() );
    
    pool.RemoveThreads(numOfThreads, true);
   
    ASSERT_EQUAL(0 , pool.Size() );

END_UNIT

UNIT(Create_Pool_0_Threads_Add_10_Thread_Remove_10_Add_2_Remove_All)
    ThreadPool pool(40,0);
    pool.AddThreads(10);
    
    ASSERT_EQUAL( 10, pool.Size() );
    for(size_t i = 0; i < 30; ++i)
    {
        pool.AddTask(advcpp::SharedPtr<Runnable>(new CountTo(pow(2,i / 5))));
    }

    pool.RemoveThreads(10);
    ASSERT_EQUAL(0, pool.Size() );

    pool.AddThreads(2);
    ASSERT_EQUAL( 2, pool.Size() );
    
    pool.StopAll();
    ASSERT_EQUAL(0, pool.Size() );

END_UNIT

UNIT(Creat_Pool_By_Default_Add_50_Thread_Remove_10_Add_5_Remove_All)

    ThreadPool pool;
    for(size_t i = 0; i < 63; ++i)
    {
        pool.AddTask(advcpp::SharedPtr<Runnable>(new CountTo(pow(2, i / 2))));
    }
    
    size_t defaultThreads = pool.Size();
    pool.AddThreads(50, false);
    ASSERT_EQUAL( 50 + defaultThreads, pool.Size() );
    
    pool.RemoveThreads(10,false);
    ASSERT_EQUAL( 40 + defaultThreads, pool.Size() );
    
    pool.AddThreads(5, false);
    ASSERT_EQUAL( 45 + defaultThreads, pool.Size() );

    pool.RemoveThreads( pool.Size(), true );
    ASSERT_EQUAL( 0, pool.Size() ); 

END_UNIT

UNIT(ShutdownByDefualt)

    ThreadPool pool(30,20);
    for(size_t i = 0; i < 30; ++i)
    {
        pool.AddTask(advcpp::SharedPtr<Runnable>(new CountTo(pow(2,i / 2))));
    }
    pool.AddThreads(10);
    ASSERT_EQUAL(true ,pool.Shutdown());

END_UNIT

UNIT(Shutdown)
    size_t timerInMicroSec = 1; 
    ThreadPool pool(30,20);
    for(size_t i = 0; i < 30; ++i)
    {
        pool.AddTask(advcpp::SharedPtr<Runnable>(new CountTo(pow(2,i))));
    }
    
    ASSERT_EQUAL(false ,pool.Shutdown(timerInMicroSec));
END_UNIT

/* TEST(ShutdownImediateByDefault)
END_UNIT


TEST(ShutdownImediate)
END_UNIT


TEST(ShutdownAggressive)
    size_t timerInMicroSec = 10; 
    ThreadPool pool(30,20);
    for(size_t i = 0; i < 30; ++i)
    {
        pool.AddTask(advcpp::SharedPtr<Runnable>(new CountTo(pow(2,i / 2))));
    }

    pool.AddThreads(10);
    
    ASSERT_EQUAL(false ,pool.Shutdown(timerInMicroSec));
END_UNIT */


TEST_SUITE(ThreadPool) 
    TEST(CreatePool)
    TEST(CreatePoolByDefault)
    // -------------------- Add And Remove ------------------
    TEST(Create_10_Threads_With_10_Tasks_Check_Size_And_Remove)
    TEST(Create_Pool_0_Threads_Add_10_Thread_Remove_10_Add_2_Remove_All)
    TEST(Creat_Pool_By_Default_Add_50_Thread_Remove_10_Add_5_Remove_All)
   
    // -------------------- ShutDown ------------------
    TEST(ShutdownByDefualt)
    TEST(Shutdown)
    //TEST(ShutdownImediateByDefault)
    //TEST(ShutdownImediate)
    //TEST(ShutdownAggressive)

END_SUITE 