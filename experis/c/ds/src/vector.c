#include <stddef.h> /* size_t       */
#include <stdlib.h> /* malloc, free */
#include <stdio.h>  /* printf       */
#include "vector.h"

#define MAGIC_NUMBER 0xFAFAFAFA
#define RESIZE_FACTOR 2

static ADTErr CheckVectorInitialize(Vector *_vector);
static ADTErr CheckIndex(Vector *_vector, size_t _index);
static ADTErr AllocNewMemory(Vector *_vector);
static ADTErr ReductionVector(Vector *_vector);

struct Vector
{
    int *m_items;
    size_t m_originalSize;      /* original allcated space for items           */
    size_t m_size;              /* actual allocated space for item             */
    size_t m_nItems;            /* actual number of items                      */
    size_t m_blockSize;         /* the chunk size to be allocated when no space*/
    unsigned int magicNumber;   /* magic number for avoid double free          */ 
};

Vector * VectorCreate(size_t _initialSize, size_t _extensionBlockSize)
{
    Vector *vector = NULL;
    int *m_items = NULL;

    if(0 == _initialSize && 0 == _extensionBlockSize)
    {
        return NULL;
    }

    vector = (Vector *)malloc(sizeof(Vector));

    if( NULL == vector)
    {
        return NULL;
    }

    m_items = (int *)malloc(sizeof(int) * _initialSize);

    if(NULL == m_items)
    {
        free(vector);
        vector = NULL;
        return NULL;
    }

    vector ->m_items = m_items;
    vector->m_nItems = 0;
    vector->m_originalSize = _initialSize;
    vector->m_size =  _initialSize;
    vector->m_blockSize = _extensionBlockSize;
    vector->magicNumber = MAGIC_NUMBER;

    return vector;
}

void VectorDestroy(Vector * _vector)
{
    if(NULL != _vector && MAGIC_NUMBER == _vector->magicNumber)
    {
        _vector->magicNumber = 0;

        if (NULL != _vector->m_items) /* check if the arr not NULL */
        {
            free(_vector->m_items);
            _vector->m_items = NULL;
        }

        free(_vector);
    }
}

ADTErr VectorAdd (Vector *_vector, int _item)
{
    ADTErr err_status = CheckVectorInitialize(_vector);

    if(ERR_OK == err_status)
    {
        if(_vector->m_nItems == _vector->m_size)
        {
            err_status = AllocNewMemory(_vector);
        }

        if(ERR_OK == err_status)
        {
            _vector->m_items[_vector->m_nItems] = _item;
            ++_vector->m_nItems; /* increment NumberOfElements By 1 */
        }
    }
    
    return err_status;
}

ADTErr VectorDelete(Vector *_vector, int *_item)
{
    ADTErr err_status = CheckVectorInitialize(_vector);

    /* check if Vector and item inisilize before delete*/
    if(ERR_OK == err_status && NULL != _item)
    {
        size_t FreeSpace = 0;

        if(0 == _vector->m_nItems)
        {
            return ERR_UNDERFLOW;
        }

        /* delete item */
        *_item = _vector->m_items[_vector->m_nItems - 1];
        --_vector->m_nItems;
        
        /* calculate if realloc is require (reduction Vector) */
        FreeSpace = _vector->m_size - _vector->m_nItems; 
        
        if((_vector->m_size != _vector->m_originalSize) && 
           FreeSpace > (RESIZE_FACTOR * _vector->m_blockSize))
        {
            err_status = ReductionVector(_vector);
        }
    }

    return err_status; 
} 

ADTErr VectorGet(Vector *_vector, size_t _index, int *_item)
{
    ADTErr err_status = CheckVectorInitialize(_vector);
    
    if(ERR_OK == err_status)
    {
        if (ERR_OK == (err_status = CheckIndex(_vector, _index)))
        {
            *_item = _vector->m_items[_index];
        }
    }

    return err_status;
}

ADTErr VectorSet(Vector *_vector, size_t _index, int _item)
{
    ADTErr err_status = CheckVectorInitialize(_vector);

    /* check if Vector inisilize before checking index*/
    if(ERR_OK == err_status) 
    {
        /* check if index is valid */
        if(ERR_OK == (err_status = CheckIndex(_vector, _index)))
        {
           _vector->m_items[_index] = _item;
        }
    }

    return err_status;
}
ADTErr VectorItemsNum(Vector *_vector, size_t *_numOfItems)
{
    if(ERR_OK == CheckVectorInitialize(_vector)  && _numOfItems != NULL)
    {
        *_numOfItems = _vector->m_nItems;
        return ERR_OK;
    }

    return ERR_NOT_INITIALZED; 
}

void VectorPrint(Vector * _vector)
{
    if(ERR_OK == CheckVectorInitialize(_vector))
    {
        size_t i = 0;

        for(; i < _vector->m_nItems; ++i)
        {
            printf("%d,",_vector->m_items[i]);
        }

        putchar('\n');
    }
}

/* ----------------- static functions --------------------------*/  
static ADTErr AllocNewMemory(Vector *_vector)
{
    int *save_arr = _vector->m_items;

    if(0 == _vector->m_blockSize)
    {
        return ERR_OVERFLOW;
    }
    
    _vector->m_items = (int *)realloc(_vector->m_items, 
                        (_vector-> m_size + _vector->m_blockSize) * sizeof(int));
        
    if(NULL == _vector->m_items)
    {
        _vector->m_items = save_arr;
        return ERR_ALLOCTAION_FAILED; 
    }
    
    _vector-> m_size += _vector->m_blockSize;
    return ERR_OK;       
}

static ADTErr ReductionVector(Vector *_vector)
{
    int *save_arr = _vector->m_items;

    _vector->m_items = (int *)realloc(_vector->m_items, 
                       (_vector-> m_size - _vector->m_blockSize) 
                        * sizeof(int));
        
    if(NULL == _vector->m_items)
    {
        _vector->m_items = save_arr;
        return ERR_ALLOCTAION_FAILED; 
    }
    
    _vector-> m_size -= _vector->m_blockSize;
    return ERR_OK;       
}

static ADTErr CheckVectorInitialize(Vector *_vector)
{
    if(NULL == _vector || NULL == _vector->m_items)
    {
        return ERR_NOT_INITIALZED;
    }

    return ERR_OK;

}

static ADTErr CheckIndex(Vector *_vector, size_t _index)
{
    if(_index >= _vector->m_nItems)
    {
        return ERR_WRONG_INDEX;
    }

    return ERR_OK;
}

/* -------------------------- test functions------------------- */
ADTErr GetVectorSize(Vector * _vector, size_t *_size)
{
    if(NULL != _vector)
    {
        *_size = _vector->m_size;
        return ERR_OK;
    }
    
    return ERR_NOT_INITIALZED;
}


