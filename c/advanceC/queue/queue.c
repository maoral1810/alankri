#include <stdlib.h> /* malloc, free */
#include "queue.h"

static int IsFullQueue(Queue *_queue);

static QueueResult QueueEnqueueCheckParam(Queue* _queue, void* _item);
static QueueResult QueueDequeueCheckParam(Queue* _queue, void** _pValue);
static QueueResult QueueForEachCheckParam(const Queue* _queue, 
                                          QueueElementAction _action);

struct Queue
{
    void **m_que;
    size_t m_size; /* sizeof queue */
    size_t m_head; /* head of the queue */
    size_t m_tail; /* the last place in queue */
    size_t nItems;
};

Queue* QueueCreate(size_t _maxSize)
{
    Queue *newQueue;
    
    if(_maxSize == 0)
    {
        return NULL;
    }

    newQueue = (Queue *)malloc(sizeof(Queue));

    if(newQueue == NULL)
    {
        return NULL;
    } 

    newQueue->m_que = (void **)malloc(sizeof(void *) *_maxSize);

    if(newQueue->m_que == NULL)
    {
        free(newQueue);
        return NULL;
    }

    newQueue->m_size = _maxSize;
    newQueue->m_head = 0;
    newQueue->m_tail = 0;
    newQueue->nItems = 0;
    
    /* calloc - what is nmem size????*/

    return newQueue;
}

void QueueDestroy(Queue** _queue, void (*_elementDestroy)(void* _item))
{
    size_t i;

    if(_queue != NULL)
    {
        if(_elementDestroy != NULL)
        {
            for(i = 0; i < (*_queue)->nItems; ++i)
            {
                _elementDestroy((*_queue)->m_que[i]);
            }
        }

        free((*_queue)->m_que);

        free(*_queue);
        *_queue = NULL;
    }
}

QueueResult QueueEnqueue(Queue* _queue, void* _item)
{
    QueueResult status = QueueEnqueueCheckParam(_queue, _item);

    if(status == QUEUE_SUCCESS)
    {
        if(IsFullQueue(_queue))
        {
            return QUEUE_OVERFLOW;
        }

        _queue->m_que[_queue->m_tail] = _item;
        _queue->m_tail = (_queue->m_tail + 1) % _queue->m_size;
        ++_queue->nItems;
    }

    return status;
}

QueueResult QueueDequeue(Queue* _queue, void** _pValue)
{
    QueueResult status = QueueDequeueCheckParam(_queue, _pValue);
    if(status == QUEUE_SUCCESS)
    {
        if(QueueIsEmpty(_queue))
        {
            return QUEUE_UNDERFLOW;
        }

        *_pValue = _queue->m_que[_queue->m_head];
        _queue->m_head = (_queue->m_head + 1) % _queue->m_size;
        --_queue->nItems;
    }

    return status;
}

int QueueIsEmpty(const Queue* _queue)
{
    if(_queue != NULL)
    {
        return (_queue->nItems == 0);
    }

    return TRUE;
}
size_t QueueForEach(const Queue* _queue, QueueElementAction _action, void* _context)
{
    size_t i = 0;
    size_t index;
    QueueResult status = QueueForEachCheckParam(_queue, _action);
    
    if(status == QUEUE_SUCCESS)
    {
        index = _queue->m_head;

        for(i = 0; i < _queue->nItems ; ++i)
        {
            if(_action(_queue->m_que[index], index , _context) == FALSE)
            {
                break;
            }
            
            index = (index + 1)	% _queue->m_size;	
        }		
    }
    return i;
}
/* ------------------- static functions ----------------------*/
static int IsFullQueue(Queue *_queue)
{
    return( _queue->m_head == _queue->m_tail && _queue->nItems != 0);
}

static QueueResult QueueEnqueueCheckParam(Queue* _queue, void* _item)
{
    if(_queue == NULL || _item == NULL)
    {
        return QUEUE_UNINITIALIZED_ERROR;
    }

    return QUEUE_SUCCESS;
}

static QueueResult QueueDequeueCheckParam(Queue* _queue, void** _pValue)
{
    if(_queue == NULL || _pValue == NULL)
    {
        return QUEUE_UNINITIALIZED_ERROR;
    }

    return QUEUE_SUCCESS;
}

static QueueResult QueueForEachCheckParam(const Queue* _queue, 
                                          QueueElementAction _action)
{
    if( _queue == NULL || _action == NULL)
    {
        return QUEUE_UNINITIALIZED_ERROR;
    }

    return QUEUE_SUCCESS;
}





