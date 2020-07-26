#include "mu_test.h"

#include <unistd.h>     // sleep
#include <iostream>     // cout
#include <algorithm>    // sort , copy
#include <queue>

#include "condition_variable.hpp"
#include "mutex.hpp"
#include "runnable.hpp"
#include "thread.hpp"
#include "waitable_bounded_queue.hpp"
#include "common_utils.hpp"
#include "cyclic_fifo.hpp"

//! @brief Create a cat class and enqueue and dequeue from waitabl queue
//* The Queue wraps around stl container
//* Concept: First In First Out Container thread safe
//! @author Author Maor Alankri

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
//----------------------------------------------
struct Compere {

    Compere(){}
    bool operator()(const Cat& a_cat1, const Cat& a_cat2)
    {
        return a_cat1.GetCatId() < a_cat2.GetCatId();
    }
};

struct CheckAllElementsExsist {

    CheckAllElementsExsist()
    : m_elements(0)
    {}
    bool operator()(const Cat& a_cat)
    {
        //std::cout << "cat id = " << a_cat.GetCatId() << '\n';
        return (a_cat.GetCatId() == m_elements++);
    }

private:
    size_t m_elements;
};

// ----------------------------------------------
template<typename T, class Container>
class WriteToQueue : public advcpp::Runnable {
public:
    WriteToQueue(size_t a_startNum, size_t a_numOfIterations, 
    advcpp::WaitableBoundedQueue<T,Container>& a_queue,
    size_t a_id);
    virtual void Run();
    bool IsOk() const NOEXCEPTIONS;

private:
    size_t m_numOfIterations;
    size_t m_startNum;
    bool m_isOk;
    advcpp::WaitableBoundedQueue<T, Container>& m_queue;
    size_t m_producerId;
};

template<typename T, class Container>
WriteToQueue<T,Container>::WriteToQueue(size_t a_startNum, size_t a_numOfIterations, 
advcpp::WaitableBoundedQueue<T,Container>& a_queue,
size_t a_id)
    : m_numOfIterations(a_numOfIterations)
    , m_startNum(a_startNum)
    , m_isOk(true)
    , m_queue(a_queue)
    , m_producerId(a_id)
{}

template<typename T, class Container>
void WriteToQueue<T,Container >::Run() 
{
    try {
        for(size_t i = 0; i < m_numOfIterations; ++i)
        {
            //std::cout<< "write: " << m_startNum << '\n';
            
                m_queue.Enqueue(Cat(m_startNum, m_producerId));
            ++m_startNum;
        }
    }
    catch(...)
    {
        m_isOk = false;
    }
}

template<typename T, class Container>
bool WriteToQueue<T,Container>::IsOk() const NOEXCEPTIONS
{
    return m_isOk;
}
// ---------------------------------------------------------
template<typename T, class Container>
class ReadFromQueue : public advcpp::Runnable {
public:
    ReadFromQueue(size_t a_numOfIterations, 
    advcpp::WaitableBoundedQueue<T,Container>& a_queue
    , std::vector<T>& a_vec
    , size_t a_numOfProducers);
    
    virtual void Run();
    bool IsOk() const NOEXCEPTIONS;
private:
    size_t m_numOfIterations;
    advcpp::WaitableBoundedQueue<T,Container>& m_queue;
    bool m_isOk;
    std::vector<T>& m_vec;
    size_t m_numOfProducers;
};

template<typename T, class Container>
ReadFromQueue<T,Container>::ReadFromQueue(size_t a_numOfIterations, 
                            advcpp::WaitableBoundedQueue<T,Container>& a_queue,
                            std::vector<T>& a_vec,
                            size_t a_numOfProducers) 
    : m_numOfIterations(a_numOfIterations)
    , m_queue(a_queue)
    , m_isOk(true)
    , m_vec(a_vec)
    , m_numOfProducers(a_numOfProducers)
{}

template<typename T, class Container>
void ReadFromQueue<T,Container>::Run() 
{
    T data;
    std::vector<T> catsGroup(m_numOfProducers);

    try {
        for(size_t i = 0; i < m_numOfIterations; ++i)
        {
            m_queue.Dequeue(data);
           //std::cout << "read:" << data.GetCatId() << '\n';  
            
            if( (catsGroup[data.GetCatColor() - 1].GetCatId() > data.GetCatId()) )
            {
                std::cout << "Here" << std::endl;
                m_isOk = false;
                break;
            } 
            m_vec[i] = data;
            catsGroup[data.GetCatColor() - 1] = data;
        }
    }
    catch(...)
    {
        m_isOk = false;
    }

    putchar('\n');
}

template<typename T, class Container>
bool ReadFromQueue<T,Container>::IsOk() const NOEXCEPTIONS
{
    return m_isOk;
}

