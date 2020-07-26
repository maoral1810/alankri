#ifndef __DUBLY_LINK_LIST_H__
#define __DUBLY_LINK_LIST_H__

#define TRUE 1
#define FALSE 0

#include <stddef.h> /* size_t */
#include "ADTDefs.h" /* erros */

typedef struct List List;
typedef struct Node Node;

List * ListCreate(void);
/* 
    the function create new list

    output
        pointer to the new empty list
    
    error
        if allocation failed return NULL
 */
void ListDestroy(List *_list);
/* 
    the function destroy list
   
    input:
        list - list (accses to head & tail) 

*/
ADTErr ListPushHead(List *_list, int _data);
/* 
    the function insert node to head and return the new head

    input:
        list - list (accses to head & tail) 
        data - the data to insert

    output:
        ERR_OK - on sucsess
        other ADTErr on failure

    error:
        ERR_NOT_INITIALZED - if the list is NULL
        ERR_ALLOCTAION_FAILED - if the node create failed
*/ 
ADTErr ListPushTail(List *_list, int _data);
/* 
    the function insert node to end of the list

    input:
        list - list (accses to head & tail) 
        data - the data to insert

    output:
        ERR_OK - on sucsess
        other ADTErr on failure

    error:
        ERR_NOT_INITIALZED - if the list is NULL
        ERR_ALLOCTAION_FAILED - if the node create failed
*/ 
ADTErr ListPopHead(List *_list, int *_data);
/* 
    the function remove node from head of the list

    input:
        list - list (accses to head & tail) 
        data - the data from the removed node

    output:
        ERR_OK - on sucsess
        other ADTErr on failure

    error:
        ERR_NOT_INITIALZED - if the list is NULL
        ERR_UNDERFLOW - if the list is empty
*/ 
ADTErr ListPopTail(List *_list, int *_data);
/* 
    the function remove node from the end of the list

    input:
        list - list (accses to head & tail) 
        data - the data from the removed node

    output:
        ERR_OK - on sucsess
        other ADTErr on failure

    error:
        ERR_NOT_INITIALZED - if the list is NULL
        ERR_UNDERFLOW - if the list is empty
*/ 
size_t ListCountItems(List *_list);
/* 
    the function count element in list

    input:
        list - list (accses to head & tail) 

    output:
        the number of nodes in the list

    error:
        if the list is empty or NULL return 0
*/ 
int ListIsEmpty(List *_list);
/* 
    the function check if the list is empty

    input:
        list - list (accses to head & tail) 

    output:
        TRUE  - if empty
        FALSE - if not empty

    error:
        if the list is NULL return TRUE
*/ 
void ListPrint(List *_list);
/* 
    the function print the list from head to the end of the list
    
    input:
        list - list (accses to head & tail) 
*/

#endif /*__DUBLY_LINK_LIST_H__*/