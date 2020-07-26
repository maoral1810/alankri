#include <stdio.h>		/* printf       */
#include<stdlib.h>      /* free         */
#include "vector.h"	    /* Vector API   */
#include "colors.h"

#define ARR_LENGTH(x)(sizeof(x) / sizeof(x[0]))
#define TRUE 1

static void PrintResualt(char *_testName, char *_scenario, int err);
static void ElementDestroy(void* _item);
static int PrintIntVector(void* _element, size_t _index, void* _context);

static void TestVectorCreateBlockSizeAndInitialCapacityZero(void);
static void TestVectorCreateBlockSizeAndInitialCapacityNotZero(void);
static void TestVectorCreateBlockSizeZeroInitialCapacityNotZero(void);
static void TestVectorCreateBlockSizeNotZeroInitialCapacityZero(void);

static void TestVectorDestroyDoubleFree(void);
static void TestVectorDestroyFunctionNull(void);

static void TestVectorAppendVectorNull(void);
static void TestVectorAppendItemNull(void);
static void TestVectorAppendFullVector(void);
static void TestVectorAppendFullVectorIncSizeZero(void);
static void TestVectorAppendFullVectorReallocTwice(void);

static void TestVectorRemoveVectorNull(void);
static void TestVectorRemoveItemNull(void);
static void TestVectorRemoveItemAndVectorNull(void);
static void TestVectorRemoveEmptyVector(void);
static void TestVectorRemoveFullVector(void);

static void TestVectorGetVectorNull(void);
static void TestVectorGetInvalidIndex(void);
static void TestVectorGetValidIndex(void);

static void TestVectorSetVectorNull(void);
static void TestVectorSetInvalidIndex(void);
static void TestVectorSetValidIndex(void);

static void TestVectorSizeAndCapcity(void);

static void TestVectorForEachVectorNull(void);
static void TestVectorForEachPrintVector(void);

int main(void)
{
    TestVectorCreateBlockSizeAndInitialCapacityZero();
    TestVectorCreateBlockSizeAndInitialCapacityNotZero();
    TestVectorCreateBlockSizeZeroInitialCapacityNotZero();
    TestVectorCreateBlockSizeNotZeroInitialCapacityZero();

    TestVectorDestroyDoubleFree();
    TestVectorDestroyFunctionNull();

    TestVectorAppendVectorNull();
    TestVectorAppendItemNull();
    TestVectorAppendFullVector();
    TestVectorAppendFullVectorIncSizeZero();
    TestVectorAppendFullVectorReallocTwice();

    TestVectorRemoveVectorNull();
    TestVectorRemoveItemNull();
    TestVectorRemoveItemAndVectorNull();
    TestVectorRemoveEmptyVector();
    TestVectorRemoveFullVector();

    TestVectorGetVectorNull();
    TestVectorGetInvalidIndex();
    TestVectorGetValidIndex();

    TestVectorSetVectorNull();
    TestVectorSetInvalidIndex();
    TestVectorSetValidIndex();

    TestVectorSizeAndCapcity();

    TestVectorForEachVectorNull();
    TestVectorForEachPrintVector();

    return 0;
}

static void TestVectorCreateBlockSizeAndInitialCapacityZero(void)
{
    int err = 0;
    char *testName = "TestVectorCreate";
    char *scenario = "BlockSizeAndInitialCapacityZero";
    Vector *newVector = VectorCreate(0, 0);

    if(NULL != newVector)
    {
        ++err;
    }
    
    PrintResualt(testName, scenario, err);
}

static void TestVectorCreateBlockSizeAndInitialCapacityNotZero(void)
{
    int err = 0;
    char *testName = "TestVectorCreate";
    char *scenario = "BlockSizeAndInitialCapacityNotZero";
    Vector *newVector = VectorCreate(4, 4);

    if(NULL == newVector)
    {
        ++err;
    }
    
    PrintResualt(testName, scenario, err);

    VectorDestroy(&newVector,ElementDestroy);
}

