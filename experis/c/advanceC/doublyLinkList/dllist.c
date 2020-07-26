#include <stdlib.h> /* malloc , free */
#include <stdio.h>  /* putchar       */   
#include <assert.h> /* assert        */
#include "dllist.h"
#include "listfunctions.h"

#define MAGIC_NUMBER 0XACACACAC
#define MAGIC_DESTROY 0xBEDC0FFE

static Node g_wrongNode;
ListItr g_wrongIter = &g_wrongNode;

struct Node
{
    void *m_data;
    Node *m_next;
    Node *m_prev;
};

struct  List
{
    Node m_head;
    Node m_tail;
    size_t m_magicNumber;
};

static Node *CreateNode(void *_data);
static ListResult InsertNode(Node *_toInsert, Node *_PrevNode, Node *_NextNode);
static int ListIsEmpty(List *_list);
static void SwapData(ListItr _iter1, ListItr _iter2);

List* ListCreate(void)
{
    List *newDll = (List *)calloc(1, sizeof(List));
    
    if(NULL == newDll)
    {
        return NULL;
    }

    newDll->m_head.m_next = &newDll->m_tail;
    newDll->m_head.m_prev = &newDll->m_head;
    newDll->m_tail.m_prev = &newDll->m_head;
    newDll->m_tail.m_next = &newDll->m_tail;

    newDll->m_magicNumber = MAGIC_NUMBER;

    return newDll;
}

/* void ListDestroy(List** _pList, void (*_elementDestroy)(void* _item))
{
    Node *saveNext = NULL;
    Node *toFree = NULL;

    if(_pList != NULL && *_pList != NULL && MAGIC_NUMBER == (*_pList)->m_magicNumber)
    {
        (*_pList)->m_magicNumber = MAGIC_DESTROY;
        
        if(_elementDestroy != NULL)
        {
            toFree = (*_pList)->m_head.m_next;

            while(toFree != &(*_pList)->m_tail)
            {
                _elementDestroy((*_pList)->m_head.m_data);
                
                saveNext = toFree->m_next;
                free(toFree);
                toFree = saveNext;
            }
        }

        free(*_pList);
        *_pList = NULL;
    }
} */

void ListDestroy(List** _pList, void (*_elementDestroy)(void* _item))
{
	Node *temp;
	if (_pList == NULL || *_pList  == NULL || (*_pList) -> m_magicNumber != MAGIC_NUMBER)
	{
		return;
	}
	(*_pList) -> m_magicNumber = 0; 
	
	while( ((*_pList)->m_head.m_next) != &((*_pList)->m_tail))
	{
		temp = (*_pList) -> m_head.m_next;

		if (_elementDestroy != NULL)
		{
			_elementDestroy((*_pList) -> m_head.m_next -> m_data);
		}

		(*_pList)->m_head.m_next = temp->m_next;
		free(temp);
	}
	free(*_pList);
	*_pList = NULL;
	return;
}


ListResult ListPushHead(List* _list, void* _item)
{
    Node *node = NULL;
    
    if(NULL == _list  || MAGIC_NUMBER != _list->m_magicNumber)
    {
        return LIST_UNINITIALIZED_ERROR;
    }

    if(NULL == _item)
    {
        return LIST_NULL_ELEMENT_ERROR;
    }

    node = CreateNode(_item);
    
    if(NULL == node)
    {
        return LIST_ALLOCATION_ERROR;
    }

    return InsertNode(node, &_list->m_head, _list->m_head.m_next);
}

ListResult ListPushTail(List* _list, void* _item)
{
    Node *node = NULL;
    
    if(NULL == _list || MAGIC_NUMBER != _list->m_magicNumber)
    {
        return LIST_UNINITIALIZED_ERROR;
    }

    if(NULL == _item)
    {
        return LIST_NULL_ELEMENT_ERROR;
    }

    node = CreateNode(_item);
    
    if(NULL == node)
    {
        return LIST_ALLOCATION_ERROR;
    }

    return InsertNode(node, _list->m_tail.m_prev, &_list->m_tail); 
}