// ---------------------------------------------------------
UNIT(Test_Waitable_Q_1_producer_1_consumer) 
    const size_t numOfWrites = 1000000;
    const size_t producers = 1;
    const size_t consumers = 1;
    
    std::vector<Cat> vecConsumer1(numOfWrites);
    advcpp::WaitableBoundedQueue<Cat,advcpp::CyclicFIFO<Cat> > q(100);
    WriteToQueue<Cat,advcpp::CyclicFIFO<Cat> > producerFunc(numOfWrites * 0, numOfWrites / producers, q, 1);
    ReadFromQueue<Cat, advcpp::CyclicFIFO<Cat> > consumerFunc(numOfWrites / consumers, q, vecConsumer1,producers);
    advcpp::Thread producer (&producerFunc);
    advcpp::Thread consumer (&consumerFunc);
    
    producer.Join();
    consumer.Join();
    
    ASSERT_EQUAL(std::count_if(vecConsumer1.begin(), vecConsumer1.end(),CheckAllElementsExsist()) , numOfWrites);

    std::sort(vecConsumer1.begin(), vecConsumer1.end(), Compere());

    ASSERT_THAT(consumerFunc.IsOk());
END_UNIT

UNIT(Test_Waitable_Q_2_producer_1_consumer) 
    const size_t numOfWrites = 1000000;
    const size_t producers = 2;
    const size_t consumers = 1;

    advcpp::WaitableBoundedQueue<Cat,advcpp::CyclicFIFO<Cat> > q(10);
    
    WriteToQueue<Cat,advcpp::CyclicFIFO<Cat> > producerFunc1( (numOfWrites / producers) * 0, numOfWrites / producers, q, 1);
    WriteToQueue<Cat,advcpp::CyclicFIFO<Cat> > producerFunc2( (numOfWrites / producers) * 1, numOfWrites / producers, q, 2);
    
    std::vector<Cat> vecConsumer1(numOfWrites);
    ReadFromQueue<Cat,advcpp::CyclicFIFO<Cat> > consumerFunc(numOfWrites / consumers, q, vecConsumer1,producers);
    
    advcpp::Thread producer1 (&producerFunc1);
    advcpp::Thread producer2 (&producerFunc2);
    advcpp::Thread consumer  (&consumerFunc);

    producer1.Join();
    producer2.Join();
    consumer.Join();
    
    std::sort(vecConsumer1.begin(), vecConsumer1.end(), Compere());
    ASSERT_EQUAL(std::count_if(vecConsumer1.begin(), vecConsumer1.end(),CheckAllElementsExsist()) , numOfWrites);

    
    ASSERT_THAT(consumerFunc.IsOk());
END_UNIT

UNIT(Test_Waitable_Q_1_producer_2_consumer) 
    const size_t numOfWrites = 1000000;
    const size_t producers = 1;
    const size_t consumers = 2;

    std::vector<Cat> vecConsumer1(numOfWrites / consumers);
    std::vector<Cat> vecConsumer2(numOfWrites / consumers);
    
    advcpp::WaitableBoundedQueue<Cat,advcpp::CyclicFIFO<Cat> > q(20);
    
    WriteToQueue<Cat, advcpp::CyclicFIFO<Cat> > producerFunc((numOfWrites / producers) * 0, numOfWrites, q, 1);
    
    ReadFromQueue<Cat, advcpp::CyclicFIFO<Cat> > consumerFunc1(numOfWrites / consumers, q, vecConsumer1,producers);
    ReadFromQueue<Cat, advcpp::CyclicFIFO<Cat> > consumerFunc2(numOfWrites / consumers, q, vecConsumer2,producers);
    
    advcpp::Thread producer1 (&producerFunc);
    advcpp::Thread consumer1 (&consumerFunc1);
    advcpp::Thread consumer2 (&consumerFunc2);

    producer1.Join();
    consumer1.Join();
    consumer2.Join();
    
    ASSERT_THAT(consumerFunc1.IsOk() && consumerFunc2.IsOk());

    std::vector<Cat> allCats;
    std::copy(vecConsumer1.begin(), vecConsumer1.end(), std::back_inserter(allCats));
    std::copy(vecConsumer2.begin(), vecConsumer2.end(), std::back_inserter(allCats));
    std::sort(allCats.begin(), allCats.end(), Compere());
    
    ASSERT_EQUAL(std::count_if(allCats.begin(), allCats.end(),CheckAllElementsExsist()) , numOfWrites);
END_UNIT