static void TestVectorCreateBlockSizeZeroInitialCapacityNotZero(void)
{
    int err = 0;
    char *testName = "TestVectorCreate";
    char *scenario = "BlockSizeZeroInitialCapacityNotZero";
    Vector *newVector = VectorCreate(4,0);

    if(NULL == newVector)
    {
        ++err;
    }
    
    PrintResualt(testName, scenario, err);

    VectorDestroy(&newVector,ElementDestroy);
}

static void TestVectorCreateBlockSizeNotZeroInitialCapacityZero(void)
{
    int err = 0;
    char *testName = "TestVectorCreate";
    char *scenario = "BlockSizeNotZeroInitialCapacityZero";
    Vector *newVector = VectorCreate(0,4);

    if(NULL == newVector)
    {
        ++err;
    }
    
    PrintResualt(testName, scenario, err);

    VectorDestroy(&newVector,ElementDestroy);
}

static void TestVectorDestroyDoubleFree(void)
{
    int err = 0;
    char *testName = "TestVectorDestroy";
    char *scenario = "DoubleFree";
    Vector *newVector = VectorCreate(4,4);
    Vector *saveVetor = newVector;
    if(NULL == newVector)
    {
        ++err;
    }
    
    VectorDestroy(&newVector,ElementDestroy);
    VectorDestroy(&saveVetor,ElementDestroy);      
    
    PrintResualt(testName, scenario, err);
}

static void TestVectorDestroyFunctionNull(void)
{
    int err = 0;
    char *testName = "TestVectorDestroy";
    char *scenario = "FunctionNull";
    Vector *newVector = VectorCreate(4,4);
    
    if(NULL == newVector)
    {
        ++err;
    }
    
    VectorDestroy(&newVector, NULL);

    PrintResualt(testName, scenario, err);
}

