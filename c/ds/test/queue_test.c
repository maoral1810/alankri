#include <stdio.h> /* printf */
#include "queue.h" 
#include "colors.h" /* colors for printf */

static void TestCreatAndDestroy(void);
static void TestInsert(void);
static void TestRemove(void);

static void PrintResualt(char *_testName, char *_scenario , int err);

int main(void)
{
    TestCreatAndDestroy();
    TestInsert();
    TestRemove();

    return 0;
}

static void TestCreatAndDestroy(void)
{
    Queue *queue = NULL;
    size_t queueSize = 5;
    char *testName = "TestCreatAndDestroy";
    int err = 0;

    /* Scenario 1: create Queue with size != 0 */
    queue = QueueCreate(queueSize);

    if(queue == NULL)
    {
        ++err;
    }

    PrintResualt(testName, "Scenario 1", err);

    QueueDestroy(queue);
    queue = NULL;
    err = 0;

    /*Scenario 2: create Queue with size = 0 */
    queue = QueueCreate(0);

    if(queue != NULL)
    {
        ++err;
    }

    PrintResualt(testName, "Scenario 2", err);

    QueueDestroy(queue);
    queue = NULL;
    err = 0;

    /* Scenario 3:create Queue with size & blockSize = MAX_LONG */
    queue = QueueCreate(-1);

    if(queue != NULL)
    {
        ++err;
    }

    PrintResualt(testName, "Scenario 3", err);

    QueueDestroy(queue);
    queue = NULL;
    err = 0;

    /* Scenario 4: 1) create Queue with size != 0 
                   2) double free */

    queue = QueueCreate(100);

    if(queue == NULL)
    {
        ++err;
    }

    QueueDestroy(queue);
    QueueDestroy(queue);
    
    PrintResualt(testName, "Scenario 4", err);
    queue = NULL;
    err = 0;

    putchar('\n');
}

static void TestInsert(void)
{
    Queue *queue = NULL;
    size_t queueSize = 5;
    size_t i = 0;
    char *testName = "TestInsert";
    int err = 0;
    int toAdd[] = {1,2,3,4,5};
    int item = 0;

    /* Scenario 1: fill all Queue and check overflow */
    
    queue = QueueCreate(queueSize);
    /* fill all queue */
    
    for(i = 0; i < queueSize; ++i)
    {
        if (ERR_OK != QueueInsert(queue, toAdd[i]))
        {
            ++err;
        }
    }

    if(ERR_OVERFLOW != QueueInsert(queue, toAdd[0]))
    {
        ++err;
    }
    
    PrintResualt(testName, "Scenario 1", err);
    QueueDestroy(queue);
    err = 0;

    /* Scenario 2: IsEmptyqueue */
    queue = QueueCreate(queueSize);

    if(!QueueIsEmpty(queue))
    {
        ++err;
    }

    PrintResualt(testName, "Scenario 2", err);
    QueueDestroy(queue);
    err = 0;

   /* Scenario 3: 1) fill 3 element in queue
                  2) remove all items and check the order
                  3) IsEmptyqueue */

    queue = QueueCreate(queueSize);

    if(!QueueIsEmpty(queue))
    {
        ++err;
    }
    /* fill 3 elements */
    for(i = 0; i < 3; ++i)
    {
        if (ERR_OK != QueueInsert(queue, toAdd[i]))
        {
            ++err;
        }
    }
    
    /* remove all itmes and check order */
    for(i = 0; i < 3; ++i)
    {
        if(ERR_OK != QueueRemove(queue,&item))
        {
            ++err;
        }

        if(item != toAdd[i])
        {
            ++err;
        }
    }

    if(!QueueIsEmpty(queue))
    {
        ++err;
    }

    PrintResualt(testName, "Scenario 3", err);
    QueueDestroy(queue);
    err = 0;

    /* Scenario 4:1) fill all queue
                  2) remove 2 items
                  3) fill 2 item
                  4) check IsEmptyqueue */

    queue = QueueCreate(queueSize);

    if(!QueueIsEmpty(queue))
    {
        ++err;
    }
    /* fill 3 elements */
    for(i = 0; i < queueSize; ++i)
    {
        if (ERR_OK != QueueInsert(queue, toAdd[i]))
        {
            ++err;
        }
    }
    
    /* remove 1 item and check order */
    if(ERR_OK != QueueRemove(queue,&item))
    {
        ++err;
    }
    
    if(item != toAdd[0])
    {
        ++err;
    }

    /* add 1 item and check isempty */
    if (ERR_OK != QueueInsert(queue, toAdd[0]))
    {
        ++err;
    }

    if(QueueIsEmpty(queue))
    {
        ++err;
    }

    PrintResualt(testName, "Scenario 4", err);
    QueueDestroy(queue);
    err = 0;

    putchar('\n');
}

static void TestRemove(void)
{
    Queue *queue = NULL;
    size_t queueSize = 5;
    size_t i = 0;
    char *testName = "TestDelete";
    int err = 0;
    int toAdd[] = {1,2,3,4,5};
    int item = 0;

    /* Scenario 1: Queue empty, delete and check underflow */
    
    queue = QueueCreate(queueSize);
    /* fill all queue */
    
    if(ERR_UNDERFLOW != QueueRemove(queue, &item))
    {
        ++err;
    }
    
    PrintResualt(testName, "Scenario 1", err);
    QueueDestroy(queue);
    err = 0;

    /* Scenario 2: 1) fill full Queue
                   2) delete all items 
                   3) check order       */

    if(!QueueIsEmpty(NULL))
    {
        ++err;
    }

    queue = QueueCreate(queueSize);

    /* fill all queue */
    for(i = 0; i < queueSize; ++i)
    {
        QueueInsert(queue, toAdd[i]);
    }
    
    /* remove all items and check order */
    for(i = 0; i < queueSize; ++i)
    {
        if(ERR_OK != QueueRemove(queue,&item))
        {
            ++err;
        }

        if(item != toAdd[i])
        {
            ++err;
        }
    }

    if(!QueueIsEmpty(queue))
    {
        ++err;
    }

    PrintResualt(testName, "Scenario 2", err);
    QueueDestroy(queue);
    err = 0;

    /* Scenario 3: 1) fill full Queue
                   2) delete 4 items
                   3) check order
                   4) insert 3 items 
                   5) check isEmpty       */

    queue = QueueCreate(queueSize);

    /* fill all queue */
    for(i = 0; i < queueSize; ++i)
    {
        QueueInsert(queue, toAdd[i]);
    }
    
    /* remove 4 items and check order */
    for(i = 0; i < 4; ++i)
    {
        if(ERR_OK != QueueRemove(queue,&item))
        {
            ++err;
        }

        if(item != toAdd[i])
        {
            ++err;
        }
    }

    for(i = 0; i < 3; ++i)
    {
        QueueInsert(queue, toAdd[i]);
    }

    if(QueueIsEmpty(queue))
    {
        ++err;
    }

    PrintResualt(testName, "Scenario 3", err);
    QueueDestroy(queue);
    err = 0;

    putchar('\n');
}


static void PrintResualt(char *_testName, char *_scenario , int err)
{
    if(err)
    {
        printf(BOLDCYAN"%s"BOLDMAGENTA":%s: "BOLDRED"FAIL!\n"RESET,
        _testName, _scenario); 
    }
    else
    {
        printf(BOLDCYAN"%s"BOLDMAGENTA":%s: "BOLDGREEN"SUCSSES \n"RESET,_testName, _scenario);
    }
}
