#include <iostream> // cout 
#include <pthread.h> // pthreade create,  pthreade mutex lock
#include <semaphore.h>
#include "MUTest.h"
#include "thread.hpp"
#include "runnable.hpp"
#include "work_add.hpp"

int g_num = 0;
pthread_mutex_t g_lock;
sem_t g_semaphore;

static const int numOfIterations = 10000000;

UNIT (ctor)

    sem_init(&g_semaphore, 0 ,1);
    experis::WorkAdd workfunc(&g_num);
    experis::Thread* thread1 = new experis::Thread(&workfunc, numOfIterations);
    experis::Thread* thread2 = new experis::Thread(&workfunc, numOfIterations);
    
    delete thread1;
    delete thread2;

    std::cout<< g_num << std::endl;

    sem_destroy(&g_semaphore);

END_UNIT

TEST_SUITE(Thread)

    TEST(ctor)

END_SUITE
