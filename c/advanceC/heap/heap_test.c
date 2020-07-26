#include <stdio.h> /* printf */
#include "heap.h" /* API functions */
#include "colors.h"

#define ARR_LENGTH(x) (sizeof(x) / sizeof(x[0]))

static void PrintResualt(char *_testName, char *_scenario, int err);
static int	IsLess(const void *_left, const void *_right);
static int PrintIntHeap(const void* _element, void* _context);
static int VectorForEachFunc(const void* _element, size_t _index, void* _context);
static void PrintVector(Vector *_vec); /* for debug */

static void TestBuildHeapFunctionNULL(void);
static void TestBuildHeapVectorNull(void);
static void TestBuildHeap(void);

static void TestHeapDestroyNULL(void);
static void TestHeapDestroyDoubleFree(void);

static void TestHeapInsertHeapNULL(void);
static void TestHeapInsertElementNULL(void);
static void TestHeapInsertSameData(void);
static void TestHeapInsertBigAfterSmall(void);
static void TestHeapInsertSmallAfterBig(void);

static void TestHeapPeak(void);
static void TestHeapPeakHeapNULL(void);
static void TestHeapPeakEmptyHeap(void);

static void TestHeapExtractHeapNULL(void);
static void TestHeapExtractEmptyHeap(void);
static void TestHeapExtractOneData(void);
static void TestHeapExtractMultiplyData(void);

static void TestHeapSizeHeapNULL(void);
static void TestHeapSizeEmptyHeap(void);
static void TestHeapSize10Inserts(void);
static void TestHeapSize10InsertsExtract5(void);

static void TestHeapForEachHeapNull(void);
static void TestHeapForEachFanctionNull(void);
static void TestHeapForEachEmptyHeap(void);
static void TestHeapForEachPrintHeap(void);

static void TestHeapSortUnsortedVector(void);
static void TestHeapSortSortedVector(void);

int main(void)
{
    TestBuildHeapFunctionNULL();
    TestBuildHeapVectorNull();
    TestBuildHeap();

    TestHeapDestroyNULL();
    TestHeapDestroyDoubleFree();

    TestHeapInsertHeapNULL();
    TestHeapInsertElementNULL();
    TestHeapInsertSameData();
    TestHeapInsertBigAfterSmall();
    TestHeapInsertSmallAfterBig();

    TestHeapPeak();
    TestHeapPeakHeapNULL();
    TestHeapPeakEmptyHeap();

    TestHeapExtractHeapNULL();
    TestHeapExtractEmptyHeap();
    TestHeapExtractOneData();
    TestHeapExtractMultiplyData();

    TestHeapSizeHeapNULL();
    TestHeapSizeEmptyHeap();
    TestHeapSize10Inserts();
    TestHeapSize10InsertsExtract5();

    TestHeapForEachHeapNull();
    TestHeapForEachFanctionNull();
    TestHeapForEachEmptyHeap();
    TestHeapForEachPrintHeap();

    TestHeapSortUnsortedVector();
    TestHeapSortSortedVector();

    return 0;
}

static void TestBuildHeapFunctionNULL(void)
{
    int err = 0;
    char *testName = "TestBuildHeap";
    char *scenario = "FunctionNULL";
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,NULL);

    if (NULL != heap)
    {
        ++err;
    }

    VectorDestroy(&vector, NULL);
    PrintResualt(testName, scenario, err);
}

