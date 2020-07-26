#ifndef __LINK_LIST_H__
#define __LINK_LIST_H__

/*  singly link list:

    programer: Maor Alankri 
    create date:    14/11/19
    last modify:    17/11/19
*/
typedef struct Person Person;

struct Person
{
    int m_id; /* primary Key */
    char m_name[128];
    int m_age;
    Person *m_next;
};

Person *ListInsertHead(Person *_head, Person *_p);
/* 
    the function insert node to head and return the new head

    input:
        head - the head of the list 
        p - the node to insert

    output:
        pointer to new head

    error:
        if the node is NULL return head
*/
Person *ListRemoveHead(Person * _head, Person **_item);
/* 
    1) the function remove node from the head of the list
    2) return his values in item 

    input:
        head - the head of the list 
        item - the return value of the removed node

    output:
        pointer to new head

    error:
        if item or head is NULL return head, item = NULL
*/
Person *ListInsertByKey(Person *_head, int _key, Person *_p);
/* 
    1) the function insert node to list by key( from low to high)
    2) return the new head

    input:
        head - the head of the list 
        p - the node to insert
        key - the insertion factor 

    output:
        pointer to new head

    error:
        if the node is NULL return head
        if the key allreday in the list the function dont add him and return head 
*/
Person *ListInsertByKeyRec(Person *_head, int key, Person *_p);
/* 
    1) the function insert node to list by key(from low to high)
    2) return the new head
    3) the function is recursive

    input:
        head - the head of the list 
        p - the node to insert
        key - the insertion factor 

    output:
        pointer to new head

    error:
        if the node is NULL return head
        if the key allreday in the list the function dont add this new node 
*/
Person *ListRemoveByKey(Person * _head, int _key, Person **_p);
/* 
    1) the funcion search by key value for node in the list 
    2) the function remove the node 
    3) return his values in item 

    input:
        head - the head of the list 
        item - the return value of the removed node
        key - the value to search  

    output:
        pointer to new head

    error:
        if item or head is NULL return head
        if the key dont show in list return head, *person = NULL
*/
Person *ListRemoveByKeyRec(Person * _head, int _key, Person **_p);
/* 
    1) the funcion search by key value for node in the list 
    2) the function remove the node 
    3) return his values in item 
    4) the function is recursive
    
    input:
        head - the head of the list 
        item - the return value of the removed node
        key - the value to search  

    output:
        pointer to new head

    error:
        if item or head is NULL return head
        if the key dont show in list return head, *person = NULL
*/
void PrintList(Person *_head);
/* 
    the function print the list from head to the end of the list
        
    input:
        head - the head of the list 
*/
#endif /*__LINK_LIST_H__*/