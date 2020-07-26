#include <stdio.h> /* printf */

#include "heap.h" /* API functions */
#include "colors.h"

static void PrintResualt(char *_testName, char *_scenario, int err);

static void TestBuildHeap(void);
static void TestBuildHeapVectorNull(void);

static void TestHeapDestroyNULL(void);
static void TestHeapDestroyDoubleFree(void);

static void TestHeapInsertNULL(void);
static void TestHeapInsertSameData(void);
static void TestHeapInsertBigAfterSmall(void);
static void TestHeapInsertSmallAfterBig(void);

static void TestHeapMax(void);
static void TestHeapMaxDataNULL(void);
static void TestHeapMaxHeapNULL(void);
static void TestHeapMaxHeapNULLs(void);

static void TestHeapItemsNumNULL(void);
static void TestHeapItemsNumEmptyHeap(void);
static void TestHeapItemsNum10Inserts(void);
static void TestHeapItemsNum10InsertsExtract9(void);

static void TestHeapExtractMaxHeapNULL(void);
static void TestHeapExtractMaxDataNULL(void);
static void TestHeapExtractMaxNULLs(void);
static void TestHeapExtractMaxEmptyHeap(void);
static void TestHeapExtractMaxOneData(void);
static void TestHeapExtractMaxMultiplyData(void);

int main(void)
{
    TestBuildHeap();
    TestBuildHeapVectorNull();

    TestHeapDestroyNULL();
    TestHeapDestroyDoubleFree();

    TestHeapInsertNULL();
    TestHeapInsertSameData();
    TestHeapInsertBigAfterSmall();
    TestHeapInsertSmallAfterBig();

    TestHeapMax();
    TestHeapMaxDataNULL();
    TestHeapMaxHeapNULL();
    TestHeapMaxHeapNULLs();

    TestHeapItemsNumNULL();
    TestHeapItemsNumEmptyHeap();
    TestHeapItemsNum10Inserts();
    TestHeapItemsNum10InsertsExtract9();

    TestHeapExtractMaxHeapNULL();
    TestHeapExtractMaxDataNULL();
    TestHeapExtractMaxNULLs();
    TestHeapExtractMaxEmptyHeap();
    TestHeapExtractMaxOneData();
    TestHeapExtractMaxMultiplyData();

    return 0;
}

static void TestBuildHeap(void)
{
    int err = 0;
    char *testName = "TestBuildHeap";
    char *scenario = "";
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector);

    if (NULL == heap)
    {
        ++err;
    }

    HeapDestroy(heap);
    VectorDestroy(vector);
    PrintResualt(testName, scenario, err);
}

static void TestBuildHeapVectorNull(void)
{
    int err = 0;
    char *testName = "TestBuildHeap";
    char *scenario = "VectorNull";
    Heap *heap = HeapBuild(NULL);

    if (NULL != heap)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestHeapDestroyNULL(void)
{
    int err = 0;
    char *testName = "TestHeapDestroy";
    char *scenario = "NULL";

    HeapDestroy(NULL);

    PrintResualt(testName, scenario, err);
}

static void TestHeapDestroyDoubleFree(void)
{
    int err = 0;
    char *testName = "TestHeapDestroy";
    char *scenario = "DoubleFree";
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector);

    HeapDestroy(heap);
    HeapDestroy(heap);

    VectorDestroy(vector);

    PrintResualt(testName, scenario, err);
}

static void TestHeapInsertNULL(void)
{
    int err = 0;
    char *testName = "TestHeapInsert";
    char *scenario = "NULL";

    if (ERR_NOT_INITIALZED != HeapInsert(NULL, 100))
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestHeapInsertSameData(void)
{
    int err = 0;
    char *testName = "TestHeapInsert";
    char *scenario = "SameData";
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector);

    if (ERR_OK != HeapInsert(heap, 100))
    {
        ++err;
    }

    if (ERR_OK != HeapInsert(heap, 100))
    {
        ++err;
    }

    HeapDestroy(heap);
    VectorDestroy(vector);

    PrintResualt(testName, scenario, err);
}

