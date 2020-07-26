#include <stdio.h> /* printf*/ 
#include <stdlib.h> /* malloc , free */
#include "bst.h"
#include "colors.h"

extern BSTreeItr g_BSTWrongIter;

#define ARR_LENGTH(x) (sizeof(x) / sizeof(x[0]))
static void PrintResualt(char *_testName, char *_scenario, int err);
static int IsSmaller(void* _x, void* _y);
static void ElementDestroy(void *_element);
static int IsDataExsist(void * _element, void* _context);
static int IsDataEven(void * _element, void* _context);


static void TestBSTreeCreateFunctionNull(void);
static void TestBSTreeCreateFunctionNotNull(void);

/* static void TestBSTreeDestroyDubbleFree(void); */
static void TestBSTreeDestroyBSTNull(void);
static void TestBSTreeDestroyBSTDynamicAllocation(void);

static void TestBSTreeInsertBSTNULL(void);
static void TestBSTreeInsertItemNull(void);
static void TestBSTreeInsertExisistItem(void);
static void TestBSTreeInsert10Item(void);

static void TestBSTreeFindFirstBSTNULL(void);
static void TestBSTreeFindFirstPradicateNULL(void);
static void TestBSTreeFindFirstContextNULL(void);
static void TestBSTreeFindFirstDataExsist(void);
static void TestBSTreeFindFirstPredicateMoreThen1(void);
static void TestBSTreeFindFirstDataNotExsist(void);

static void TestBSTreeItrBeginTreeNull(void);
static void TestBSTreeItrBeginTreeNotNull(void);
/* static void TestBSTreeItrBeginEmptyTree(void); */

static void TestBSTreeItrEndTreeNull(void);
static void TestBSTreeItrEndTreeNotNull(void);

static void TestBSTreeItrNextTreeNull(void);
static void TestBSTreeItrNextEmptyTree(void);
static void TestBSTreeItrNextAndGet(void);

static void TestBSTreeItrPrevTreeNull(void);
static void TestBSTreeItrPrevEmptyTree(void);
static void TestBSTreeItrPrevAndGet(void);


int main(void)
{
    TestBSTreeCreateFunctionNull();
    TestBSTreeCreateFunctionNotNull();

/*     TestBSTreeDestroyDubbleFree(); */
    TestBSTreeDestroyBSTNull();
    TestBSTreeDestroyBSTDynamicAllocation();

    TestBSTreeInsertBSTNULL();
    TestBSTreeInsertItemNull();
    TestBSTreeInsertExisistItem();
    TestBSTreeInsert10Item();

    TestBSTreeFindFirstBSTNULL();
    TestBSTreeFindFirstPradicateNULL();
    TestBSTreeFindFirstContextNULL();
    TestBSTreeFindFirstDataExsist();
    TestBSTreeFindFirstPredicateMoreThen1();
    TestBSTreeFindFirstDataNotExsist();

    TestBSTreeItrBeginTreeNull();
    TestBSTreeItrBeginTreeNotNull();

    TestBSTreeItrEndTreeNull();
    TestBSTreeItrEndTreeNotNull();

    TestBSTreeItrNextTreeNull();
    TestBSTreeItrNextEmptyTree();
    TestBSTreeItrNextAndGet();

    TestBSTreeItrPrevTreeNull();
    TestBSTreeItrPrevEmptyTree();
    TestBSTreeItrPrevAndGet();

    return 0;
}


static void TestBSTreeCreateFunctionNull(void)
{
    char *testNmae = "TestBSTreeCreate";
    char *scenario = "FunctionNull";
    int err = 0;

    if( NULL != BSTreeCreate(NULL))
    {
        ++err;
    }

    PrintResualt(testNmae, scenario, err);
}

static void TestBSTreeCreateFunctionNotNull(void)
{
    char *testNmae = "TestBSTreeCreate";
    char *scenario = "FunctionNotNull";
    int err = 0;
    BSTree *newBST = BSTreeCreate(IsSmaller);

    if(NULL == newBST)
    {
        ++err;
    }

    BSTreeDestroy(newBST, NULL);

    PrintResualt(testNmae, scenario, err);
}