static void TestVectorAppendVectorNull(void)
{
    int err = 0;
    char *testName = "TestVectorAppend";
    char *scenario = "VectorNull";
    int data = 5;
    
    if(VECTOR_UNITIALIZED_ERROR != VectorAppend(NULL, &data))
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestVectorAppendItemNull(void)
{
    int err = 0;
    char *testName = "TestVectorAppend";
    char *scenario = "ItemNull";
    Vector *newVector = VectorCreate(4,4);
        
    if(VECTOR_UNITIALIZED_ERROR != VectorAppend(newVector, NULL))
    {
        ++err;
    }
    
    VectorDestroy(&newVector, NULL);
    PrintResualt(testName, scenario, err);
}

static void TestVectorAppendFullVector(void)
{
    int err = 0;
    char *testName = "TestVectorAppend";
    char *scenario = "FullVector";
    Vector *newVector = VectorCreate(4,4);
    int data[] = {10, 11,20, 22};
    size_t size = ARR_LENGTH(data);
    size_t i;

    for(i = 0; i < size; ++i)
    {
        if(VECTOR_SUCCESS != VectorAppend(newVector, &data[i]) )
        {
            ++err;
        }
    }

    VectorDestroy(&newVector, NULL);
    PrintResualt(testName, scenario, err);
}

static void TestVectorAppendFullVectorIncSizeZero(void)
{
    int err = 0;
    char *testName = "TestVectorAppend";
    char *scenario = "FullVectorIncSizeZero";
    Vector *newVector = VectorCreate(4,0);
    int data[] = {10, 11, 20, 22, 5};
    size_t size = ARR_LENGTH(data);
    size_t i;

    for(i = 0; i < size - 1; ++i)
    {
        if(VECTOR_SUCCESS != VectorAppend(newVector, &data[i]))
        {
            ++err;
        }
    }

    if(VECTOR_OVERFLOW != VectorAppend(newVector, &data[i]))
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
    VectorDestroy(&newVector, NULL);
}

static void TestVectorAppendFullVectorReallocTwice(void)
{
    int err = 0;
    char *testName = "TestVectorAppend";
    char *scenario = "FullVectorReallocTwice";
    Vector *newVector = VectorCreate(2,2);
    int data[] = {10, 11, 20, 22, 5};
    size_t size = ARR_LENGTH(data);
    size_t i;

    for(i = 0; i < size; ++i)
    {
        if(VECTOR_SUCCESS != VectorAppend(newVector, &data[i]))
        {
            ++err;
        }
    }

    PrintResualt(testName, scenario, err);
    VectorDestroy(&newVector, NULL);
}

static void TestVectorRemoveVectorNull(void)
{
    int err = 0;
    char *testName = "TestVectorRemove";
    char *scenario = "VectorNull";
    void *voidptr;

    if(VectorRemove(NULL, &voidptr) != VECTOR_UNITIALIZED_ERROR)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestVectorRemoveItemNull(void)
{
    int err = 0;
    char *testName = "TestVectorRemove";
    char *scenario = "ItemNull";
    Vector *newVector = VectorCreate(2,2);

    if(VectorRemove(newVector, NULL) != VECTOR_UNITIALIZED_ERROR)
    {
        ++err;
    }

    VectorDestroy(&newVector, NULL);
    PrintResualt(testName, scenario, err); 
}

static void TestVectorRemoveItemAndVectorNull(void)
{
    int err = 0;
    char *testName = "TestVectorRemove";
    char *scenario = "ItemAndVectorNull";

    if(VectorRemove(NULL, NULL) != VECTOR_UNITIALIZED_ERROR)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err); 
}

static void TestVectorRemoveEmptyVector(void)
{
    int err = 0;
    char *testName = "TestVectorRemove";
    char *scenario = "EmptyVector";
    Vector *newVector = VectorCreate(2,2);
    void *item;

    if(VectorRemove(newVector, &item) != VECTOR_UNDERFLOW)
    {
        ++err;
    }

    VectorDestroy(&newVector, NULL);
    PrintResualt(testName, scenario, err); 
}

static void TestVectorRemoveFullVector(void)
{
    int err = 0;
    char *testName = "TestVectorRemove";
    char *scenario = "FullVector";
    Vector *newVector = VectorCreate(2,2);
    void *item;
    int data[] = {10, 11};

    VectorAppend(newVector, &data[0]);
    VectorAppend(newVector, &data[1]);
    
    if(VectorRemove(newVector, &item) != VECTOR_SUCCESS)
    {
        ++err;
    }

/*     if(*(int *)item != data[1])
    {
        ++err;
    } */

    VectorDestroy(&newVector, NULL);
    PrintResualt(testName, scenario, err); 
}

static void TestVectorGetVectorNull(void)
{
    int err = 0;
    char *testName = "TestVectorGet";
    char *scenario = "VectorNull";
    void *item;

    if(VECTOR_UNITIALIZED_ERROR != VectorGet(NULL, 1, &item))
    {
        ++err;
    }

    PrintResualt(testName, scenario, err); 
}

static void TestVectorGetInvalidIndex(void)
{
    int err = 0;
    char *testName = "TestVectorGet";
    char *scenario = "InvalidIndex";
    Vector *newVector = VectorCreate(2,2);
    void *item;
    int data[] = {10, 11};

    VectorAppend(newVector, &data[0]);
    VectorAppend(newVector, &data[1]);

    if(VECTOR_INDEX_OUT_OF_BOUNDS_ERROR != VectorGet(newVector, 3, &item))
    {
        ++err;
    }

    VectorDestroy(&newVector, NULL);
    PrintResualt(testName, scenario, err); 
}

static void TestVectorGetValidIndex(void)
{
    int err = 0;
    char *testName = "TestVectorGet";
    char *scenario = "VectorNull";
    Vector *newVector = VectorCreate(2,2);
    void *item;
    int data[] = {10, 11};

    VectorAppend(newVector, &data[0]);
    VectorAppend(newVector, &data[1]);

    if(VECTOR_SUCCESS != VectorGet(newVector, 1, &item))
    {
        ++err;
    }

/*     if(*(int *)item != data[0])
    {
        ++err;
    } */
    VectorDestroy(&newVector, NULL);
    PrintResualt(testName, scenario, err); 
}

static void TestVectorSetVectorNull(void)
{
    int err = 0;
    char *testName = "TestVectorSet";
    char *scenario = "VectorNull";
    int i = 9;

    if(VECTOR_UNITIALIZED_ERROR != VectorSet(NULL, 1, &i))
    {
        ++err;
    }

    PrintResualt(testName, scenario, err); 
}

static void TestVectorSetInvalidIndex(void)
{
    int err = 0;
    char *testName = "TestVectorSet";
    char *scenario = "InValidIndex";
    Vector *newVector = VectorCreate(2,2);
    int data[] = {10, 11};

    VectorAppend(newVector, &data[0]);
    VectorAppend(newVector, &data[1]);

    if(VECTOR_INDEX_OUT_OF_BOUNDS_ERROR != VectorSet(newVector, 4, &data[1]))
    {
        ++err;
    }
    
    VectorDestroy(&newVector, NULL);
    PrintResualt(testName, scenario, err); 
}

static void TestVectorSetValidIndex(void)
{
    int err = 0;
    char *testName = "TestVectorSet";
    char *scenario = "ValidIndex";
    Vector *newVector = VectorCreate(2,2);
    int data[] = {10, 11};

    VectorAppend(newVector, &data[0]);
    VectorAppend(newVector, &data[1]);

    if(VECTOR_SUCCESS != VectorSet(newVector, 1, &data[1]))
    {
        ++err;
    }
    
    VectorDestroy(&newVector, NULL);
    PrintResualt(testName, scenario, err); 
}

static void TestVectorSizeAndCapcity(void)
{
    int err = 0;
    char *testName = "TestVectorSizeAndCapcity";
    char *scenario = "";
    Vector *newVector = VectorCreate(10,2);
    int data[] = {10, 11};

    VectorAppend(newVector, &data[0]);
    VectorAppend(newVector, &data[1]);

    if(2 != VectorSize(newVector))
    {
        ++err;
    }

    if(10 != VectorCapacity(newVector))
    {
        ++err;
    }

    if(0 != VectorSize(NULL))
    {
        ++err;
    }

    if(0 != VectorCapacity(NULL))
    {
        ++err;
    }
    
    VectorDestroy(&newVector, NULL);
    PrintResualt(testName, scenario, err); 
}

static void TestVectorForEachVectorNull(void)
{
    int err = 0;
    char *testName = "TestVectorForEach";
    char *scenario = "VectorNull";

    if(0 != VectorForEach(NULL, PrintIntVector, NULL))
    {
        ++err;
    }

    PrintResualt(testName, scenario, err); 
}

static void TestVectorForEachPrintVector(void)
{
    int err = 0;
    char *testName = "TestVectorForEach";
    char *scenario = "PrintVector";
    Vector *newVector = VectorCreate(10,2);
    int data[] = {10, 11};

    VectorAppend(newVector, &data[0]);
    VectorAppend(newVector, &data[1]);
    VectorAppend(newVector, &data[0]);
    VectorAppend(newVector, &data[1]);

    if(VectorSize(newVector) != VectorForEach(newVector, PrintIntVector, NULL))
    {
        ++err;
    }

    VectorDestroy(&newVector, NULL);
    PrintResualt(testName, scenario, err); 
}

/* ---------------------- static functions ---------------------------*/

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

static void ElementDestroy(void* _item)
{
    free(_item);
    return;
}

static int PrintIntVector(void* _element, size_t _index, void* _context)
{
    printf("%d,",*(int *)_element);
    return TRUE;
}


