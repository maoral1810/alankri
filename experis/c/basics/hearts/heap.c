#include <stdlib.h> /* malloc, free */
#include "heap.h" /* API functions */

#define PARENT(x)((x - 1) / 2)
#define LEFT_CHILED(x)((2 * x) + 1)
#define RIGHT_CHILED(x)((2 * x) + 2)
#define MAX_CHILD(a,b)( (a > b) ? a : b)
#define MAX_DATA(a,b)( (a > b ) ? 1 : 0)
#define LEAF(x,HeapSize)( (LEFT_CHILED(x) > HeapSize) && (RIGHT_CHILED(x) > HeapSize) )
#define MAGIC_NUMBER 0XDEADBEEF

static void BubbleUp(Heap *_heap, size_t _index);
static void Heapify(Heap *_heap, size_t _index);
static void SwapData(Vector *_vector,size_t _x, size_t _y);

struct Heap
{
    Vector *m_vec;
    size_t m_heapSize;
    size_t m_magicNumber;
};

Heap *HeapBuild(Vector *_vec)
{
    Heap *heap = NULL;
    size_t heapSize = 0;
    size_t fatherIndex = 0;
  
    if(NULL == _vec)
    {
        return NULL;
    }

    heap = (Heap *)malloc(sizeof(Heap));

    if(NULL == heap)
    {
        return NULL;
    }

    heap->m_vec =_vec;
    VectorItemsNum(heap->m_vec, &heapSize);
    heap->m_heapSize = heapSize;
    heap->m_magicNumber = MAGIC_NUMBER;

    fatherIndex = PARENT(heapSize);
    for(;fatherIndex > - 1; --fatherIndex)
    {
        Heapify(heap, fatherIndex);
    }
    return heap;
}

void HeapDestroy(Heap *_heap)
{
    if(NULL !=_heap)
    {
        _heap->m_magicNumber = 0;
        free(_heap);
    }
}

ADTErr HeapInsert(Heap *_heap, int _data)
{
    ADTErr status = ERR_OK;
    
    if(NULL == _heap)
    {
        return ERR_NOT_INITIALZED;
    }

    status = VectorAdd(_heap->m_vec, _data);
    ++_heap->m_heapSize;

    BubbleUp(_heap, (_heap->m_heapSize - 1));
    return status;
}

ADTErr HeapMax(Heap *_heap, int *_data)
{
    if(NULL == _heap || NULL == _data)
    {
        return ERR_NOT_INITIALZED;
    }
    
    return VectorGet(_heap->m_vec, 0, _data);
}

ADTErr HeapExtractMax(Heap *_heap, int *_data)
{
    ADTErr status = ERR_OK;
    int saveLast = 0;

    if(NULL == _heap || NULL == _data)
    {
        return ERR_NOT_INITIALZED;
    }

    if(0 == _heap->m_heapSize)
    {
        return ERR_UNDERFLOW;
    }

    VectorDelete(_heap->m_vec, _data);
    --_heap->m_heapSize;
    
    if(0 == _heap->m_heapSize) 
    {
        return status;
    }
    /* data now restore the last element in heap */
    saveLast = *_data;
    VectorGet(_heap->m_vec, 0, _data);
    VectorSet(_heap->m_vec, 0, saveLast);
    Heapify(_heap, 0);

    return status;
}

int HeapItemsNum(Heap *_heap)
{
    if(NULL == _heap)
    {
        return -1;
    }

    return (_heap->m_heapSize);
}

void HeapPrint(Heap *_heap)
{
    if(NULL != _heap)
    {
        VectorPrint(_heap->m_vec);
    }
}

/* --------------------------- static functions ---------------------------*/
static void Heapify(Heap *_heap, size_t _index)
{
    int maxChiled = 0;
    int leftChiled = 0;
    int rightChiled = 0;
    int parent = 0;
    size_t swapIndex = 0;

    /* from the younger father to root */
    if(LEAF(_index, _heap->m_heapSize))
    {
        return;
    }
    
    VectorGet(_heap->m_vec, _index, &parent);
    if(RIGHT_CHILED(_index) < _heap->m_heapSize)
    {
        VectorGet(_heap->m_vec, RIGHT_CHILED(_index), &rightChiled);
    }

    VectorGet(_heap->m_vec, LEFT_CHILED(_index), &leftChiled);

    maxChiled = MAX_CHILD(leftChiled, rightChiled);

    if(parent > maxChiled)
    {
        return;
    }

    swapIndex = (maxChiled == leftChiled) ? LEFT_CHILED(_index) : 
                                            RIGHT_CHILED(_index);
    SwapData(_heap->m_vec, swapIndex, _index);
    Heapify(_heap, swapIndex);
}

static void BubbleUp(Heap *_heap, size_t _index)
{
    int childData;
    int ParentData;
    
    if(_index == 0)
    {
        return;
    }

    VectorGet(_heap->m_vec, _index, &childData);
    VectorGet(_heap->m_vec, PARENT(_index), &ParentData);
        
    if(MAX_DATA(childData, ParentData)) /* child > parent */
    {
        SwapData(_heap->m_vec, _index, PARENT(_index));
        BubbleUp(_heap, PARENT(_index));
    }
}

static void SwapData(Vector *_vector,size_t _x, size_t _y)
{
    int saveX = 0;
    int saveY = 0; 
    
    VectorGet(_vector, _x, &saveX);
    VectorGet(_vector, _y, &saveY);

    VectorSet(_vector, _y, saveX);
    VectorSet(_vector, _x, saveY);
}