/* static void TestBSTreeDestroyDubbleFree(void)
{
    char *testNmae = "TestBSTreeDestroy";
    char *scenario = "DubbleFree";
    int err = 0;
    BSTree *newBST = BSTreeCreate(IsSmaller);

    BSTreeDestroy(newBST, NULL);
    BSTreeDestroy(newBST, NULL);

    PrintResualt(testNmae, scenario, err);
} */

static void TestBSTreeDestroyBSTNull(void)
{
    char *testNmae = "TestBSTreeDestroy";
    char *scenario = "BSTNull";
    int err = 0;

    BSTreeDestroy(NULL, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestBSTreeDestroyBSTDynamicAllocation(void)
{
    char *testNmae = "TestBSTreeDestroy";
    char *scenario = "DubbleFree";
    int err = 0;
    BSTree *newBST = BSTreeCreate(IsSmaller);
    int toInsert = 7;
    int *data = (int *)malloc(sizeof(int *));
    data = &toInsert;

    BSTreeInsert(newBST, (void *)data);
    BSTreeDestroy(newBST, ElementDestroy);

    PrintResualt(testNmae, scenario, err);
}

static void TestBSTreeInsertBSTNULL(void)
{
    char *testNmae = "TestBSTreeInsert";
    char *scenario = "BSTNULL";
    int err = 0;
    int data = 8;
  
    if(BSTreeItrEquals(BSTreeItrEnd(NULL), BSTreeInsert(NULL, &data)))
    {
        ++err;
    }

    PrintResualt(testNmae, scenario, err);
}

static void TestBSTreeInsertItemNull(void)
{
    char *testNmae = "TestBSTreeInsert";
    char *scenario = "ItemNull";
    int err = 0;
    BSTree *newBST = BSTreeCreate(IsSmaller);

    if(BSTreeItrEquals(BSTreeItrEnd(NULL), BSTreeInsert(newBST, NULL)))
    {
        ++err;
    }

    BSTreeDestroy(newBST, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestBSTreeInsertExisistItem(void)
{
    char *testNmae = "TestBSTreeInsert";
    char *scenario = "ExisistItem";
    int err = 0;
    BSTree *newBST = BSTreeCreate(IsSmaller);
    int data = 9;
    BSTNode *node;

    node = BSTreeInsert(newBST, &data);
    
    if(!BSTreeItrEquals(BSTreeItrEnd(newBST), BSTreeInsert(newBST, &data)))
    {
        ++err;
    }

    BSTreeDestroy(newBST, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestBSTreeInsert10Item(void)
{
    char *testNmae = "TestBSTreeInsert";
    char *scenario = "10Item";
    int err = 0;
    BSTree *newBST = BSTreeCreate(IsSmaller);
    int data[] = {1,2,3,4,5,6,7,8,9,10};
    size_t i;
    size_t size = ARR_LENGTH(data);
    BSTreeItr iter;

    for(i = 0; i < size; ++i)
    {
        iter = BSTreeInsert(newBST, &(data[i]));
        if(*(int *)BSTreeItrGet(iter) != data[i])
        {
            ++err;
        }
    }

    BSTreeDestroy(newBST, NULL);
    PrintResualt(testNmae, scenario, err);
}


static void TestBSTreeFindFirstBSTNULL(void)
{
    char *testNmae = "TestBSTreeFindFirst";
    char *scenario = "BSTNULL";
    int err = 0;
    int context = 9;

    if(!BSTreeItrEquals(BSTreeItrEnd(NULL) ,BSTreeFindFirst(NULL, IsDataExsist, &context)))
    {
        ++err;
    }
    
    PrintResualt(testNmae, scenario, err);
}

static void TestBSTreeFindFirstPradicateNULL(void)
{
    char *testNmae = "TestBSTreeFindFirst";
    char *scenario = "PradicateNULL";
    int err = 0;
    int context = 9;
    BSTree *newBST = BSTreeCreate(IsSmaller);

    if(!BSTreeItrEquals(BSTreeItrEnd(NULL) ,BSTreeFindFirst(newBST, NULL, &context)))
    {
        ++err;
    }
    
    BSTreeDestroy(newBST, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestBSTreeFindFirstContextNULL(void)
{
    char *testNmae = "TestBSTreeFindFirst";
    char *scenario = "PradicateNULL";
    int err = 0;
    BSTree *newBST = BSTreeCreate(IsSmaller);

    if(!BSTreeItrEquals(BSTreeItrEnd(NULL) ,BSTreeFindFirst(newBST, IsDataExsist, NULL)))
    {
        ++err;
    }
    
    BSTreeDestroy(newBST, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestBSTreeFindFirstDataExsist(void)
{
    char *testNmae = "TestBSTreeFindFirst";
    char *scenario = "PradicateNULL";
    int err = 0;
    BSTree *newBST = BSTreeCreate(IsSmaller);
    int data = 9;

    BSTreeInsert(newBST, &data);

    if(!BSTreeItrEquals(BSTreeItrBegin(newBST) ,BSTreeFindFirst(newBST, IsDataExsist, &data)))
    {
        ++err;
    }
    
    BSTreeDestroy(newBST, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestBSTreeFindFirstDataNotExsist(void)
{
    char *testNmae = "TestBSTreeFindFirst";
    char *scenario = "PradicateNULL";
    int err = 0;
    BSTree *newBST = BSTreeCreate(IsSmaller);
    int data []= {1,2,3,4,5,6,7,8,9};
    int notExsist = 10;
    size_t size = ARR_LENGTH(data);
    size_t i;

    for (i = 0; i < size ; ++i)
    {
        BSTreeInsert(newBST, &data[i]);
    }
    
    if(!BSTreeItrEquals(BSTreeItrEnd(newBST) ,BSTreeFindFirst(newBST, IsDataExsist, &notExsist)))
    {
        ++err;
    }
    
    BSTreeDestroy(newBST, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestBSTreeFindFirstPredicateMoreThen1(void)
{
    char *testNmae = "TestBSTreeFindFirst";
    char *scenario = "PredicateMoreThen1";
    int err = 0;
    int data []= {1,2,3,4,5,6,7,8,9};
    size_t size = ARR_LENGTH(data);
    size_t i;
    BSTree *newBST = BSTreeCreate(IsSmaller);

    for (i = 0; i < size ; ++i)
    {
        BSTreeInsert(newBST, &data[i]);
    }

    if(2 != *(int *)BSTreeItrGet(BSTreeFindFirst(newBST, IsDataEven, NULL)))
    {
        ++err;
    }

    BSTreeDestroy(newBST, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestBSTreeItrBeginTreeNull(void)
{
    char *testNmae = "TestBSTreeItrBegin";
    char *scenario = "TreeNull";
    int err = 0;

    if(g_BSTWrongIter != BSTreeItrBegin(NULL))
    {
        ++err;
    }

    PrintResualt(testNmae, scenario, err);
}

static void TestBSTreeItrBeginTreeNotNull(void)
{
    char *testNmae = "TestBSTreeItrBegin";
    char *scenario = "TreeNotNull";
    int err = 0;
    int data []= {1,2,3,4,5,6,7,8,9};
    size_t size = ARR_LENGTH(data);
    size_t i = size -1;
    BSTree *newBST = BSTreeCreate(IsSmaller);

    for(; size > 0; --i)
    {
        BSTreeInsert(newBST, &data[i]);
    }

    if(data[0] != *(int *)BSTreeItrGet(BSTreeItrBegin(newBST)))
    {
        ++err;
    }

    BSTreeDestroy(newBST, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestBSTreeItrEndTreeNull(void)
{
    char *testNmae = "TestBSTreeItrEnd";
    char *scenario = "TreeNull";
    int err = 0;

    if(g_BSTWrongIter != BSTreeItrEnd(NULL))
    {
        ++err;
    }

    PrintResualt(testNmae, scenario, err);
}

static void TestBSTreeItrEndTreeNotNull(void)
{
    char *testNmae = "TestBSTreeItrEnd";
    char *scenario = "TreeNotNull";
    int err = 0;
    int data []= {1,2,3,4,5};
    size_t size = ARR_LENGTH(data);
    size_t i = 0;
    BSTree *newBST = BSTreeCreate(IsSmaller);

    for(; i < size; ++i)
    {
        BSTreeInsert(newBST, &data[i]);
    }

    if(!BSTreeItrEquals(BSTreeItrEnd(newBST), BSTreeItrNext(BSTreeItrEnd(newBST))))
    {
        ++err;
    }

    BSTreeDestroy(newBST, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestBSTreeItrNextTreeNull(void)
{
    char *testNmae = "TestBSTreeItrNext";
    char *scenario = "TreeNull";
    int err = 0;

    if(g_BSTWrongIter != BSTreeItrNext(NULL))
    {
        ++err;
    }

    PrintResualt(testNmae, scenario, err);
}

static void TestBSTreeItrNextEmptyTree(void)
{
    char *testNmae = "TestBSTreeItrNext";
    char *scenario = "TreeNull";
    int err = 0;
    BSTree *newBST = BSTreeCreate(IsSmaller);


    if(!BSTreeItrEquals(BSTreeItrEnd(newBST),BSTreeItrNext(BSTreeItrBegin(newBST))))
    {
        ++err;
    }
    
    BSTreeDestroy(newBST, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestBSTreeItrNextAndGet(void)
{
    char *testNmae = "TestBSTreeItrNext";
    char *scenario = "AndGet";
    int err = 0;
    int data []= {1,2,3,4,5};
    size_t size = ARR_LENGTH(data);
    size_t i = 0;
    BSTree *newBST = BSTreeCreate(IsSmaller);
    BSTreeItr itr;

    for(; i < size; ++i)
    {
        BSTreeInsert(newBST, &data[i]);
    }

    i = 0;
    itr = BSTreeItrBegin(newBST);

    if(data[i++] != *(int *)BSTreeItrGet(itr))
    {
        ++err;
    }

    for(; i < size; ++i)
    {
        itr = BSTreeItrNext(itr);
        if(data[i] != *(int *)BSTreeItrGet(itr))
        {
            ++err;
        }
    }

    BSTreeDestroy(newBST, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestBSTreeItrPrevTreeNull(void)
{
    char *testNmae = "TestBSTreeItrPrev";
    char *scenario = "TreeNull";
    int err = 0;

    if(g_BSTWrongIter != BSTreeItrPrev(NULL))
    {
        ++err;
    }

    PrintResualt(testNmae, scenario, err);
}

static void TestBSTreeItrPrevEmptyTree(void)
{
    char *testNmae = "TestBSTreeItrNext";
    char *scenario = "TreeNull";
    int err = 0;
    BSTree *newBST = BSTreeCreate(IsSmaller);

    if(!BSTreeItrEquals(BSTreeItrBegin(newBST),BSTreeItrPrev(BSTreeItrBegin(newBST))))
    {
        ++err;
    }
    
    BSTreeDestroy(newBST, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestBSTreeItrPrevAndGet(void)
{
        char *testNmae = "TestBSTreeItrNext";
    char *scenario = "AndGet";
    int err = 0;
    int data []= {1,2,3,4,5};
    size_t size = ARR_LENGTH(data);
    size_t i = 0;
    BSTree *newBST = BSTreeCreate(IsSmaller);
    BSTreeItr itr;

    for(; i < size; ++i)
    {
        BSTreeInsert(newBST, &data[i]);
    }

    i = size - 1;
    itr = BSTreeItrEnd(newBST);

    for(; i < size; ++i)
    {
        itr = BSTreeItrPrev(itr);
        if(data[i] != *(int *)BSTreeItrGet(itr))
        {
            ++err;
        }
    }

    BSTreeDestroy(newBST, NULL);
    PrintResualt(testNmae, scenario, err);
}

/* --------------------helpful functions ----------------------------*/
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

static int IsSmaller(void* _x, void* _y)
{
    return (*(int *)_x > *(int *)_y);
}

static void ElementDestroy(void *_element)
{
    free(_element);
}

static int IsDataExsist(void * _element, void* _context)
{
    return *(int *)_element == *(int *)_context;
}

static int IsDataEven(void * _element, void* _context)
{
    return *(int *)_element % 2 == 0;
}
