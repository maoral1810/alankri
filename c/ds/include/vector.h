#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stddef.h> /*size_t */
#include "ADTDefs.h"

typedef struct Vector Vector;

Vector * VectorCreate(size_t _initialSize, size_t _extensionBlockSize);
/*
    the function allocated Vector and return a pointer to Vector

    input:
        initialSize        - the size of array elements; 
        extensionBlockSize - block realloc factor;

    output:
        pointer to Vector

    error:
        return NULL if allocation failed or if both inputs are 0
*/
void VectorDestroy(Vector * _vector);
/*
    the function free Vector 

    input:
        vector - pointer to Vector; 
    
    output:
        pointer to Vector

    error:
*/
ADTErr VectorAdd (Vector *_vector, int _item);
/*
    the function add item to Vector 

    input:
        vector - pointer to Vector;
        item   - data to add;
    
    output: 
        ADTErr - errors status 

    error:
        ERR_NOT_INITIALZED    - if vector or the array are NULL;
        ERR_OVERFLOW          - if extra allocated is needed and blockSize = 0
        ERR_ALLOCTAION_FAILED - if allocation for extra space is failed
        ERR_OK                - on sucsses
*/

ADTErr VectorDelete(Vector *_vector, int *_item);
/*
    the function delete item from Vector 

    input:
        vector - pointer to Vector;
        item   - pointer for return delete data;
    
    output: 
        ADTErr - errors status 

    error:
        ERR_NOT_INITIALZED    - if vector or the array are NULL;
        ERR_UNDERFLOW         - if array is empty
        ERR_ALLOCTAION_FAILED - if allocation for reduction block is failed
        ERR_OK                - on sucsses
*/
ADTErr VectorGet(Vector *_vector, size_t _index, int *_item);
/*
    the function get item from Vector 

    input:
        vector - pointer to Vector
        item   - pointer for return data
        index  - the require index 
    
    output: 
        ADTErr - errors status 

    error:
        ERR_NOT_INITIALZED - if vector or the array are NULL;
        ERR_WRONG_INDEX    - if the index is not valid
        ERR_OK             - on sucsses
*/
ADTErr VectorSet(Vector *_vector, size_t _index, int _item);
/* 
    the function set item in Vector 

    input:
        vector - pointer to Vector
        item   - data to insert
        index  - the require index 
    
    output: 
        ADTErr - errors status 

    error:
        ERR_NOT_INITIALZED  - if vector or the array are NULL;
        ERR_WRONG_INDEX     - if the index is not valid
        ERR_OK              - on sucsses
 */
ADTErr VectorItemsNum(Vector *_vector, size_t *_numOfItems);
/* 
    the function set item in Vector 

    input:
        vector     - pointer to Vector
        numOfItems - returning data pointer
        
    output: 
        ADTErr - errors status 

    error:
        ERR_NOT_INITIALZED  - if vector or the array are NULL;
        ERR_OK              - on sucsses
*/

/* Unit Test functions */

void VectorPrint(Vector * _vector);
/*
    the function print all items in Vector 

    input:
        vector - pointer to Vector
        
    output: 

    error:

*/
#endif /*__VECTOR_H__ */
