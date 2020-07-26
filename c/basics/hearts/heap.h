#ifndef __HEAP_H__
#define __HEAP_H__

#include "ADTDefs.h"
#include "vector.h" /* Vector Api */

#define TRUE 1
#define FALSE 0
typedef struct Heap Heap;

/*
    the function create a heap and return a pointer to heap
    intput:

    output:
        pointer to heap
    
    error:
        return NULL on failure     
*/
Heap *HeapBuild(Vector *_vec); /* O(n) */
/* 
    the function destroyed a heap

    input:
        heap - pointer to heap
    
    error:

*/
void HeapDestroy(Heap *_heap);
/*     
    the function Insert a data to heap

    input:
        heap - pointer to heap
        data - data to insert

    output:
        return status - ERR_OK on sucsses

    error:
        ERR_NOT_INITIALIZED - if heap is NULL 
        ERR_WRONG_INDEX    - if the index is not valid
*/
ADTErr HeapInsert(Heap *_heap, int _data);/* Olog(n) */
/*     
    the function return the max of the heap

    input:
        heap - pointer to heap
        data - pointer to return data 

    output:
        return status - ERR_OK on sucsses

    error:
        ERR_NOT_INITIALIZED - if heap or data are NULL 
*/
ADTErr HeapMax(Heap *_heap, int *_data);
/* 
    the function pop the max of the heap 

    input:
        heap - pointer to heap
        data - pointer to return data 

    output:
        return status - ERR_OK on sucsses

    error:
        ERR_NOT_INITIALIZED - if heap or data are NULL 
        ERR_UNDERFLOW - if heap is empty
*/
ADTErr HeapExtractMax(Heap *_heap, int *_data); /* Olog(n) */
/* 
    the function return the number of elements in heap

    input:
        heap - pointer to heap

    output:
        return status - ERR_OK on sucsses

    error:
        ERR_NOT_INITIALIZED - if heap is NULL 
*/
int HeapItemsNum(Heap *_heap);
/*     the function print the heap

    input:
        heap - pointer to heap

    output:

    error:
*/
void HeapPrint(Heap *_heap);


#endif /* __HEAP_H__ */