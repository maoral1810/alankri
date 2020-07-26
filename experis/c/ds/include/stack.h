#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h>  /* size_t */
#include "ADTDefs.h" /* errors */

typedef struct Stack Stack;

Stack *StackCreate(size_t _size, size_t _blockSize);
/*
    the function allocated Stack and return a pointer to Stack

    input:
        initialSize        - the size of array elements; 
        extensionBlockSize - block realloc factor;

    output:
        pointer to Stack

    error:
        return NULL if allocation failed or if both inputs are 0
*/
void StackDestroy(Stack *_stack);
/*
    the function free Stack 

    input:
        Stack - pointer to Stack; 
    
    output:
        pointer to Stack

    error:
*/
ADTErr StackPush(Stack *_stack, int _item);

/*
    the function push item to top of the Stack 

    input:
        Stack - pointer to Stack;
        item   - data to push;
    
    output: 
        ADTErr - errors status 

    error:
        ERR_NOT_INITIALZED    - if Stack or the array are NULL;
        ERR_OVERFLOW          - if extra allocated is needed and blockSize = 0
        ERR_ALLOCTAION_FAILED - if allocation for extra space is failed
        ERR_OK                - on sucsses
*/
ADTErr StackPop(Stack *_stack, int * _item);
/*
    the function pop item from top of the Stack 

    input:
        Stack - pointer to Stack;
        item   - pointer for return pop data;
    
    output: 
        ADTErr - errors status 

    error:
        ERR_NOT_INITIALZED    - if Stack or the array are NULL;
        ERR_UNDERFLOW         - if array is empty
        ERR_OK                - on sucsses
*/
ADTErr StackTop(Stack *_stack, int * _item);
/*
    the function get item from top of the Stack 

    input:
        Stack - pointer to Stack
        item   - pointer for return data
    
    output: 
        ADTErr - errors status 

    error:
        ERR_NOT_INITIALZED - if Stack or the array are NULL;
        ERR_OK             - on sucsses
*/
int StackIsEmpty(Stack *_stack);
/* 
    the function return if the stack is empty 

    input:
        stack - pointer to stack
        
    output: 
       return:
            TRUE on sucsses
            FALSE on failure or NULL

    error:
        ERR_NOT_INITIALZED  - if stack or the array are NULL;
        ERR_OK              - on sucsses
*/
/* Unit-Test Functions */

void StackPrint(Stack *_stack);
/*
    the function print all items in Stack 

    input:
        stack - pointer to Stack
        
    output: 

    error:

*/
#endif /*__STACK_H__*/