static void TestHeapInsertBigAfterSmall(void)
{
    int err = 0;
    int max = 0;
    char *testName = "TestHeapInsert";
    char *scenario = "BigAfterSmall";
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector);

    if (ERR_OK != HeapInsert(heap, 100))
    {
        ++err;
    }

    if (ERR_OK != HeapInsert(heap, 200))
    {
        ++err;
    }

    HeapMax(heap, &max);

    if (max != 200)
    {
        ++err;
    }

    HeapDestroy(heap);
    VectorDestroy(vector);

    PrintResualt(testName, scenario, err);
}

static void TestHeapInsertSmallAfterBig(void)
{
    int err = 0;
    int max = 0;
    char *testName = "TestHeapInsert";
    char *scenario = "SmallAfterBig";
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector);

    if (ERR_OK != HeapInsert(heap, 200))
    {
        ++err;
    }

    if (ERR_OK != HeapInsert(heap, 100))
    {
        ++err;
    }

    HeapMax(heap, &max);

    if (max != 200)
    {
        ++err;
    }

    HeapDestroy(heap);
    VectorDestroy(vector);

    PrintResualt(testName, scenario, err);
}

static void TestHeapMaxHeapNULL(void)
{
    int err = 0;
    int max = 0;
    char *testName = "HeapMax";
    char *scenario = "HeapNULL";

    if (ERR_NOT_INITIALZED != HeapMax(NULL, &max))
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestHeapMaxDataNULL(void)
{
    int err = 0;
    int max = 0;
    char *testName = "HeapMax";
    char *scenario = "DataNULL";
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector);

    if (ERR_NOT_INITIALZED != HeapMax(heap, NULL))
    {
        ++err;
    }

    HeapDestroy(heap);
    VectorDestroy(vector);

    PrintResualt(testName, scenario, err);
}

static void TestHeapMaxHeapNULLs(void)
{
    int err = 0;
    int max = 0;
    char *testName = "HeapMax";
    char *scenario = "NULLs";

    if (ERR_NOT_INITIALZED != HeapMax(NULL, NULL))
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestHeapMax(void)
{
    int err = 0;
    int max = 0;
    char *testName = "HeapMax";
    char *scenario = "";
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector);

    HeapInsert(heap, 100);
    HeapInsert(heap, 20);
    HeapInsert(heap, 60);
    HeapInsert(heap, 50);
    HeapInsert(heap, 30);

    if (ERR_OK != HeapMax(heap, &max))
    {
        ++err;
    }

    if (max != 100)
    {
        ++err;
    }

    HeapDestroy(heap);
    VectorDestroy(vector);

    PrintResualt(testName, scenario, err);
}

static void TestHeapItemsNumNULL(void)
{
    int err = 0;
    int max = 0;
    char *testName = "HeapItemsNum";
    char *scenario = "NULL";

    if (-1 != HeapItemsNum(NULL))
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestHeapItemsNumEmptyHeap(void)
{
    int err = 0;
    int max = 0;
    char *testName = "HeapMax";
    char *scenario = "EmptyHeap";
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector);

    if (0 != HeapItemsNum(heap))
    {
        ++err;
    }

    HeapDestroy(heap);
    VectorDestroy(vector);

    PrintResualt(testName, scenario, err);
}

static void TestHeapItemsNum10Inserts(void)
{
    int err = 0;
    char *testName = "HeapMax";
    char *scenario = "10Inserts";
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector);

    HeapInsert(heap, 100);
    HeapInsert(heap, 20);
    HeapInsert(heap, 60);
    HeapInsert(heap, 50);
    HeapInsert(heap, 30);
    HeapInsert(heap, 10);
    HeapInsert(heap, 2);
    HeapInsert(heap, 6);
    HeapInsert(heap, 5);
    HeapInsert(heap, 3);

    if (10 != HeapItemsNum(heap))
    {
        ++err;
    }

    HeapDestroy(heap);
    VectorDestroy(vector);

    PrintResualt(testName, scenario, err);
}