static void TestBuildHeapVectorNull(void)
{
    int err = 0;
    char *testName = "TestBuildHeap";
    char *scenario = "VectorNull";
    Heap *heap = HeapBuild(NULL ,IsLess);

    if (NULL != heap)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestBuildHeap(void)
{
    int err = 0;
    char *testName = "TestBuildHeap";
    char *scenario = "";
    Vector *vector = VectorCreate(4, 4);
    int data[] = {7,20,5,81,3};
    size_t size = ARR_LENGTH(data);
    Heap *heap =  NULL;
    size_t i;
    void *getData;

    for(i = 0; i < size; ++i)
    {
        VectorAppend(vector, &data[i]);
    }

    heap = HeapBuild(vector ,IsLess);

    if (NULL == heap)
    {
        ++err;
    }

    VectorDestroy(&vector, NULL);
    HeapDestroy(&heap);
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
    Heap *heap = HeapBuild(vector ,IsLess);

    HeapDestroy(&heap);
    HeapDestroy(&heap);

    VectorDestroy(&vector, NULL);
    PrintResualt(testName, scenario, err);
}

static void TestHeapInsertHeapNULL(void)
{
    int err = 0;
    char *testName = "TestHeapInsert";
    char *scenario = "HeapNULL";
    int data = 5;

    if(HEAP_NOT_INITIALIZED != HeapInsert(NULL ,&data))
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestHeapInsertElementNULL(void)
{
    int err = 0;
    char *testName = "TestHeapInsert";
    char *scenario = "ElementNULL";
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,IsLess);
    
    if(HEAP_NOT_INITIALIZED != HeapInsert(heap, NULL))
    {
        ++err;
    }

    HeapDestroy(&heap);
    VectorDestroy(&vector, NULL);

    PrintResualt(testName, scenario, err);
}

static void TestHeapInsertSameData(void)
{
    int err = 0;
    char *testName = "TestHeapInsert";
    char *scenario = "SameData";
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,IsLess);
    int data[] = {55,55,10,10};
    size_t size = ARR_LENGTH(data);
    size_t i;

    for(i = 0; i < size; ++i)
    {
        if(HEAP_SUCCESS != HeapInsert(heap, &data[i]))
        {
            ++err;
        }
    }
    
    if(*(int *)HeapPeek(heap) != data[0])
    {
        ++err;
    }

    HeapDestroy(&heap);
    VectorDestroy(&vector, NULL);

    PrintResualt(testName, scenario, err);    
}

static void TestHeapInsertBigAfterSmall(void)
{
    int err = 0;
    char *testName = "TestHeapInsert";
    char *scenario = "BigAfterSmall";
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,IsLess);
    int data[] = {5,10,100,40};
    size_t size = ARR_LENGTH(data);
    size_t i;
    void *printData;

    for(i = 0; i < size; ++i)
    {
        if(HEAP_SUCCESS != HeapInsert(heap, &data[i]))
        {
            ++err;
        }
    }
    
    for(i = 1; i < size + 1; ++i)
    {
        VectorGet(vector, i, &printData);
        printf("%d,",*(int *)printData);
    }
    putchar('\n');

    if(*(int *)HeapPeek(heap) != data[2])
    {
        ++err;
    }

    HeapDestroy(&heap);
    VectorDestroy(&vector, NULL);

    PrintResualt(testName, scenario, err);   
}

static void TestHeapInsertSmallAfterBig(void)
{
    int err = 0;
    char *testName = "TestHeapInsert";
    char *scenario = "SmallAfterBig";
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,IsLess);
    int data[] = {500,10,100,400};
    size_t size = ARR_LENGTH(data);
    size_t i;

    for(i = 0; i < size; ++i)
    {
        if(HEAP_SUCCESS != HeapInsert(heap, &data[i]))
        {
            ++err;
        }
    }
    
    if(*(int *)HeapPeek(heap) != data[0])
    {
        ++err;
    }

    HeapDestroy(&heap);
    VectorDestroy(&vector, NULL);

    PrintResualt(testName, scenario, err);  
}

static void TestHeapPeak(void)
{
    int err = 0;
    char *testName = "TestHeapPeak";
    char *scenario = "";
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,IsLess);
    int data[] = {500,10,100,400};
    size_t size = ARR_LENGTH(data);
    size_t i;
    void *extractData;

    for(i = 0; i < size; ++i)
    {
        if(HEAP_SUCCESS != HeapInsert(heap, &data[i]))
        {
            ++err;
        }
    }

    if(*(int *)HeapPeek(heap) != data[0])
    {
        ++err;
    }

    extractData = HeapExtract(heap);

    if(*(int *)extractData != data[0])
    {
        ++err;
    }

    if(*(int *)HeapPeek(heap) != data[3])
    {
        ++err;
    }

    extractData = HeapExtract(heap);

    if(*(int *)HeapPeek(heap) != data[2])
    {
        ++err;
    }

    HeapDestroy(&heap);
    VectorDestroy(&vector, NULL);

    PrintResualt(testName, scenario, err);  
}

