#include <stdlib.h> /* malloc , free */
#include "heap.h"

#define MAGIC_NUMBER 0XACACACAC
#define MAGIC_DESTROY 0xBEDC0FFE

#define PARENT(x)(x / 2)
#define LEFT_CHILED(x)((2 * x))
#define RIGHT_CHILED(x)((2 * x) + 1)
#define LEAF(x,HeapSize)((LEFT_CHILED(x) > HeapSize))

static void SwapDataInVector(Vector *_vector, size_t _i, size_t _j);
static void Heapify(Heap *_heap, size_t _index, size_t _heapSize);
static void BubbleUp(Heap *_heap, size_t _index);

struct Heap
{
    Vector *m_vec;
    size_t m_magicNumber;
    LessThanComparator m_lessFunc;
};

Heap* HeapBuild(Vector* _vector, LessThanComparator _pfLess)
{
    Heap *newHeap =  NULL;
    size_t heapSize;
    size_t fatherIndex;

    if(_vector == NULL || _pfLess == NULL)
    {
        return NULL;
    }

    newHeap = (Heap *)malloc(sizeof(Heap));

    if(newHeap == NULL)
    {
        return NULL;
    }

    newHeap->m_magicNumber = MAGIC_NUMBER;
    newHeap->m_vec = _vector;
    newHeap->m_lessFunc = _pfLess;

    heapSize = VectorSize(newHeap->m_vec);

    fatherIndex = PARENT(heapSize);

    for(;fatherIndex > 0; --fatherIndex)
    {
        Heapify(newHeap, fatherIndex, heapSize);
    }

    return newHeap;
}

Vector* HeapDestroy(Heap** _heap)
{
    Vector *toReturn = NULL;

    if(_heap != NULL && *_heap != NULL && (*_heap)->m_magicNumber == MAGIC_NUMBER)
    {
        (*_heap)->m_magicNumber = MAGIC_DESTROY;
        toReturn = (*_heap)->m_vec;
        free(*_heap);
        *_heap = NULL;
    }

    return toReturn;
}

HeapResult HeapInsert(Heap* _heap, void* _element)
{
    VectorResult appendResualt;

    if(_heap == NULL || _heap ->m_magicNumber != MAGIC_NUMBER || _element == NULL)
    {
        return HEAP_NOT_INITIALIZED;
    }

    appendResualt = VectorAppend(_heap->m_vec, _element);

    if(appendResualt == VECTOR_ALLOCATION_ERROR)
    {
        return HEAP_REALLOCATION_FAILED;
    }

    if(appendResualt == VECTOR_OVERFLOW)
    {
        return HEAP_OVERFLOW;
    }
    
    BubbleUp(_heap, HeapSize(_heap));

    return HEAP_SUCCESS;
}

const void* HeapPeek(const Heap* _heap)
{
    void *data;

    if(_heap == NULL || _heap->m_magicNumber != MAGIC_NUMBER 
    || HeapSize(_heap) == 0)
    {
        return NULL;
    }

    VectorGet(_heap->m_vec, 1, &data);

    return data;
}

void* HeapExtract(Heap* _heap)
{
    size_t heapSize;
    void *removedData;

    if(_heap == NULL || _heap->m_magicNumber != MAGIC_NUMBER)
    {
        return NULL;
    }

    heapSize = VectorSize(_heap->m_vec);

    if(heapSize == 0)
    {
        return NULL;
    }

    SwapDataInVector(_heap->m_vec, 1, heapSize);
    VectorRemove(_heap->m_vec, &removedData);
    Heapify(_heap, 1, --heapSize);

    return removedData;
}

size_t HeapSize(const Heap* _heap)
{
    if(_heap == NULL || _heap->m_magicNumber != MAGIC_NUMBER)
    {
        return 0;
    }

    return VectorSize(_heap->m_vec);
}

/* size_t HeapForEach(const Heap* _heap, ActionFunction _act, void* _context)
{
    if(_heap == NULL || _heap->m_magicNumber != MAGIC_NUMBER)
    {
        return 0;
    }

    return VectorForEach(_heap->m_vec,*(VectorElementAction *)_context, &_act);
} */

size_t HeapForEach(const Heap* _heap, ActionFunction _act, void* _context)
{
    size_t i = 1;
    void *element;

    if(_heap == NULL || _act == NULL || _heap->m_magicNumber != MAGIC_NUMBER)
    {
        return 0;
    }
    
    while (VECTOR_SUCCESS == VectorGet(_heap->m_vec, i++, &element))
    {
        if(_act(element,_context) == FALSE)
        {
            break;
        }		
    }		
    
    return i - 2;
}

void HeapSort(Vector* _vec, LessThanComparator _pfLess)
{
    Heap *heap = NULL;
    size_t heapSize;
    
    if(_vec != NULL && _pfLess != NULL)
    {
        heap = HeapBuild(_vec , _pfLess);
        if(heap == NULL)
        {
            return;
        }

        heapSize = VectorSize(heap->m_vec);

        while(heapSize > 0)
        {
            SwapDataInVector(_vec, 1 , heapSize);
            --heapSize;
            Heapify(heap, 1, heapSize);
        }

        HeapDestroy(&heap);
    }
}

/* --------------------- STATIC FUNCTION ---------------------*/
static void BubbleUp(Heap *_heap, size_t _index)
{
    void *childData;
    void *ParentData;
    
    if(_index == 1)
    {
        return;
    }

    VectorGet(_heap->m_vec, _index, &childData);
    VectorGet(_heap->m_vec, PARENT(_index), &ParentData);
        
    if(_heap->m_lessFunc(ParentData ,childData)) /* child > parent */
    {
        SwapDataInVector(_heap->m_vec, _index, PARENT(_index));
        BubbleUp(_heap, PARENT(_index));
    }
}

static void Heapify(Heap *_heap, size_t _index, size_t _heapSize)
{
    void *maxChiled = NULL;
    void *leftChiled = NULL;
    void *rightChiled = NULL;
    void *parent = NULL;
    size_t maxIndex = 0;

    /* from the younger father to root */
    if(LEAF(_index, _heapSize))
    {
        return;
    }
    
    VectorGet(_heap->m_vec, _index, &parent);
    VectorGet(_heap->m_vec, LEFT_CHILED(_index), &leftChiled);

    if(RIGHT_CHILED(_index) <= _heapSize)
    {
        VectorGet(_heap->m_vec, RIGHT_CHILED(_index), &rightChiled);
        if(_heap->m_lessFunc(leftChiled, rightChiled))
        {
            maxIndex = RIGHT_CHILED(_index);
            maxChiled = rightChiled;
        }
        else
        {
            maxIndex = LEFT_CHILED(_index);
            maxChiled = leftChiled;
        }
    }
    else
    {
        maxIndex = LEFT_CHILED(_index);
        maxChiled = leftChiled;
    }

    if(_heap->m_lessFunc(maxChiled , parent))
    {
        return;
    }
    
    SwapDataInVector(_heap->m_vec, maxIndex, _index);
    Heapify(_heap, maxIndex, _heapSize);
}

static void SwapDataInVector(Vector *_vector, size_t _i, size_t _j)
{
    void *saveDataI;
    void *saveDataJ;

    VectorGet(_vector, _i, &saveDataI);
    VectorGet(_vector, _j, &saveDataJ);

    VectorSet(_vector, _i, saveDataJ);
    VectorSet(_vector, _j, saveDataI);
}

