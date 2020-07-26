#include <stdio.h>  /* printf    */
#include "queue.h"  /* queue API */
#include "colors.h" /* colors    */

#define ARR_LENGTH(x)(sizeof(x) / sizeof(x[0]))

static void PrintResualt(char *_testName, char *_scenario, int err);
static int PrintIntQueue(void* _element, size_t _index, void* _context);

static void TestQueueCreateMaxSizeZero(void);
static void TestQueueCreateMaxSizeNotZero(void);

/* static void TestQueueDestroyDoubleFree(void); */

static void TestQueueEnqueueQueueNULL(void);
static void TestQueueEnqueueItemNULL(void);
static void TestQueueEnqueueQueueAndItemNULL(void);
static void TestQueueEnqueueFullQueue(void);

static void TestQueueDequeueQueueNULL(void);
static void TestQueueDequeuePValueNULL(void);
static void TestQueueDequeueQueueAndPValueNULL(void);
static void TestQueueDequeueEmptyQueue(void);
static void TestQueueDequeueFullQueue(void);

static void TestQueueIsEmptyQueueNULL(void);
static void TestQueueIsEmptyFullQueue(void);
static void TestQueueIsEmptyEmptyQueue(void);

static void TestQueueForEachQueueNULL(void);
static void TestQueueForEachQueueElementActionNULL(void);
static void TestQueueForEachconPrintQueue(void);




int main(void)
{
    TestQueueCreateMaxSizeZero();
    TestQueueCreateMaxSizeNotZero();

/*     TestQueueDestroyDoubleFree(); */

    TestQueueEnqueueQueueNULL();
    TestQueueEnqueueItemNULL();
    TestQueueEnqueueQueueAndItemNULL();
    TestQueueEnqueueFullQueue();

    TestQueueDequeueQueueNULL();
    TestQueueDequeuePValueNULL();
    TestQueueDequeueQueueAndPValueNULL();
    TestQueueDequeueEmptyQueue();
    TestQueueDequeueFullQueue();

    TestQueueIsEmptyQueueNULL();
    TestQueueIsEmptyFullQueue();
    TestQueueIsEmptyEmptyQueue();

    TestQueueForEachQueueNULL();
    TestQueueForEachQueueElementActionNULL();
    TestQueueForEachconPrintQueue();

    return 0;
}


static void TestQueueCreateMaxSizeZero(void)
{
    int err = 0;
    char *testName = "TestQueueCreate";
    char *scenario = "MaxSizeZero";
    Queue *newQueue = QueueCreate(0);

    if(NULL != newQueue)
    {
        ++err;
    }
    
    PrintResualt(testName, scenario, err);
}

static void TestQueueCreateMaxSizeNotZero(void)
{
    int err = 0;
    char *testName = "TestQueueCreate";
    char *scenario = "MaxSizeNotZero";
    Queue *newQueue = QueueCreate(10);

    if(NULL == newQueue)
    {
        ++err;
    }
    
    QueueDestroy(&newQueue, NULL);
    PrintResualt(testName, scenario, err);
}

/* static void TestQueueDestroyDoubleFree(void)
{
    int err = 0;
    char *testName = "TestQueueDestroy";
    char *scenario = "DoubleFree";
    Queue *newQueue = QueueCreate(10);
    Queue *saveQueue = newQueue;

    QueueDestroy(&newQueue, NULL);
    QueueDestroy(&saveQueue, NULL);

    PrintResualt(testName, scenario, err);
} */