ListResult ListPopHead(List* _list, void** _pItem)
{
    Node *saveNext = NULL;
    Node *toPop = NULL;

    if(NULL == _list || MAGIC_NUMBER != _list->m_magicNumber || NULL == _pItem)
    {
        return LIST_UNINITIALIZED_ERROR;
    }
    
    if(ListIsEmpty(_list))
    {
        return LIST_UNDERFLOW;
    }

    toPop = _list->m_head.m_next;
    saveNext = toPop->m_next;
    
    *_pItem = toPop->m_data;
    free(toPop);
    
    _list->m_head = *(saveNext->m_prev);
    saveNext->m_prev = &_list->m_head;

    return LIST_SUCCESS;
}

ListResult ListPopTail(List* _list, void** _pItem)
{
    Node *savePrev = NULL;
    Node *toPop = NULL;

    if(NULL == _list || MAGIC_NUMBER != _list->m_magicNumber || NULL == _pItem)
    {
        return LIST_UNINITIALIZED_ERROR;
    }
    
    if(ListIsEmpty(_list))
    {
        return LIST_UNDERFLOW;
    }
    
    toPop = _list->m_tail.m_prev;        
    savePrev = toPop->m_prev;

    *_pItem = toPop->m_data;
    free(toPop);
    
    _list->m_tail = *(savePrev->m_next);
    savePrev->m_next = &_list->m_tail;

    return LIST_SUCCESS;
}

size_t ListSize(const List* _list)
{
    size_t counter = 0;
    Node *current;

    if(NULL != _list && MAGIC_NUMBER == _list->m_magicNumber)
    {
        current = _list->m_head.m_next;

        while(current != &_list->m_tail)
        {
            current = current->m_next;
            ++counter;
        }
    }

    return counter;
}

ListItr ListItrForEach(ListItr _begin, ListItr _end, 
                       ListActionFunction _action, void* _context)
{
    ListItr current = _begin;
    
    if(_action != NULL)
    {
        for(; !ListItrEquals(_end, current); current = ListItrNext(current))
        {
            if(FALSE == _action(ListItrGet(current), _context))
            {
                break;
            }
        }
    }

    putchar('\n');

    return current;
}

ListItr ListItrFindFirst(ListItr _begin, ListItr _end, 
                         PredicateFunction _predicate, void* _context)
{
    ListItr current = NULL;
    
    if(_predicate == NULL)
    {
        return _end;
    }

    for(current = _begin; !ListItrEquals(_end, current); current = ListItrNext(current))
    {
        if(_predicate(ListItrGet(current), _context))
        {
            break;
        }
    }
    
    return current;
}

void ListItrSort(ListItr _begin, ListItr _end, LessFunction _less)
{
    int notNeedSorting;
    Node *current = NULL;
    if(_less == NULL)
    {
        return;
    }
    
    while(!ListItrEquals(_end, _begin))
    {
        notNeedSorting = 1;
        _end = ListItrPrev(_end);
        
        for(current = _begin; !ListItrEquals(current, _end); current = ListItrNext(current))
        {
            if(_less(ListItrGet(current), ListItrGet(ListItrNext(current))))
            {
                SwapData(current, ListItrNext(current));
                notNeedSorting = 0;
            }
        }

        if(notNeedSorting)
        {
            break;
        }
    }
}

List* ListItrCut(ListItr _begin, ListItr _end)/* TODO*/
{
    List *newList = NULL; 

    if(newList == NULL || _begin == g_wrongIter || _end == g_wrongIter)
    {
        ListDestroy(&newList, NULL);
        return NULL;
    }

    _begin->m_prev->m_next = _end->m_next;
    _end->m_next->m_prev = _begin->m_prev;

    newList->m_head.m_next = _begin;
    newList->m_tail.m_prev = _end;

    return newList;
}

