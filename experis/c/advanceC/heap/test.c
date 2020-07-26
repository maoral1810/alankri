#include <stdio.h>
#include <stdlib.h>
#include "mu_test.h"
#include "vector.h"
#include "heap.h"

#define ARR_LENGTH(x) (sizeof(x) / sizeof(x[0]))

static int	IsLess(const void *_left, const void *_right);
static int PrintIntHeap(const void* _element, void* _context);
static int VectorForEachFunc(const void* _element, size_t _index, void* _context);
static void PrintVector(Vector *_vec);

UNIT(TestBuildHeapFunctionNULL)
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,NULL);

    ASSERT_THAT(NULL != vector);
    ASSERT_THAT(NULL == heap);

    VectorDestroy(&vector, NULL);
END_UNIT

UNIT(TestBuildHeapVectorNull)
    Heap *heap = HeapBuild(NULL ,IsLess);

    ASSERT_THAT(NULL == heap);
END_UNIT

UNIT(TestBuildHeap)
    Vector *vector = VectorCreate(5,0);
    int data[] = {7,20,5,81,3,7};
    Heap *heap =  NULL;
    size_t i = 0;

    while(VECTOR_SUCCESS == VectorAppend(vector, &data[i++]));

    heap = HeapBuild(vector ,IsLess);

    ASSERT_THAT(NULL != heap);
    
    VectorDestroy(&vector, NULL);
    HeapDestroy(&heap);
END_UNIT

UNIT(TestHeapDestroyNULL)
    HeapDestroy(NULL);
END_UNIT

UNIT(TestHeapDestroyDoubleFree)
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,IsLess);

    HeapDestroy(&heap);
    HeapDestroy(&heap);

    VectorDestroy(&vector, NULL);
END_UNIT

UNIT(TestHeapInsertHeapNULL)
    int data = 5;

    ASSERT_THAT(HEAP_NOT_INITIALIZED == HeapInsert(NULL ,&data));
END_UNIT

UNIT(TestHeapInsertElementNULL)
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,IsLess);
    
    ASSERT_THAT(HEAP_NOT_INITIALIZED == HeapInsert(heap, NULL));
    HeapDestroy(&heap);
    VectorDestroy(&vector, NULL);
END_UNIT

UNIT(TestHeapInsertSameData)
    Vector *vector = VectorCreate(4,0);
    Heap *heap = HeapBuild(vector ,IsLess);
    int data[] = {55,55,10,10};
    size_t size = ARR_LENGTH(data);
    size_t i = 0;

    while (HEAP_SUCCESS == HeapInsert(heap, &data[i++]));

    ASSERT_THAT(!IsLess(HeapPeek(heap), &data[0]));

    HeapDestroy(&heap);
    VectorDestroy(&vector, NULL);

END_UNIT

UNIT(TestHeapInsertBigAfterSmall)
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,IsLess);
    int data[] = {5,10,100,40};
    size_t size = ARR_LENGTH(data);
    size_t i;
    void *printData;

    for(i = 0; i < size; ++i)
    {
        ASSERT_THAT(HEAP_SUCCESS == HeapInsert(heap, &data[i]));
    }
    
    for(i = 1; i < size + 1; ++i)
    {
        VectorGet(vector, i, &printData);
        printf("%d,",*(int *)printData);
    }
    putchar('\n');

    ASSERT_THAT(*(int *)HeapPeek(heap) == data[2]);

    HeapDestroy(&heap);
    VectorDestroy(&vector, NULL);
END_UNIT

UNIT(TestHeapInsertSmallAfterBig)
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,IsLess);
    int data[] = {500,10,100,400};
    size_t size = ARR_LENGTH(data);
    size_t i;

    for(i = 0; i < size; ++i)
    {
        ASSERT_THAT(HEAP_SUCCESS == HeapInsert(heap, &data[i]));
    }
    
    ASSERT_THAT(*(int *)HeapPeek(heap) == data[0]);

    HeapDestroy(&heap);
    VectorDestroy(&vector, NULL);
END_UNIT

UNIT(TestHeapPeak)
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,IsLess);
    int data[] = {500,10,100,400};
    size_t size = ARR_LENGTH(data);
    size_t i;
    void *extractData;

    for(i = 0; i < size; ++i)
    {
        ASSERT_THAT(HEAP_SUCCESS == HeapInsert(heap, &data[i]));
    }

    ASSERT_THAT(*(int *)HeapPeek(heap) == data[0]);

    extractData = HeapExtract(heap);
    ASSERT_THAT(*(int *)extractData == data[0]);
    ASSERT_THAT(*(int *)HeapPeek(heap) == data[3]);

    extractData = HeapExtract(heap);
    ASSERT_THAT(*(int *)HeapPeek(heap) == data[2]);

    HeapDestroy(&heap);
    VectorDestroy(&vector, NULL);
END_UNIT

UNIT(TestHeapPeakEmptyHeap)
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,IsLess);

    ASSERT_THAT(HeapPeek(heap) == NULL);

    HeapDestroy(&heap);
    VectorDestroy(&vector, NULL);
END_UNIT

UNIT(TestHeapPeakHeapNULL)
    ASSERT_THAT(HeapPeek(NULL) == NULL);
END_UNIT

UNIT(TestHeapExtractHeapNULL)
    ASSERT_THAT(HeapExtract(NULL) == NULL);
END_UNIT

UNIT(TestHeapExtractEmptyHeap)
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,IsLess);

    ASSERT_THAT(HeapExtract(NULL) == NULL);

    HeapDestroy(&heap);
    VectorDestroy(&vector, NULL);
