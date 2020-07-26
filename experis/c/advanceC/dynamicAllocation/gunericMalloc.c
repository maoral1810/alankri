#include <stddef.h> 	    /* size_t 			*/
#include <stdlib.h> 	    /* malloc , free 	*/
#include <stdio.h> 		    /* printf 			*/
#include "gunericMalloc.h" 	/* API myMalloc 	*/

#define MAGIC_NUMBER 0XACACACAC
#define MAGIC_DESTROY 0xBEDC0FFE

#define CHECK_POOL(x)(NULL != (x) && MAGIC_NUMBER == (((Mdata *)(x))->m_magicNumber))
/* ----------- structs ----------- */

typedef struct BufferMd BufferMd;

struct BufferMd
{
    size_t m_BufferSize;
	BufferMd *m_next;
	BufferMd *_m_prev;
};

struct Mdata
{
	size_t m_magicNumber;
    size_t m_poolSize;
    BufferMd *m_head;
};

/* -------------------- API Functions ---------------------------*/
void *CreatePool(size_t _poolSize)
{
    Mdata *pool;
	size_t actualSize;

	if(!_poolSize)
	{
		return NULL;
	}

	if(_poolSize < sizeof(void *))
	{
		_poolSize = sizeof(void *);
	}

	actualSize = _poolSize + sizeof(Mdata) + sizeof(BufferMd);
	pool = (Mdata *)malloc(actualSize);
	
	if(pool == NULL)
	{
		return NULL;
	}
	
	pool->m_poolSize = actualSize;
	pool->m_head = (BufferMd *)((char *)pool + sizeof(Mdata));
	pool->m_magicNumber = MAGIC_NUMBER;

	pool->m_head->m_BufferSize = actualSize - sizeof(Mdata) - sizeof(BufferMd);
	pool->m_head->m_next = NULL;
	pool->m_head->_m_prev = pool->m_head;
	
	return pool;
}

void DestroyPool(void *_pool)
{
	if(CHECK_POOL(_pool))
	{
		free(_pool);
	}
}

void *GunericMalloc(void *_pool, size_t _bufferSize)
{
	BufferMd *currentBuffer;
	BufferMd *newBuffer;
	size_t bufferOffSet;

	if(!CHECK_POOL(_pool) || !_bufferSize)
	{
		return NULL;
	}

	currentBuffer = ((Mdata *)_pool)->m_head;
	
	while(currentBuffer != NULL)
	{
		if(currentBuffer->m_BufferSize >= _bufferSize)
		{
			bufferOffSet = currentBuffer->m_BufferSize - _bufferSize;
			
			if(bufferOffSet >= sizeof(BufferMd))
			{
				/* create new buffer */
				newBuffer = (BufferMd *)((char *)currentBuffer + sizeof(BufferMd) + _bufferSize);
				newBuffer->m_BufferSize = bufferOffSet - sizeof(BufferMd);
				newBuffer->m_next = currentBuffer->m_next;
				newBuffer->_m_prev = currentBuffer->_m_prev;
				
				if(currentBuffer->m_next != NULL)
				{
					currentBuffer->m_next->_m_prev = newBuffer;
				}

				currentBuffer->_m_prev->m_next = newBuffer;
				((Mdata *)_pool)->m_head = newBuffer;
			}
			else /* currentBuffer->m_BufferSize == bufferSize */ 
			{
				if(currentBuffer->m_next != NULL)
				{
					currentBuffer->m_next->_m_prev = currentBuffer->_m_prev;
				}
				
				currentBuffer->_m_prev->m_next = currentBuffer->m_next;
				((Mdata *)_pool)->m_head = currentBuffer->m_next;
			}
			
			return (char *)currentBuffer + sizeof(size_t);
		}

		currentBuffer = currentBuffer->m_next;
	}

	return currentBuffer;
}

void MyFree(void *_buffer, void *_pool)
{
	BufferMd *toInsert;
	
	if(!CHECK_POOL(_pool) || _buffer == NULL)
	{
		return;
	}

	toInsert = (BufferMd *)_buffer - sizeof(size_t);

	if(((Mdata *)_pool)->m_head == NULL) /* empty list */
	{
		toInsert->m_next = NULL;
		toInsert->_m_prev = toInsert;
	}
	else
	{
		toInsert->m_next = ((Mdata *)_pool)->m_head->m_next;
		toInsert->_m_prev = ((Mdata *)_pool)->m_head;
	}
	
	((Mdata *)_pool)->m_head = toInsert;
}

