#include <stdio.h> /* printf */
#include <limits.h> /* MAX_INT */
#include "vectorTestFunc.h" /* getVectorSize */
#include "stackTestFunc.h" /* getStacSize */
#include "stack.h" 
#include "colors.h" /* colors for printf */


static void TestCreatAndDestroy(void);
static void TestPushAndTop(void);
static void TestPopAndIsEmpty(void);

static void PrintResualt(char *_testName, char *_scenario , int err);

int main(void)
{
    TestCreatAndDestroy();
    TestPushAndTop();
    TestPopAndIsEmpty();

    return 0;
}

static void TestCreatAndDestroy(void)
{
    Stack *stack = NULL;
    size_t stackSize = 5;
    size_t blockSize = 2;
    char *testName = "TestCreatAndDestroy";
    int err = 0;

    /* Scenario 1: create stack with size & blockSize != 0 */
    stack = StackCreate(stackSize, blockSize);

    if(stack == NULL)
    {
        ++err;
    }

    PrintResualt(testName, "Scenario 1", err);

    StackDestroy(stack);
    stack = NULL;
    err = 0;

    /*Scenario 2: create Stack with size & blockSize = 0 */
    stack = StackCreate(0, 0); 

    if(stack != NULL)
    {
        ++err;
    }

    PrintResualt(testName, "Scenario 2", err);
    err = 0;

    /* Scenario 3:create Stack with size & blockSize = MAX_INT */
    stack = StackCreate(LONG_MAX, LONG_MAX); 
    if(stack != NULL)
    {
        ++err;
    }

    PrintResualt(testName, "Scenario 3", err);
    StackDestroy(stack);
    err = 0;

    /* Scenario 4: create Stack with size = 0 blockSize != 0 */
    stack = StackCreate(0, blockSize);
    if(stack == NULL)
    {
        ++err;
    }

    PrintResualt(testName, "Scenario 4", err);
    StackDestroy(stack);
    err = 0;

    /* Scenario 5: create Stack with size != 0 blockSize = 0 */
    stack = StackCreate(stackSize, 0);
    if(stack == NULL)
    {
        ++err;
    }
    
    PrintResualt(testName,"Scenario 5",err);
    StackDestroy(stack);
    
    err = 0;

    /* Scenario 6: 1) create Stack with size != 0 blockSize != 0
                   2) double free */

    stack = StackCreate(stackSize, blockSize);
    if(stack == NULL)
    {
        ++err;
    }

    StackDestroy(stack);
    StackDestroy(stack);
    PrintResualt(testName, "Scenario 6", err);
    err = 0;
}

static void TestPushAndTop(void)
{
    Stack *stack = NULL;
    size_t stackSize = 6;
    size_t blockSize = 2;
    size_t i = 0;
    size_t size = 0;
    int item = 0;
    char testName[] = "TestPush";
    int to_add[] = {1,2,3,4,5,6};
    int err = 0;

    stack = StackCreate(stackSize, blockSize); 
     
    /* Scenario 1: fill Stack and resize by realloc */

    for(i = 0; i < stackSize; ++i)
    {
        if (ERR_OK != StackPush(stack, to_add[i]))
        {
            ++err;
        }
    }

    PrintResualt(testName, "Scenario 1", err);
    StackDestroy(stack);
    err = 0;
    
    /* Scenario 2: try to add for full Stack with block size 0 */
    
    stack = StackCreate(1, 0);

    if(ERR_OK != StackPush(stack, 1))
    {
        ++err;
    }

    if(ERR_OVERFLOW != StackPush(stack, to_add[0]))
    {
        ++err;
    }
    /* check the lest item */
    if(ERR_OK != StackTop(stack, &item) && to_add[0] != item)
    {
        ++err;
    }

    PrintResualt(testName, "Scenario 2", err);
    StackDestroy(stack);
    err = 0;

    /* Scenario 3: try to add for full Stack with 
    size & block size != 0 (realloc) */

    stack = StackCreate(stackSize, 2);
    
    for(i = 0; i < stackSize; ++i)
    {
        if (ERR_OK != StackPush(stack, to_add[i]))
        {
            ++err;
        }
    }

    if (ERR_OK != StackPush(stack, to_add[0]))
    {
        ++err;
    }
    
    if(ERR_OK != GetStackSize(stack, &size) && 8 != size)
    {
        ++err;
    }

    PrintResualt(testName, "Scenario 3", err);
    StackDestroy(stack);
    err = 0;
    
    /* Scenario 4: create Stack with size != 0 block size >> and try to realloc */

    stack = StackCreate(stackSize, -1);
    /* fill the array */
    for(i = 0; i < stackSize; ++i)
    {
        if (ERR_OK != StackPush(stack, to_add[i]))
        {
            ++err;
        }
    }

    if (ERR_ALLOCTAION_FAILED == StackPush(stack, to_add[0]))
    {
        ++err;/*TODO*/
    }

    PrintResualt(testName, "Scenario 4", err);
    StackDestroy(stack);
    err = 0;

    /* Scenario 5: Stack NULL */
    stack = NULL;
    
    if(ERR_NOT_INITIALZED != StackPush(NULL,0))
    {
        ++err;
    }    

    PrintResualt(testName, "Scenario 5", err);
}

