#include "dublyLinkList.h"
#include <stddef.h>     /* size_t ,NULL*/
#include <stdlib.h>     /* malloc, free*/
#include <stdio.h>      /* printf */

#define MAGIC_NUMBER 0xFCFC

static Node *CreateNode(int _data);
static ADTErr CheckParam(List *_list, Node *_node, Node *_prev, Node *_next);
static ADTErr InsertNode(List *_list, Node *_toInsert,
                         Node *_PrevNode, Node *_NextNode);

struct Node
{
    int m_data;
    Node *m_next;
    Node *m_prev;
};

struct  List
{
    Node m_head;
    Node m_tail;
};


List *ListCreate(void)
{
    List *dlist = (List *)malloc(sizeof (List));
    
    if(NULL == dlist)
    {
        return NULL;
    }

    dlist->m_head.m_data = MAGIC_NUMBER;
    dlist->m_head.m_prev = NULL;
    dlist->m_head.m_next = &dlist->m_tail;
    
    dlist->m_tail.m_data = 0;
    dlist->m_tail.m_prev = &dlist->m_head;
    dlist->m_tail.m_next = NULL;

    return dlist;
}

void ListDestroy(List *_list)
{
    if(NULL != _list  && MAGIC_NUMBER == _list->m_head.m_data )
    {
        _list->m_head.m_data = 0;

        while (_list->m_head.m_next != &_list->m_tail)
        {
            Node *saveNext = _list->m_head.m_next;

            free(&_list->m_head);
            _list->m_head = *saveNext;
        }

        free(_list);
    }
}

ADTErr ListPushHead(List *_list, int _data)
{
    Node *node = NULL;
    
    if(NULL == _list)
    {
        return ERR_NOT_INITIALZED;
    }

    node = CreateNode(_data);
    
    if(NULL == node)
    {
        return ERR_ALLOCTAION_FAILED;
    }

    return InsertNode(_list, node, &_list->m_head, _list->m_head.m_next);
}

ADTErr ListPushTail(List *_list, int _data)
{
    Node *node = NULL;
    
    if(NULL == _list)
    {
        return ERR_NOT_INITIALZED;
    }

    node = CreateNode(_data);
    
    if(NULL == node)
    {
        return ERR_ALLOCTAION_FAILED;
    }

    return InsertNode(_list, node, _list->m_tail.m_prev, &_list->m_tail); 
}

ADTErr ListPopHead(List *_list, int *_data)
{
    if(NULL != _list && NULL != _data)
    {
        Node *saveNext = _list->m_head.m_next;
        
        if(ListIsEmpty(_list))
        {
            return ERR_UNDERFLOW;
        }

        *_data = _list->m_head.m_next->m_data;
        
        free(_list->m_head.m_next);

        _list->m_head = *saveNext;
        
        return ERR_OK;
    }

    return ERR_NOT_INITIALZED;
}

ADTErr ListPopTail(List *_list, int *_data)
{
    if(NULL != _list && NULL != _data)
    {
        Node *saveprev = _list->m_tail.m_prev;
                
        if(ListIsEmpty(_list))
        {
            return ERR_UNDERFLOW;
        }

        *_data = _list->m_tail.m_prev->m_data;
        
        free(_list->m_tail.m_prev);
                
        _list->m_tail = *saveprev;

        return ERR_OK;
    }

    return ERR_NOT_INITIALZED; 
}

size_t ListCountItems(List *_list)
{
    size_t counter = 0;

    if(NULL ==  _list)
    {
        return 0;
    }

    while(_list->m_head.m_next != &_list->m_tail)
    {
        _list->m_head = *_list->m_head.m_next;
        ++counter;
    }

    return counter;
}

int ListIsEmpty(List *_list)
{
    if(NULL != _list)
    {
        if(_list->m_head.m_next != &_list->m_tail && 
           _list->m_tail.m_prev != &_list->m_head)
        {
            return FALSE;
        }
    }

    return TRUE;
}

void ListPrint(List *_list)
{
    if(NULL != _list)
    {
        Node *saveHead = &_list->m_head;

        printf("[Head]->");

        while(_list->m_head.m_next != &_list->m_tail)
        {
            printf("[%d]->",_list->m_head.m_next->m_data);
            _list->m_head = *_list->m_head.m_next;
        }
        
        printf("[Tail]");
        putchar('\n');
        _list->m_head = *saveHead;
    }   
}
/* ------------------static function ------------------*/

static Node *CreateNode(int _data)
{
    Node *node = (Node *)malloc(sizeof(Node));

    if(NULL == node)
    {
        return NULL;
    }

    node->m_data = _data;
    node->m_next = NULL;
    node->m_prev = NULL;

    return node;
}

static ADTErr InsertNode(List *_list, Node *_toInsert, 
                         Node *_PrevNode, Node *_NextNode)
{
    ADTErr status = CheckParam(_list, _toInsert , _PrevNode, _NextNode);

    if(ERR_OK == status)
    {
        _toInsert ->m_prev = _PrevNode;
        _toInsert ->m_next = _NextNode;

        _PrevNode->m_next = _toInsert;
        _NextNode->m_prev = _toInsert;
    }

    return status;
}

static ADTErr CheckParam(List *_list, Node *_node, Node *_prev, Node *_next)
{
    if(NULL != _list  && NULL != _node && NULL != _prev && NULL != _next && 
       MAGIC_NUMBER == _list->m_head.m_data)
    {
        return ERR_OK;
    }

    return ERR_NOT_INITIALZED;
}