END_UNIT

UNIT(TestHeapExtractOneData)
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,IsLess);
    int data = 7;

    HeapInsert(heap, &data);

    ASSERT_THAT(*(int *)HeapExtract(heap) == data);

    HeapDestroy(&heap);
    VectorDestroy(&vector, NULL);
END_UNIT


UNIT(TestHeapExtractMultiplyData)
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,IsLess);
    int data[] = {500,10,100,400};
    size_t size = ARR_LENGTH(data);
    size_t i;

    for(i = 0; i < size; ++i)
    {
        HeapInsert(heap, &data[i]);
    }

    ASSERT_THAT(*(int *)HeapExtract(heap) == data[0]);
    ASSERT_THAT(*(int *)HeapExtract(heap) == data[3]);
    ASSERT_THAT(*(int *)HeapExtract(heap) == data[2]);
    ASSERT_THAT(*(int *)HeapExtract(heap) == data[1]);

    HeapDestroy(&heap);
    VectorDestroy(&vector, NULL);
END_UNIT


UNIT(TestHeapSizeHeapNULL)
    ASSERT_THAT(HeapSize(NULL) == 0);
END_UNIT

UNIT(TestHeapSizeEmptyHeap)
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,IsLess);

    ASSERT_THAT(HeapSize(heap) == 0);

    HeapDestroy(&heap);
    VectorDestroy(&vector, NULL);

END_UNIT

 
UNIT(TestHeapSize10Inserts)
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,IsLess);
    int data[] = {500,10,100,400,54,32,11,2,6,8};
    size_t size = ARR_LENGTH(data);
    size_t i;

    for(i = 0; i < size; ++i)
    {
        HeapInsert(heap, &data[i]);
    }

    ASSERT_THAT(HeapSize(heap) == size);

    HeapDestroy(&heap);
    VectorDestroy(&vector, NULL);
END_UNIT

UNIT(TestHeapSize10InsertsExtract5)
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
        ASSERT_THAT(HeapSize(heap) == size - i);
        HeapExtract(heap);
    }

    HeapDestroy(&heap);
    VectorDestroy(&vector, NULL);
END_UNIT


UNIT(TestHeapForEachHeapNull)
    ASSERT_THAT(HeapForEach(NULL,PrintIntHeap,NULL) == 0);
END_UNIT

UNIT(TestHeapForEachFanctionNull)
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,IsLess);

    ASSERT_THAT(HeapForEach(heap,NULL,NULL) == 0);

    HeapDestroy(&heap);
    VectorDestroy(&vector, NULL);
END_UNIT

UNIT(TestHeapForEachPrintHeap)
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,IsLess);

    ASSERT_THAT(HeapForEach(heap,PrintIntHeap,NULL) == 0);
    
    HeapDestroy(&heap);
    VectorDestroy(&vector, NULL);
END_UNIT

UNIT(TestHeapForEachEmptyHeap)
    Vector *vector = VectorCreate(4, 4);
    Heap *heap = HeapBuild(vector ,IsLess);
    int data[] = {500,10,100,400,54,32,11,2,6,8};
    size_t size = ARR_LENGTH(data);
    size_t i;
  
    for(i = 0; i < size; ++i)
    {
        HeapInsert(heap, &data[i]);
    }
    ASSERT_THAT(HeapForEach(heap,PrintIntHeap, NULL) == size);
    
    HeapDestroy(&heap);
    VectorDestroy(&vector, NULL);
END_UNIT

UNIT(TestHeapSortUnsortedVector)
    Vector *vector = VectorCreate(4, 4);
    int data[] = {500,10,100,400,54,32};
    size_t size = ARR_LENGTH(data);
    size_t i;

    for(i = 0; i < size; ++i)
    {
        VectorAppend(vector, &data[i]);
    }
    putchar('\n');
    PrintVector(vector);
    HeapSort(vector, IsLess);
    PrintVector(vector);
    
    VectorDestroy(&vector, NULL);
END_UNIT

UNIT(TestHeapSortSortedVector)
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
END_UNIT

TEST_SUITE(heap)
	TEST(TestBuildHeapFunctionNULL)
	TEST(TestBuildHeapVectorNull)
	TEST(TestBuildHeap)
    TEST(TestHeapDestroyNULL)
    TEST(TestHeapDestroyDoubleFree)
    TEST(TestHeapInsertHeapNULL)
    TEST(TestHeapInsertElementNULL)
    TEST(TestHeapInsertSameData)
    TEST(TestHeapInsertBigAfterSmall)
    TEST(TestHeapInsertSmallAfterBig)
    TEST(TestHeapPeak)
    TEST(TestHeapPeakEmptyHeap)
    TEST(TestHeapPeakHeapNULL)
    TEST(TestHeapExtractHeapNULL)
    TEST(TestHeapExtractEmptyHeap)
    TEST(TestHeapExtractOneData)
    TEST(TestHeapExtractMultiplyData)
    TEST(TestHeapSizeHeapNULL)
    TEST(TestHeapSizeEmptyHeap)
    TEST(TestHeapSize10Inserts)
    TEST(TestHeapSize10InsertsExtract5)
    TEST(TestHeapForEachHeapNull)
    TEST(TestHeapForEachFanctionNull)
    TEST(TestHeapForEachEmptyHeap)
    TEST(TestHeapSortUnsortedVector)
    TEST(TestHeapSortSortedVector)
END_SUITE

/* ----------------- static functions --------------------------------*/
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