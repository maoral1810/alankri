#include <stdlib.h>     /*malloc, free */
#include "priorityQ.h"  /* PQ API */
#include "heap.h"

#define VECTOR_INITILIZE_SIZE 10
#define VECTOR_INCREAMENT_BLOCK_SIZE 10

struct PQ
{
    Heap *m_PQ;
    Vector *m_vec;
    CompereFunction IsPrior;
};

PQ *PQCreate(CompereFunction _isPrior)
{
    PQ *newPQueue =  NULL;
    
    if(NULL == _isPrior)
    {
        return NULL;
    }

    newPQueue = (PQ *)malloc(sizeof(PQ));
    
    if(newPQueue == NULL)
    {
        return NULL;
    }
    
    newPQueue->m_vec = VectorCreate(VECTOR_INITILIZE_SIZE, VECTOR_INCREAMENT_BLOCK_SIZE);
    if(newPQueue->m_vec == NULL)
    {
        free(newPQueue);
        return NULL;
    }

    newPQueue->m_PQ = HeapBuild(newPQueue->m_vec ,_isPrior);

    if(NULL == newPQueue->m_PQ)
    {
        VectorDestroy(&newPQueue->m_vec, NULL);
        free(newPQueue);
        return NULL;
    }

    return newPQueue;
}

void PQDestroy(PQ *_pQueue)
{
    if(_pQueue != NULL)
    {
        HeapDestroy(&_pQueue->m_PQ);
        VectorDestroy(&_pQueue->m_vec, NULL);
        free(_pQueue);
    }
}

pqErr PQEnquqe(PQ *_pQueue, void *_value)
{
    if(HEAP_SUCCESS != HeapInsert(_pQueue->m_PQ, _value))
    {
        return PQ_NOT_INITIALIZE;
    }

    return PQ_SUCSSES;
}

pqErr PQDequeue(PQ *_pQueue, void **_pValue)
{
    *_pValue = HeapExtract(_pQueue->m_PQ);
    if(NULL == *_pValue)
    {
        return PQ_UNDERFLOW;
    }

    return PQ_SUCSSES;
}

size_t PQSize(PQ *_pQueue)
{
    return HeapSize(_pQueue->m_PQ);
}