ListItr ListItrSplice(ListItr _dest, ListItr _begin, ListItr _end)/* TODO*/
{
    /* ListItr next;
    ListItr first = _dest;

    while(!ListItrEquals(_begin , _end))
    {
        next = ListItrNext(_begin);
        ListItrInsertBefore(_dest, ListItrRemove(_begin));
        first = ListItrPrev(first);
        _begin = next;
        return first;
    } */
    
    
    _begin->m_prev->m_next = _end->m_next;
    _end->m_next->m_prev = _begin->m_prev;

    _begin->m_prev = _dest->m_prev;
    _end->m_next = _dest;
    _dest->m_prev->m_next = _begin;
    _dest->m_prev = _end;

    return _dest;
    
}
/*------------------------ iterator function ------------------------------*/
ListItr ListItrBegin(const List* _list)
{
    if(_list != NULL && _list->m_magicNumber == MAGIC_NUMBER)
    {
        return (_list->m_head.m_next);
    }
    
    return g_wrongIter;
}

ListItr ListItrEnd(const List* _list)
{
    if(_list != NULL && _list->m_magicNumber == MAGIC_NUMBER)
    {
        return &((List *)_list)->m_tail;
    }

    return g_wrongIter;
}

int ListItrEquals(const ListItr _a, const ListItr _b)
{
    if(_a != g_wrongIter && _b != g_wrongIter)
    {
        return (_a == _b);
    }

    return FALSE;
}

ListItr ListItrNext(ListItr _itr)
{
    if(_itr == g_wrongIter)
    {
        return g_wrongIter;
    }

    return _itr->m_next;
}

ListItr ListItrPrev(ListItr _itr)
{
    if(_itr == g_wrongIter)
    {
        return g_wrongIter;
    }
    
    return _itr->m_prev->m_prev->m_next;
}

void* ListItrGet(ListItr _itr)
{
    if(_itr == g_wrongIter)
    {
        return g_wrongIter->m_data;
    }
    
    return _itr->m_data;
}

void* ListItrSet(ListItr _itr, void* _element)
{
    Node *node = _itr;
    void *saveData;
    
    if(_itr == g_wrongIter)
    {
        return _itr;
    }

    saveData = node->m_data;
    node->m_data = _element;

    return saveData;
}

ListItr ListItrInsertBefore(ListItr _itr, void* _element)
{
    Node *nextNode;
    Node *prevNode;
    Node *newNode;

    assert(_element);
    if(NULL == _itr || ListItrEquals(_itr, ListItrNext(_itr)))
    {
        return NULL;
    }

    newNode = CreateNode(_element);
    if(newNode == NULL)
    {
        return NULL;
    }

    nextNode = _itr;
    prevNode = nextNode->m_prev;

    prevNode->m_next = newNode;
    nextNode->m_prev = newNode;

    _itr = newNode;

    return _itr; 
}

void* ListItrRemove(ListItr _itr)
{
    void *data = NULL;
    Node *nodeToRemove = NULL;
    
    if(g_wrongIter == _itr)
    {
        return NULL;
    }

    data = ListItrGet(_itr);
    nodeToRemove = _itr;

    nodeToRemove->m_next->m_prev = nodeToRemove->m_prev;
    nodeToRemove->m_prev->m_next = nodeToRemove->m_next;

    free(nodeToRemove);

    return data;
}

/*------------------------ static functions --------------------------*/
static Node *CreateNode(void *_data)
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

static ListResult InsertNode(Node *_toInsert, Node *_PrevNode, Node *_NextNode)
{
    assert(_toInsert);
    assert(_NextNode);
    assert(_PrevNode);
    
    _toInsert ->m_prev = _PrevNode;
    _toInsert ->m_next = _NextNode;

    _PrevNode->m_next = _toInsert;
    _NextNode->m_prev = _toInsert;

    return LIST_SUCCESS;
}

static int ListIsEmpty(List *_list)
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

static void SwapData(ListItr _iter1, ListItr _iter2)
{
    void *saveData = ListItrGet(_iter1);
    ListItrSet(_iter1, ListItrGet(_iter2));
    ListItrSet(_iter2, saveData);
}