UNIT(Test_Waitable_Q_4_producer_7_consumer) 
    const size_t numOfWrites = 280000;
    const size_t producers = 4;
    const size_t consumers = 7;

    advcpp::WaitableBoundedQueue<Cat,advcpp::CyclicFIFO<Cat> > q(10);
    WriteToQueue<Cat, advcpp::CyclicFIFO<Cat> > producerFunc1( (numOfWrites / producers) * 0, numOfWrites / producers, q, 1);
    WriteToQueue<Cat, advcpp::CyclicFIFO<Cat> > producerFunc2( (numOfWrites / producers) * 1, numOfWrites / producers, q, 2);
    WriteToQueue<Cat, advcpp::CyclicFIFO<Cat> > producerFunc3( (numOfWrites / producers) * 2, numOfWrites / producers, q, 3);
    WriteToQueue<Cat, advcpp::CyclicFIFO<Cat> > producerFunc4( (numOfWrites / producers) * 3, numOfWrites / producers, q, 4);

    advcpp::Thread producer1 (&producerFunc1);
    advcpp::Thread producer2 (&producerFunc2);
    advcpp::Thread producer3 (&producerFunc3);
    advcpp::Thread producer4 (&producerFunc4);
    // counsumers
    std::vector<Cat> vecConsmer1(numOfWrites / consumers);
    std::vector<Cat> vecConsmer2(numOfWrites / consumers);
    std::vector<Cat> vecConsmer3(numOfWrites / consumers);
    std::vector<Cat> vecConsmer4(numOfWrites / consumers);
    std::vector<Cat> vecConsmer5(numOfWrites / consumers);
    std::vector<Cat> vecConsmer6(numOfWrites / consumers);
    std::vector<Cat> vecConsmer7(numOfWrites / consumers);
    
    ReadFromQueue<Cat, advcpp::CyclicFIFO<Cat> > consumerFunc1(numOfWrites / consumers, q, vecConsmer1, producers);
    ReadFromQueue<Cat, advcpp::CyclicFIFO<Cat> > consumerFunc2(numOfWrites / consumers, q, vecConsmer2, producers);
    ReadFromQueue<Cat, advcpp::CyclicFIFO<Cat> > consumerFunc3(numOfWrites / consumers, q, vecConsmer3, producers);
    ReadFromQueue<Cat, advcpp::CyclicFIFO<Cat> > consumerFunc4(numOfWrites / consumers, q, vecConsmer4, producers);
    ReadFromQueue<Cat, advcpp::CyclicFIFO<Cat> > consumerFunc5(numOfWrites / consumers, q, vecConsmer5, producers);
    ReadFromQueue<Cat, advcpp::CyclicFIFO<Cat> > consumerFunc6(numOfWrites / consumers, q, vecConsmer6, producers);
    ReadFromQueue<Cat, advcpp::CyclicFIFO<Cat> > consumerFunc7(numOfWrites / consumers, q, vecConsmer7, producers);

    advcpp::Thread consumer1 (&consumerFunc1);
    advcpp::Thread consumer2 (&consumerFunc2);
    advcpp::Thread consumer3 (&consumerFunc3);
    advcpp::Thread consumer4 (&consumerFunc4);
    advcpp::Thread consumer5 (&consumerFunc5);
    advcpp::Thread consumer6 (&consumerFunc6);
    advcpp::Thread consumer7 (&consumerFunc7);

    producer1.Join();
    producer2.Join();
    producer3.Join();
    producer4.Join();

    consumer1.Join();
    consumer2.Join();
    consumer3.Join();
    consumer4.Join();
    consumer5.Join();
    consumer6.Join();
    consumer7.Join();

    ASSERT_THAT(consumerFunc1.IsOk() && consumerFunc2.IsOk() && consumerFunc3.IsOk()
    && consumerFunc4.IsOk() && consumerFunc5.IsOk() && consumerFunc6.IsOk()
    && consumerFunc7.IsOk());

    std::vector<Cat> allCats;
    std::copy(vecConsmer1.begin(), vecConsmer1.end(), std::back_inserter(allCats));
    std::copy(vecConsmer2.begin(), vecConsmer2.end(), std::back_inserter(allCats));
    std::copy(vecConsmer3.begin(), vecConsmer3.end(), std::back_inserter(allCats));
    std::copy(vecConsmer4.begin(), vecConsmer4.end(), std::back_inserter(allCats));
    std::copy(vecConsmer5.begin(), vecConsmer5.end(), std::back_inserter(allCats));
    std::copy(vecConsmer6.begin(), vecConsmer6.end(), std::back_inserter(allCats));
    std::copy(vecConsmer7.begin(), vecConsmer7.end(), std::back_inserter(allCats));
    

    std::sort(allCats.begin(), allCats.end(), Compere());
    std::for_each(allCats.begin(), allCats.end(),CheckAllElementsExsist());
    
    ASSERT_EQUAL(std::count_if(allCats.begin(), allCats.end(), CheckAllElementsExsist()) ,numOfWrites);
END_UNIT

TEST_SUITE(TestWaitableBoundedQueue) 
    TEST(Test_Waitable_Q_1_producer_1_consumer)
    TEST(Test_Waitable_Q_2_producer_1_consumer)
    TEST(Test_Waitable_Q_1_producer_2_consumer)
    TEST(Test_Waitable_Q_4_producer_7_consumer)
END_SUITE 


