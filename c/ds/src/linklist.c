#include <stddef.h> /* NULL */
#include <stdio.h> /* printf */
#include "linklist.h"
#include "ADTDefs.h"
#include "colors.h" /* colors for printf */

/* static ADTErr InsertNode(Person *_prevNode, Person *_node); */

Person *ListInsertHead(Person *_head, Person *_p)
{
    if(_p != NULL)
    {
       _p->m_next = _head;
    
       return _p; 
    }

    return _head; 
}

Person *ListRemoveHead(Person * _head, Person **_item)
{
    if( NULL != _item)
    {
        *_item = _head;
    }

    return (_head != NULL && _item != NULL) ? _head->m_next : _head;
}

Person *ListInsertByKey(Person *_head, int _key, Person *_p)
{
    /* insert by m_id */
    Person *runner = _head;
    Person *PrevNode = _head;

    if(_p == NULL) /*  not initilize node */
    {
        return _head;
    }
    
    if(_head == NULL) /* empty list */
    {
        _p->m_next = NULL;
        return _p; 
    }

    while(runner != NULL)
    {
        if(_key > runner->m_id)
		{
            PrevNode = runner;
            runner = runner->m_next;
		}
        else if(_key == runner->m_id)
		{
			return _head;
		}
		else if(_key < runner->m_id) 						
		{
		    if(PrevNode == _head)
		    {
		        _p->m_next = _head;
		        return _p;
		    }
		    else
		    {
			    PrevNode->m_next = _p;
			    _p->m_next = runner;
			}
			
            return _head;
		}
	}
	
    PrevNode->m_next = _p;
	return _head;
}

Person *ListInsertByKeyRec(Person *_head,int _key , Person *_p)
{
	if(NULL == _p)
	{
		return _head;
	}

	else if(NULL == _head || _key < _head-> m_id)
	{
		_p->m_next = _head;
		return _p;
	}

    else if(_key == _head->m_id)
	{
		return _head;
	}

	else
	{
		return ListInsertByKeyRec(_head->m_next, _key, _p);
	}
}

Person *ListRemoveByKey(Person * _head, int _key, Person **_p)
{
    Person *runner = _head;
    Person *PrevNode = _head;

    if(NULL  == _head && NULL == _p)
    {
        return _head;
    }

    while(NULL != runner && _key > runner->m_id)
    {
        if(_key == runner->m_id)
        {
            PrevNode->m_next = runner->m_next;
            *_p = runner;
            
            return _head;
        }
        
        else 
        {
            PrevNode = runner;
            runner = runner->m_next;
        }
    }
    
    return _head;
}

Person *ListRemoveByKeyRec(Person *_head, int _key, Person **_p)
{
	if(NULL == _p)
    {
        return _head;
    }
    
    if(NULL == _head)
	{
		*_p = NULL;
		return *_p;
	}

	if(_key == _head->m_id)
	{
		*_p = _head;

		return _head->m_next;
	}

	return ListRemoveByKeyRec(_head->m_next, _key, _p);
}
void PrintList(Person *_head)
{
    int i = 1;

    for(;_head != NULL; ++i, _head = _head->m_next)
    {
        printf(BOLDYELLOW"\nperson_%d:"CYAN"\nid:%-4d name:%-7s age:%-4d \n"RESET,
              i, _head->m_id, _head->m_name, _head->m_age);
    }
}

