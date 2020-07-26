/* Programer : Maor Alankri
   Last update: 13.11.19 
   Cyclic queue
*/

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h>  /*size_t */
#include "ADTDefs.h" /* errors */

typedef struct Queue Queue;


Queue *QueueCreate(size_t _size);
/* 
    the function allocated Queue and return a pointer to Queue

    input:
        size        - the size of queue 

    output:
        pointer to Queue

    error:
        return NULL if allocation failed or if size = 0
*/
void QueueDestroy(Queue* _queue);
/*
    the function free Queue 

    input:
        Queue - pointer to Queue; 
    
    output:
        pointer to Queue

    error:
*/
ADTErr QueueInsert(Queue* _queue, int _item);
/*
    the function insert item to last place in Queue 

    input:
        Queue - pointer to Queue;
        item   - data to insert;
    
    output: 
        ADTErr - errors status 

    error:
        ERR_NOT_INITIALZED    - if Queue or the array are NULL;
        ERR_OVERFLOW          - if no place to insert(full queue)
        ERR_OK                - on sucsses
*/
ADTErr QueueRemove(Queue* _queue, int* _item);
/*
    the function remove the first item in queue  

    input:
        Queue - pointer to queue;
        item   - pointer for return data;
    
    output: 
        ADTErr - errors status 

    error:
        ERR_NOT_INITIALZED    - if queue or the array are NULL;
        ERR_UNDERFLOW         - if queue is empty
        ERR_OK                - on sucsses
*/
int QueueIsEmpty(Queue* _queue);
/* 
    the function return if the queue is empty 

    input:
        queue - pointer to Queue
        
    output: 
       return:
            TRUE on sucsses
            FALSE on failure or NULL

    error:
        ERR_NOT_INITIALZED  - if queue or the array are NULL;
        ERR_OK              - on sucsses
*/
void QueuePrint(Queue* _queue);
/*
    the function print all items in queue 

    input:
        queue - pointer to Queue
*/
#endif /*__QUEUE_H__*/