static void TestPopAndIsEmpty(void)
{
    Stack *stack = NULL;
    size_t stackSize = 6;
    size_t blockSize = 2;
    size_t i = 0;
    size_t j = 0;
    size_t size = 0;
    char testName[] = "TestPop";
    int numberOfItems = 0;
    int item = 0;
    int to_add[] = {1,2,3,4,5,6};
    int err = 0;
    
    /* Scenario 1:1) StackTop on NULL 
                  2) delete item from an empty Stack */

    if (ERR_NOT_INITIALZED != StackTop(NULL, &numberOfItems))
    {
        ++err;
    }

    stack = StackCreate(stackSize, blockSize); 
    
    if(!StackIsEmpty(stack))
    {
        ++err;
    }
    
    if(ERR_UNDERFLOW != StackPop(stack, &item))
    {
        ++err;
    }

    PrintResualt(testName, "Scenario 1", err);
    StackDestroy(stack);
    err = 0;
    
    /* Scenario 2: fill the stack and the pop all items */
    stack = StackCreate(stackSize, blockSize);
    
    for(i = 0; i < stackSize; ++i)
    {
        StackPush(stack, to_add[i]);
    }

    j = i -1 ;

    for(i = 0; i < stackSize; ++i, --j)
    {
       StackPop(stack, &item);
       if(to_add[j] != item)
       {
            ++err;
       }
    }

    PrintResualt(testName, "Scenario 2", err);
    StackDestroy(stack);
    err = 0;

     /* Scenario 3: 
       1) add items until 2 block will reallocated  
       2) delete  items until number of items will be in the original size of stack
       3)check if the stack resizehim self by use GetStackSize */
    
    stack = StackCreate(stackSize, blockSize); 
    /* fill all Stack */
    for(i = 0; i < stackSize; ++i)
    {
        StackPush(stack, to_add[i]);
    }

    /* realloc vector 3 times by 2*/
    for(i = 0; i < 4; ++i)
    {
        StackPush(stack, to_add[i]);
    }
    
    if(ERR_OK != GetStackSize(stack, &size) && 10 != size)
    {
        ++err;
    }
    /* sizeOfVector = 10 */
    j = i -1;
    /* delete 4 items in vector (vector need to resize) */ 
    for(i = 0; i < 4; ++i, --j)
    {
       StackPop(stack, &item);
       if(to_add[j]!= item)
       {
           ++err;
       }
    }
    
    PrintResualt(testName, "Scenario 3", err);
    StackDestroy(stack);
    err = 0;
    stack = NULL;
  
}

/* ----------------- helpful functions ------------------*/
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