static void TestQueueEnqueueQueueNULL(void)
{
    int err = 0;
    char *testName = "TestQueueEnqueue";
    char *scenario = "QueueNULL";
    int item = 2;

    if(QUEUE_UNINITIALIZED_ERROR != QueueEnqueue(NULL, &item))
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestQueueEnqueueItemNULL(void)
{
    int err = 0;
    char *testName = "TestQueueEnqueue";
    char *scenario = "ItemNULL";
    Queue *newQueue = QueueCreate(4);

    if(QUEUE_UNINITIALIZED_ERROR != QueueEnqueue(newQueue, NULL))
    {
        ++err;
    }

    QueueDestroy(&newQueue, NULL);

    PrintResualt(testName, scenario, err);
}

static void TestQueueEnqueueQueueAndItemNULL(void)
{
    int err = 0;
    char *testName = "TestQueueEnqueue";
    char *scenario = "QueueAndItemNULL";

    if(QUEUE_UNINITIALIZED_ERROR != QueueEnqueue(NULL, NULL))
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestQueueEnqueueFullQueue(void)
{
    int err = 0;
    char *testName = "TestQueueEnqueue";
    char *scenario = "FullQueue";
    Queue *newQueue = QueueCreate(4);
    int data[] = {5,6,7,8,9};
    size_t size = ARR_LENGTH(data);
    size_t i;

    for(i = 0; i < size - 1; ++i)
    {
       if(QUEUE_SUCCESS != QueueEnqueue(newQueue, &data[i]))
       {
           ++err;
       }
    }

    if(QUEUE_OVERFLOW != QueueEnqueue(newQueue, &data[i]))
    {
        ++err;
    }

    QueueDestroy(&newQueue, NULL);

    PrintResualt(testName, scenario, err);
}

static void TestQueueDequeueQueueNULL(void)
{
    int err = 0;
    char *testName = "TestQueueDequeue";
    char *scenario = "QueueNULL";
    void *item;

    if(QUEUE_UNINITIALIZED_ERROR != QueueDequeue(NULL, &item))
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestQueueDequeuePValueNULL(void)
{
    int err = 0;
    char *testName = "TestQueueDequeue";
    char *scenario = "PValueNULL";
    Queue *newQueue = QueueCreate(4);
    
    if(QUEUE_UNINITIALIZED_ERROR != QueueDequeue(newQueue, NULL))
    {
        ++err;
    }

    QueueDestroy(&newQueue, NULL);
    PrintResualt(testName, scenario, err);
}

static void TestQueueDequeueQueueAndPValueNULL(void)
{
    int err = 0;
    char *testName = "TestQueueDequeue";
    char *scenario = "QueueAndPValueNULL";

    if(QUEUE_UNINITIALIZED_ERROR != QueueDequeue(NULL, NULL))
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestQueueDequeueEmptyQueue(void)
{
    int err = 0;
    char *testName = "TestQueueDequeue";
    char *scenario = "EmptyQueue";
    Queue *newQueue = QueueCreate(4);
    void *item;
    
    if(QUEUE_UNDERFLOW != QueueDequeue(newQueue, &item))
    {
        ++err;
    }

    QueueDestroy(&newQueue, NULL);
    PrintResualt(testName, scenario, err);
}

static void TestQueueDequeueFullQueue(void)
{
    int err = 0;
    char *testName = "TestQueueDequeue";
    char *scenario = "FullQueue";
    Queue *newQueue = QueueCreate(4);
    int data[] = {5,6,7,8,9};
    size_t size = ARR_LENGTH(data);
    void *item;
    size_t i;    

    for(i = 0; i < size - 1; ++i)
    {
       QueueEnqueue(newQueue, &data[i]);
    }

    for(i = 0; i < size - 1; ++i)
    {
        if(QUEUE_SUCCESS != QueueDequeue(newQueue, &item))
        {
            ++err;
        }
        
        if(*(int *)item != data[i])
        {
            ++err;
        }
    }
    
    QueueDestroy(&newQueue, NULL);
    PrintResualt(testName, scenario, err);
}


static void TestQueueIsEmptyQueueNULL(void)
{
    int err = 0;
    char *testName = "TestQueueIsEmpty";
    char *scenario = "QueueNULL";

    if(!QueueIsEmpty(NULL))
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestQueueIsEmptyFullQueue(void)
{
    int err = 0;
    char *testName = "TestQueueIsEmpty";
    char *scenario = "FullQueue";
    Queue *newQueue = QueueCreate(5);
    int data[] = {5,6,7,8,9};
    size_t size = ARR_LENGTH(data);
    size_t i;    

    for(i = 0; i < size; ++i)
    {
       QueueEnqueue(newQueue, &data[i]);
    }

    if(QueueIsEmpty(newQueue))
    {
        ++err;
    }    

    QueueDestroy(&newQueue, NULL);
    PrintResualt(testName, scenario, err);
}

static void TestQueueIsEmptyEmptyQueue(void)
{
    int err = 0;
    char *testName = "TestQueueIsEmpty";
    char *scenario = "EmptyQueue";
    Queue *newQueue = QueueCreate(5);

    if(!QueueIsEmpty(newQueue))
    {
        ++err;
    }    

    QueueDestroy(&newQueue, NULL);
    PrintResualt(testName, scenario, err);
}

static void TestQueueForEachQueueNULL(void)
{
    int err = 0;
    char *testName = "TestQueueForEach";
    char *scenario = "QueueNULL";

    if(0 != QueueForEach(NULL, PrintIntQueue, NULL))
    {
        ++err;
    }    

    PrintResualt(testName, scenario, err);
}

static void TestQueueForEachQueueElementActionNULL(void)
{
    int err = 0;
    char *testName = "TestQueueForEach";
    char *scenario = "QueueElementActionNULL";
    Queue *newQueue = QueueCreate(5);

    if(0 != QueueForEach(newQueue, NULL, NULL))
    {
        ++err;
    }    

    QueueDestroy(&newQueue, NULL);
    PrintResualt(testName, scenario, err);
}

static void TestQueueForEachconPrintQueue(void)
{
    int err = 0;
    char *testName = "TestQueueForEach";
    char *scenario = "PrintQueue";
    Queue *newQueue = QueueCreate(5);
    int data[] = {5,6,7,8,9};
    size_t size = ARR_LENGTH(data);
    size_t i;    
    
    for(i = 0; i < size; ++i)
    {
        QueueEnqueue(newQueue, &data[i]);
    }
    
    if(size != QueueForEach(newQueue, PrintIntQueue, NULL))
    {
        ++err;
    }    

    QueueDestroy(&newQueue, NULL);
    PrintResualt(testName, scenario, err);
}



static void PrintResualt(char *_testName, char *_scenario, int err)
{
    if (err)
    {
        printf(BOLDCYAN "%s" BOLDYELLOW ":%s: " BOLDRED "FAIL!\n" RESET,
               _testName, _scenario);
    }
    else
    {
        printf(BOLDCYAN "%s" BOLDYELLOW ":%s: " BOLDGREEN "SUCSSES \n" RESET, _testName, _scenario);
    }
}

static int PrintIntQueue(void* _element, size_t _index, void* _context)
{
    printf("%d,",*(int *)_element);
    return TRUE;
}