static void TestHeapItemsNum10InsertsExtract9(void)
{
    int err = 0;
    int max = 0;
    char *testName = "HeapItemsNum";
    char *scenario = "10InsertsExtract9";
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector);

    HeapInsert(heap, 100);

    HeapInsert(heap, 20);

    HeapInsert(heap, 60);

    HeapInsert(heap, 50);

    HeapInsert(heap, 30);

    HeapInsert(heap, 10);

    HeapInsert(heap, 2);

    HeapInsert(heap, 6);

    HeapInsert(heap, 5);

    HeapInsert(heap, 3);

    if (10 != HeapItemsNum(heap))
    {
        ++err;
    }

    HeapExtractMax(heap, &max);

    if (max != 100)
    {
        ++err;
    }



    HeapExtractMax(heap, &max);
    if (max != 60)
    {
        ++err;
    }


    HeapExtractMax(heap, &max);
    if (max != 50)
    {
        ++err;
    }



    HeapExtractMax(heap, &max);
    if (max != 30)
    {
        ++err;
    }

    HeapExtractMax(heap, &max);
    if (max != 20)
    {
        ++err;
    }

    HeapExtractMax(heap, &max);
    if (max != 10)
    {
        ++err;
    }

    HeapExtractMax(heap, &max);
    if (max != 6)
    {
        ++err;
    }

    HeapExtractMax(heap, &max);
    if (max != 5)
    {
        ++err;
    }

    HeapExtractMax(heap, &max);
    if (max != 3)
    {
        ++err;
    }

    if (1 != HeapItemsNum(heap))
    {
        ++err;
    }
/*     printf("%d\n", err); */

    HeapDestroy(heap);
    VectorDestroy(vector);

    PrintResualt(testName, scenario, err);
}
static void TestHeapExtractMaxHeapNULL(void)
{
    int err = 0;
    int data = 0;
    char *testName = "HeapExtractMax";
    char *scenario = "HeapNULL";

    if (ERR_NOT_INITIALZED != HeapExtractMax(NULL, &data))
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestHeapExtractMaxDataNULL(void)
{
    int err = 0;
    int data = 0;
    char *testName = "HeapExtractMax";
    char *scenario = "DataNULL";
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector);

    if (ERR_NOT_INITIALZED != HeapExtractMax(heap, NULL))
    {
        ++err;
    }

    HeapDestroy(heap);
    VectorDestroy(vector);

    PrintResualt(testName, scenario, err);
}

static void TestHeapExtractMaxNULLs(void)
{
    int err = 0;
    char *testName = "HeapExtractMax";
    char *scenario = "NULLs";

    if (ERR_NOT_INITIALZED != HeapExtractMax(NULL, NULL))
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestHeapExtractMaxEmptyHeap(void)
{
    int err = 0;
    int data = 0;
    char *testName = "HeapExtractMax";
    char *scenario = "EmptyHeap";
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector);

    if (ERR_UNDERFLOW != HeapExtractMax(heap, &data))
    {
        ++err;
    }

    HeapDestroy(heap);
    VectorDestroy(vector);

    PrintResualt(testName, scenario, err);
}

static void TestHeapExtractMaxOneData(void)
{
    int err = 0;
    int data = 0;
    char *testName = "HeapExtractMax";
    char *scenario = "MaxOneData";
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector);

    HeapInsert(heap, 90);

    if (ERR_OK != HeapExtractMax(heap, &data))
    {
        ++err;
    }

    if (90 != data)
    {
        ++err;
    }

    HeapDestroy(heap);
    VectorDestroy(vector);

    PrintResualt(testName, scenario, err);
}

static void TestHeapExtractMaxMultiplyData(void)
{
    int err = 0;
    int data = 0;
    char *testName = "HeapExtractMax";
    char *scenario = "MultiplyData";
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector);

    HeapInsert(heap, 90);
    HeapInsert(heap, 40);
    HeapInsert(heap, 50);
    HeapInsert(heap, 80);
    HeapInsert(heap, 200);
    HeapInsert(heap, 100);

    if (ERR_OK != HeapExtractMax(heap, &data))
    {
        ++err;
    }

    if (200 != data)
    {
        ++err;
    }

    HeapMax(heap, &data);

    if (100 != data)
    {
        ++err;
    }

    HeapDestroy(heap);
    VectorDestroy(vector);

    PrintResualt(testName, scenario, err);
}

/*--------------------- static functions---------------------------*/
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