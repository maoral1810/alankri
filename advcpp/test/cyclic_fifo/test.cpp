#include "mu_test.h"
#include "cyclic_fifo.hpp"

UNIT(Insert) 
    advcpp::CyclicFIFO<int> queue(10);
    
    for(int i = 0; i< 10 ; ++i)
    {
        ASSERT_THAT(true == queue.Insert(i));
    }

    ASSERT_THAT(false == queue.Insert(10));

END_UNIT

UNIT(Remove) 
    advcpp::CyclicFIFO<int> queue(10);
    int data;
    int i = 0;
    
    for(;i < 10 ; ++i)
    {
        ASSERT_THAT(true == queue.Insert(i));
    }

    for(i = 0; i < 10; ++i)
    {
        ASSERT_EQUAL(true ,queue.Remove(&data));
        ASSERT_EQUAL(i, data);
    }

    queue.Remove(&data);
    ASSERT_THAT(false == queue.Remove(&data));

END_UNIT

UNIT(Size)
    advcpp::CyclicFIFO<int> queue(100);
    int i = 0;
    
    for(;i < 100 ; ++i)
    {
        ASSERT_THAT(true == queue.Insert(i));
    }

    ASSERT_EQUAL(100, queue.Size());
END_UNIT


TEST_SUITE(FIFOQueue) 
    TEST(Insert)
    TEST(Remove)
    TEST(Size)
END_SUITE 