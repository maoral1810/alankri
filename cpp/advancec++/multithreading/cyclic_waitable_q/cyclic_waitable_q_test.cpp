#include "thread.hpp"
#include "mutex.hpp"
#include "semaphore.hpp"
#include "cyclic_waitable_q.hpp"
#include "read_work.hpp"
#include "write_work.hpp"
#include "MUTest.hpp"

static const size_t QUEUE_SIZE = 100;
static const int CONSOUMER_ITERATIONS = 100;

UNIT(cyclicQ)
    experis::WaitCycQ<int>queue(QUEUE_SIZE);
    experis::MyRead readFunc(CONSOUMER_ITERATIONS, &queue);
    experis::MyWrite writeForP1(0, 500, &queue);
    experis::MyWrite writeForP2(500, 1000, &queue);
    
    // producers
    experis::Thread* producer1 = new experis::Thread (&writeForP1);
    experis::Thread* producer2 = new experis::Thread(&writeForP2);
    
    // counsomers
    experis::Thread* consumer1 = new experis::Thread(&readFunc);
    experis::Thread* consumer2 = new experis::Thread(&readFunc);
    
    delete consumer1;
    delete consumer2;
    delete producer1;
    delete producer2;
/*     delete queue;  */

END_UNIT


TEST_SUITE(CyclicQTest)

    TEST(cyclicQ)

END_SUITE