static void TestHeapPeakEmptyHeap(void)
{
    int err = 0;
    char *testName = "TestHeapPeak";
    char *scenario = "EmptyHeap";
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,IsLess);

    if(HeapPeek(heap) != NULL)
    {
        ++err;
    }

    HeapDestroy(&heap);
    VectorDestroy(&vector, NULL);

    PrintResualt(testName, scenario, err);  
}

static void TestHeapPeakHeapNULL(void)
{
    int err = 0;
    char *testName = "TestHeapPeak";
    char *scenario = "HeapNULL";

    if(HeapPeek(NULL) != NULL)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);  
}

static void TestHeapExtractHeapNULL(void)
{
    int err = 0;
    char *testName = "TestHeapExtract";
    char *scenario = "HeapNULL";

    if(HeapExtract(NULL) != NULL)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err); 
}

static void TestHeapExtractEmptyHeap(void)
{
    int err = 0;
    char *testName = "TestHeapExtract";
    char *scenario = "EmptyHeap";
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,IsLess);

    if(HeapExtract(NULL) != NULL)
    {
        ++err;
    }

    HeapDestroy(&heap);
    VectorDestroy(&vector, NULL);

    PrintResualt(testName, scenario, err);  
}

static void TestHeapExtractOneData(void)
{
    int err = 0;
    char *testName = "TestHeapExtract";
    char *scenario = "EmptyHeap";
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,IsLess);
    int data = 7;

    HeapInsert(heap, &data);

    if(*(int *)HeapExtract(heap) != data)
    {
        ++err;
    }

    HeapDestroy(&heap);
    VectorDestroy(&vector, NULL);

    PrintResualt(testName, scenario, err);  
}

static void TestHeapExtractMultiplyData(void)
{
    int err = 0;
    char *testName = "TestHeapExtract";
    char *scenario = "EmptyHeap";
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,IsLess);
    int data[] = {500,10,100,400};
    size_t size = ARR_LENGTH(data);
    size_t i;

    for(i = 0; i < size; ++i)
    {
        HeapInsert(heap, &data[i]);
    }

    if(*(int *)HeapExtract(heap) != data[0])
    {
        ++err;
    }

    if(*(int *)HeapExtract(heap) != data[3])
    {
        ++err;
    }

    if(*(int *)HeapExtract(heap) != data[2])
    {
        ++err;
    }

    if(*(int *)HeapExtract(heap) != data[1])
    {
        ++err;
    }

    HeapDestroy(&heap);
    VectorDestroy(&vector, NULL);

    PrintResualt(testName, scenario, err);  
}

static void TestHeapSizeHeapNULL(void)
{
    int err = 0;
    char *testName = "TestHeapSize";
    char *scenario = "HeapNULL";

    if(HeapSize(NULL) != 0)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestHeapSizeEmptyHeap(void)
{
    int err = 0;
    char *testName = "TestHeapSize";
    char *scenario = "EmptyHeap";
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,IsLess);

    if(HeapSize(heap) != 0)
    {
        ++err;
    }

    HeapDestroy(&heap);
    VectorDestroy(&vector, NULL);

    PrintResualt(testName, scenario, err); 
}

static void TestHeapSize10Inserts(void)
{
    int err = 0;
    char *testName = "TestHeapSize";
    char *scenario = "10Inserts";
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,IsLess);
    int data[] = {500,10,100,400,54,32,11,2,6,8};
    size_t size = ARR_LENGTH(data);
    size_t i;

    for(i = 0; i < size; ++i)
    {
        HeapInsert(heap, &data[i]);
    }

    if(HeapSize(heap) != size)
    {
        ++err;
    }

    HeapDestroy(&heap);
    VectorDestroy(&vector, NULL);

    PrintResualt(testName, scenario, err); 
}

static void TestHeapSize10InsertsExtract5(void)
{
    int err = 0;
    char *testName = "TestHeapSize";
    char *scenario = "10InsertsExtract5";
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,IsLess);
    int data[] = {500,10,100,400,54,32,11,2,6,8};
    size_t size = ARR_LENGTH(data);
    size_t i;

    for(i = 0; i < size; ++i)
    {
        HeapInsert(heap, &data[i]);
    }

    for(i = 0; i < size / 2; ++i)
    {
        if(HeapSize(heap) != size - i)
        {
            ++err;
        }
        HeapExtract(heap);
    }

    HeapDestroy(&heap);
    VectorDestroy(&vector, NULL);

    PrintResualt(testName, scenario, err); 
}

