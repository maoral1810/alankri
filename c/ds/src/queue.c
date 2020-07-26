#include <stdlib.h> /* malloc, free */
#include "queue.h"

#define MAGIC_NUMBER 0xFAFA1989
#define TRUE 1
#define FALSE 0

static int IsFullQueue(Queue *_queue);

static ADTErr CheckParam(Queue *_queue);

struct Queue
{
    int * m_que;
    size_t m_size; /* sizeof queue */
    size_t m_head; /* head of the queue */
    size_t m_tail; /* the last place in queue */
    size_t nItems;
    size_t magicNumber; 
};

Queue *QueueCreate(size_t _size)
{
    Queue *queue = NULL;
    
    if(0 == _size)
    {
        return NULL;
    }

    queue = (Queue *)malloc(sizeof(Queue));
    
    if(NULL == queue)
    {
        return NULL;
    }

    queue->m_que = (int *)calloc(_size ,sizeof (int) * _size);
    if(NULL == queue->m_que)
    {
        free(queue);
        return NULL;
    }

/*     queue->m_head = 0;
    queue->m_tail = 0;
    queue->nItems = 0; */
    queue->m_size = _size;
    queue->magicNumber = MAGIC_NUMBER;

    return queue;
}

void QueueDestroy(Queue* _queue)
{
    if( ERR_OK == CheckParam(_queue))
    {
        _queue ->magicNumber = 0;

        free(_queue->m_que);
        _queue->m_que = NULL;

        free(_queue);
    }
}

ADTErr QueueInsert(Queue* _queue, int _item)
{
    if(ERR_OK == CheckParam(_queue))
    {
        if(IsFullQueue(_queue))
        {
            return ERR_OVERFLOW;
        }

        _queue->m_que[_queue->m_tail] = _item;
        _queue->m_tail = (_queue->m_tail + 1) % _queue->m_size;
        ++_queue->nItems;

        return ERR_OK;
    }

    return ERR_NOT_INITIALZED;
}

ADTErr QueueRemove(Queue* _queue, int* _item)
{
    if(ERR_OK == CheckParam(_queue))
    {
        if(QueueIsEmpty(_queue))
        {
            return ERR_UNDERFLOW;
        }

        *_item = _queue->m_que[_queue->m_head];
        _queue->m_head = (_queue->m_head + 1) % _queue->m_size;
        --_queue->nItems;
    }

    return ERR_OK;
}

int QueueIsEmpty(Queue* _queue)
{
    if(ERR_OK == CheckParam(_queue))
    {
        return (_queue->nItems == 0);
    }

    return TRUE;    
}

void QueuePrint(Queue* _queue)
{
    if(ERR_OK == CheckParam(_queue))
    {
        size_t index = _queue->m_head;
        size_t i = 0;

        for(;i < _queue->nItems ; index = (index + 1) % _queue->m_size, ++i)
        {
            printf("%d,",_queue->m_que[index]);
        }

        putchar('\n');
    }
}
/* ---------------------------- static functions --------------------------*/
static ADTErr CheckParam(Queue *_queue)
{
    if(NULL == _queue || MAGIC_NUMBER != _queue->magicNumber)
    {
        return ERR_NOT_INITIALZED;
    }

    return ERR_OK;
}

static int IsFullQueue(Queue *_queue)
{
    return ((_queue->nItems == _queue->m_size) ? TRUE : FALSE);
}