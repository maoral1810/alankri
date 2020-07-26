#include<stdlib.h> /* malloc, free */
#include<stddef.h> /* size_t */
#include "vector.h" /* Vector API */

#define RESIZE_FACTOR 2
#define DECREASE_SIZE -1
#define INCREASE_SIZE 1
#define FALSE 0
#define MAGIC_NUMBER 0XACACACAC
#define MAGIC_DESTROY 0xBEDC0FFE

static VectorResult AppendCheckParams(Vector* _vector, void* _item);
static VectorResult SetCheckParam(Vector* _vector, size_t _index, void*  _value);
static VectorResult GetCheckParam(const Vector* _vector, size_t _index, void** _pValue);
static VectorResult RemoveCheckParams(Vector* _vector, void** _pValue);
static VectorResult RellocNewMemory(Vector *_vector, int _reallocFlag);

struct Vector
{
    size_t m_magicNumber;
    void **m_items;            /* array of data                               */
    size_t m_originalSize;     /* original allcated space for items           */
    size_t m_size;             /* actual allocated space for item             */
    size_t m_nItems;           /* actual number of items                      */
    size_t m_blockSize;        /* the chunk size to be allocated when no space*/
};

Vector* VectorCreate(size_t _initialCapacity, size_t _blockSize)
{
    Vector *vector = NULL;
    void  **m_items = NULL;

    if(0 == _initialCapacity && 0 == _blockSize)
    {
        return NULL;
    }

    vector = (Vector *)malloc(sizeof(Vector));

    if( NULL == vector)
    {
        return NULL;
    }

    m_items = (void **)malloc(sizeof(void *) * _initialCapacity + 1);

    if(NULL == m_items)
    {
        free(vector);
        vector = NULL;
        return NULL;
    }

    vector->m_magicNumber = MAGIC_NUMBER;
    vector ->m_items = m_items;
    vector->m_nItems = 0;
    vector->m_originalSize = _initialCapacity;
    vector->m_size =  _initialCapacity;
    vector->m_blockSize = _blockSize;

    return vector;
}

void VectorDestroy(Vector** _vector, void (*_elementDestroy)(void* _item))
{
    size_t i;

    if(_vector != NULL && *_vector != NULL && MAGIC_NUMBER == (*_vector)->m_magicNumber)
    {
        (*_vector)->m_magicNumber = MAGIC_DESTROY;
        
        if(_elementDestroy != NULL)
        {
            for(i = 1; i < (*_vector)->m_nItems + 1; ++i)
            {
                _elementDestroy((*_vector)->m_items[i]);
            }
        }

        free((*_vector)->m_items);

        free(*_vector);
        *_vector = NULL;
    }
}

VectorResult VectorAppend(Vector* _vector, void* _item)
{
    VectorResult status = AppendCheckParams(_vector, _item);

    if(VECTOR_SUCCESS == status)
    {
        if(_vector->m_nItems == _vector->m_size)
        {
            status = RellocNewMemory(_vector, INCREASE_SIZE);
        }

        if(VECTOR_SUCCESS == status)
        {
            _vector->m_items[++_vector->m_nItems] = _item;
        }
    }
    
    return status;
}

VectorResult VectorRemove(Vector* _vector, void** _pValue)
{
	VectorResult status = RemoveCheckParams(_vector, _pValue);

    /* check if Vector and item inisilize before delete*/
	if(VECTOR_SUCCESS == status)
    {
        size_t FreeSpace = 0;

        if(0 == _vector->m_nItems)
        {
            return VECTOR_UNDERFLOW;
        }

        /* delete item */
        *_pValue = _vector->m_items[_vector->m_nItems];
        --_vector->m_nItems;
        
        /* calculate if realloc is require (reduction Vector) */
        FreeSpace = _vector->m_size - _vector->m_nItems - 1; 
        
        if((_vector->m_size != _vector->m_originalSize) && 
           FreeSpace > (RESIZE_FACTOR * _vector->m_blockSize))
        {
            status = RellocNewMemory(_vector, DECREASE_SIZE);
        }
    }

    return status; 
}

VectorResult VectorGet(const Vector* _vector, size_t  _index, void** _pValue)
{
	VectorResult status = GetCheckParam(_vector , _index, _pValue);

	if(VECTOR_SUCCESS == status)
	{
		*_pValue = _vector->m_items[_index];	
	}

	return status;
}

VectorResult VectorSet(Vector* _vector, size_t _index, void*  _value)
{
	VectorResult status = SetCheckParam(_vector , _index, _value);

	if(VECTOR_SUCCESS == status)
	{
		 _vector->m_items[_index] = _value;
	}

	return status;
}

size_t VectorSize(const Vector* _vector)
{
	if( NULL != _vector)
	{
		return _vector->m_nItems;
	}
	
	return FALSE;  
}

size_t VectorCapacity(const Vector* _vector)
{
	if( NULL != _vector)
	{
		return _vector->m_size;
	}
	
	return FALSE;  
}

size_t VectorForEach(const Vector* _vector, VectorElementAction _action, void* _context)
{
    size_t i = 1;
    void *element;

    while (VECTOR_SUCCESS == VectorGet(_vector, i++, &element))
    {
        if(_action(element, i, _context) == FALSE)
        {
            break;
        }		
    }		
    
    return i - 2;
}

/*----------------- check parameters functions -------------------*/
static VectorResult AppendCheckParams(Vector* _vector, void* _item)
{
    if(_vector == NULL || _item == NULL || _vector->m_magicNumber != MAGIC_NUMBER)
    {
        return VECTOR_UNITIALIZED_ERROR;
    }

    return  VECTOR_SUCCESS;
}

static VectorResult RemoveCheckParams(Vector* _vector, void** _pValue)
{
    if(_vector == NULL || _pValue == NULL || _vector->m_magicNumber != MAGIC_NUMBER)
    {
        return VECTOR_UNITIALIZED_ERROR;
    }

    return  VECTOR_SUCCESS;
}

static VectorResult GetCheckParam(const Vector* _vector, size_t _index, void** _pValue)
{
	if(_vector == NULL || _pValue == NULL || _vector->m_magicNumber != MAGIC_NUMBER)
	{
		return VECTOR_UNITIALIZED_ERROR;
	}

	if(_index > _vector->m_nItems || _index < 1)
	{
		return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
	}

	return  VECTOR_SUCCESS;
}

static VectorResult  SetCheckParam(Vector* _vector, size_t _index, void*  _value)
{
	if(_vector == NULL || _value == NULL || _vector->m_magicNumber != MAGIC_NUMBER)
	{
		return VECTOR_UNITIALIZED_ERROR;
	}

	if(_index > _vector->m_nItems || _index < 1)
	{
		return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
	}

	return  VECTOR_SUCCESS;
}

/* ---------------------- static functions -------------------------------- */
static VectorResult RellocNewMemory(Vector *_vector, int _reallocFlag)
{
    void **save_arr = _vector->m_items;

    if(0 == _vector->m_blockSize)
    {
        return VECTOR_OVERFLOW;
    }
	
    _vector->m_items = (void **)realloc(_vector->m_items, 
                       _reallocFlag * (_vector-> m_size + _vector->m_blockSize) * sizeof(void *));
	        
    if(NULL == _vector->m_items)
    {
        _vector->m_items = save_arr;
        return VECTOR_ALLOCATION_ERROR; 
    }
    
    _vector-> m_size += (_reallocFlag * _vector->m_blockSize);
    
    return VECTOR_SUCCESS;       
}