static void TestHeapForEachHeapNull(void)
{
    int err = 0;
    char *testName = "TestHeapForEach";
    char *scenario = "HeapNull";
    
    if(HeapForEach(NULL,PrintIntHeap,NULL) != 0)
    {
        ++err;
    }
    
    PrintResualt(testName, scenario, err); 
}

static void TestHeapForEachFanctionNull(void)
{
    int err = 0;
    char *testName = "TestHeapForEach";
    char *scenario = "FanctionNull";
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,IsLess);

    if(HeapForEach(heap,NULL,NULL) != 0)
    {
        ++err;
    }
    
    HeapDestroy(&heap);
    VectorDestroy(&vector, NULL);

    PrintResualt(testName, scenario, err); 
}

static void TestHeapForEachEmptyHeap(void)
{
    int err = 0;
    char *testName = "TestHeapForEach";
    char *scenario = "EmptyHeap";
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,IsLess);

    if(HeapForEach(heap,PrintIntHeap,NULL) != 0)
    {
        ++err;
    }
    
    HeapDestroy(&heap);
    VectorDestroy(&vector, NULL);

    PrintResualt(testName, scenario, err); 
}

static void TestHeapForEachPrintHeap(void)
{
    int err = 0;
    char *testName = "TestHeapForEach";
    char *scenario = "PrintHeap";
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,IsLess);
    int data[] = {500,10,100,400,54,32,11,2,6,8};
    size_t size = ARR_LENGTH(data);
    size_t i;
  
    for(i = 0; i < size; ++i)
    {
        HeapInsert(heap, &data[i]);
    }

    if(HeapForEach(heap,PrintIntHeap, NULL) != size)
    {
        ++err;
    }
    
    HeapDestroy(&heap);
    VectorDestroy(&vector, NULL);

    PrintResualt(testName, scenario, err); 
}

static void TestHeapSortUnsortedVector(void)
{
    int err = 0;
    char *testName = "TestHeapSort";
    char *scenario = "UnsortedVector";
    Vector *vector = VectorCreate(4, 4);
    int data[] = {500,10,100,400,54,32};
    size_t size = ARR_LENGTH(data);
    size_t i;

    for(i = 0; i < size; ++i)
    {
        VectorAppend(vector, &data[i]);
    }

    PrintVector(vector);
    HeapSort(vector, IsLess);
    PrintVector(vector);
    
    VectorDestroy(&vector, NULL);
    PrintResualt(testName, scenario, err); 
}

static void TestHeapSortSortedVector(void)
{
    int err = 0;
    char *testName = "TestHeapSort";
    char *scenario = "SortedVector";
    Vector *vector = VectorCreate(4, 4);
    int data[] = {1,2,3,4,5,6,7,8,9,10,20,50,80};
    size_t size = ARR_LENGTH(data);
    size_t i;

    for(i = 0; i < size; ++i)
    {
        VectorAppend(vector, &data[i]);
    }

    PrintVector(vector);
    HeapSort(vector,IsLess);
    PrintVector(vector);
   
    VectorDestroy(&vector, NULL);
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

static int	IsLess(const void *_left, const void *_right)
{
    return (*(int *)_left < *(int *)_right);
}

static int PrintIntHeap(const void* _element, void* _context)
{
    printf("%d,",*(int *)_element);
    return TRUE;
}

static int VectorForEachFunc(const void* _element, size_t _index, void* _context)
{
    ActionFunction toAction = *(ActionFunction *)_context;

    return toAction(_element, NULL);
}

static void PrintVector(Vector *_vec)
{
    size_t vectorSize = VectorSize(_vec);
    size_t i = 1;
    void *printData;

    for(; i< vectorSize +1; ++i)
    {
        VectorGet(_vec, i, &printData);
        printf("%d,",*(int *)printData);
    }

    putchar('\n');
}
