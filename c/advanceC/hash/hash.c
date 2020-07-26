#include <stdlib.h> /* malloc, calloc, free */
#include <math.h>   /* sqrt */
#include "hash.h"
#include "dllist.h"
#include "listitr.h"
#include "listfunctions.h"

#define MAGIC_NUMBER 0XACACACAC
#define MAGIC_DESTROY 0xBEDC0FFE

#define GET_INDEX(map, key)(map->m_hashFunc(key) % map->m_capacity)

struct HashMap
{
    void **m_hash;
    size_t m_capacity;
    HashFunction m_hashFunc;
    EqualityFunction m_keysEqualFunc;
    unsigned long m_magicNumber;
};

typedef struct Pair
{
    const void *m_value;
    const void *m_key;
}Pair;

typedef struct PradicateContext
{
    EqualityFunction m_equalKeyFunc;
    const void *m_key;
}PradicateContext;

static Pair *CreatePair(const void *_key, const void *_value);
static int PradicateFucn(void *_element, void *_context);
static ListItr FindByKey(List *_list, const void *_key, EqualityFunction _equalKey);

static void DestroyHashKey(HashMap *_map, void (*_keyDestroy)(void* _value));
static void DestroyHashValue(HashMap *_map, void (*_valDestroy)(void* _value));
static void DestroyHashKeyAndValue(HashMap *_map, 
                                void (*_keyDestroy)(void* _key), 
                                void (*_valDestroy)(void* _value));
static size_t NextPrime(size_t _num);
static void DestroyPair(Pair *_pair);
static int IsPrime(size_t _num);

HashMap* HashMapCreate(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
    HashMap *newHash = NULL;

    if(NULL ==_hashFunc || NULL == _keysEqualFunc || _capacity < 1)
    {
        return NULL;
    }

    newHash = (HashMap *)malloc(sizeof(HashMap));
    if(NULL == newHash)
    {
        return NULL;
    }
    
    _capacity = NextPrime(_capacity);
    newHash->m_hash = (void **)calloc(_capacity, sizeof(void *));

    if(NULL == newHash->m_hash)
    {
        free(newHash);
        return NULL;
    }

    newHash->m_capacity = _capacity;
    newHash->m_keysEqualFunc = _keysEqualFunc;
    newHash->m_hashFunc = _hashFunc;
    newHash->m_magicNumber = MAGIC_NUMBER;

    return newHash;
}

void HashMapDestroy(HashMap** _map, 
                    void (*_keyDestroy)(void* _key), 
                    void (*_valDestroy)(void* _value))
{
    size_t i;
    size_t capacity;

    if(NULL != _map && NULL != *_map && (*_map)->m_magicNumber == MAGIC_NUMBER)
    {
        if(NULL != _keyDestroy && NULL != _valDestroy)
        {
            DestroyHashKeyAndValue(*_map, _keyDestroy, _valDestroy);
        }
        else if(NULL == _keyDestroy && NULL != _valDestroy)
        {
            DestroyHashValue(*_map, _valDestroy);
        }
        else if(NULL != _keyDestroy && NULL == _valDestroy)
        {
            DestroyHashKey(*_map, _keyDestroy);
        }
        
        capacity = (*_map)->m_capacity;
        for(i = 0; i < capacity; ++i)
        {
            if(NULL != (*_map)->m_hash[i])
            {
                ListDestroy((*_map)->m_hash[i], NULL);
            }
        }
        
        
        free((*_map)->m_hash);
        free(*_map);
        *_map = NULL;
    }
}

MapResult HashMapInsert(HashMap* _map, const void* _key, const void* _value)
{
    size_t index;
    Pair *newPair;

    if(_map == NULL || _map->m_magicNumber != MAGIC_NUMBER || _value == NULL)
    {
        return MAP_UNINITIALIZED_ERROR;
    }

    if(NULL == _key)
    {
        return MAP_KEY_NULL_ERROR;
    }

    if(NULL == (newPair = CreatePair(_key, _value)))
    {
        return MAP_UNINITIALIZED_ERROR;
    }

    index = GET_INDEX(_map, _key);
    
    if(NULL == _map->m_hash[index])
    {
        _map->m_hash[index] = ListCreate();
        if(NULL == _map->m_hash[index])
        {
            return MAP_ALLOCATION_ERROR;
        }
    }
    else
    {
        ListItr findRes = FindByKey(_map->m_hash[index], _key, _map->m_keysEqualFunc);
        if(!ListItrEquals(findRes , ListItrEnd(_map->m_hash[index])))
        {
            free(newPair);
            return MAP_KEY_DUPLICATE_ERROR;
        }
    }
    
    ListPushHead( (List *)_map->m_hash[index], (void *)newPair);

    return MAP_SUCCESS;   
}

MapResult HashMapFind(const HashMap* _map, const void* _searchKey, void** _pValue)
{
    size_t index;
    void *element;
    ListItr findRes;

    if(_map == NULL || _map->m_magicNumber != MAGIC_NUMBER || _pValue == NULL)
    {
        return MAP_UNINITIALIZED_ERROR;
    }

    if(NULL == _searchKey)
    {
        return MAP_KEY_NULL_ERROR;
    }

    index = GET_INDEX(_map, _searchKey);

    if(NULL != _map->m_hash[index])
    {
        findRes = FindByKey(_map->m_hash[index], _searchKey, _map->m_keysEqualFunc);
        if(!ListItrEquals(findRes , ListItrEnd(_map->m_hash[index])))
        {
            element = ListItrGet(findRes);
            *_pValue = (void *)((Pair *)element)->m_value;
            return MAP_SUCCESS;
        }
    }

    return MAP_KEY_NOT_FOUND_ERROR;
}

size_t HashMapSize(const HashMap* _map)
{
    size_t counter = 0;
    size_t i = 0;
    size_t capcity;
    

    if(_map == NULL || _map->m_magicNumber != MAGIC_NUMBER)
    {
        return counter;
    }

    capcity = _map->m_capacity;
    for(;i < capcity; ++i)
    {
        counter += ListSize(_map->m_hash[i]);
    }

    return counter;
}

MapResult HashMapRemove(HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue)
{
    size_t index;
    Pair *removedpair;
    ListItr findRes;

    if(_map == NULL || _map->m_magicNumber != MAGIC_NUMBER || _pValue == NULL || _pKey == NULL)
    {
        return MAP_UNINITIALIZED_ERROR;
    }

    if(NULL == _searchKey)
    {
        return MAP_KEY_NULL_ERROR;
    }

    index = GET_INDEX(_map, _searchKey);
    
    if(NULL != _map->m_hash[index])
    {
        findRes = FindByKey(_map->m_hash[index], _searchKey, _map->m_keysEqualFunc);
        if(!ListItrEquals(findRes , ListItrEnd(_map->m_hash[index])))
        {
            removedpair = (Pair *)ListItrGet(findRes);
            *_pValue = (void *)(removedpair)->m_value;
            *_pKey = (void *)(removedpair)->m_key;
            DestroyPair(removedpair);
            return MAP_SUCCESS;
        }
    }

    return MAP_KEY_NOT_FOUND_ERROR; 
}

size_t HashMapForEach(const HashMap* _map, KeyValueActionFunction _action, void* _context)
{
    size_t counter = 0;
    size_t size = _map->m_capacity;
    size_t i;
    ListItr itr;
    ListItr begin;
    ListItr end;

    if(_map == NULL || _map->m_magicNumber != MAGIC_NUMBER || _action == NULL)
    {
        return counter;
    }

    for(i = 0; i < size; ++i)
    {
        if(NULL != _map->m_hash[i])
        {
            begin = ListItrBegin(_map->m_hash[i]);
            end = ListItrEnd(_map->m_hash[i]);
        
            itr = ListItrForEach(begin, end,(ListActionFunction)_action, _context);
        
            if(ListItrEquals(itr,end))
            {
                counter += ListSize(_map->m_hash[i]);
            }
            else
            {
                while (!ListItrEquals(itr,begin))
                {
                    ++counter;
                    begin = ListItrNext(begin);
                }

                return counter;
            }
        }
    }
    
    return counter;
}


/* ------------------------ static functions ---------------------*/
static Pair *CreatePair(const void *_key, const void *_value)
{
    Pair *newPair = (Pair *)malloc(sizeof(Pair));

    if(NULL == newPair)
    {
        return NULL;
    }

    newPair->m_key = _key;
    newPair->m_value = _value;

    return newPair;
}

static void DestroyPair(Pair *_pair)
{
    free(_pair);
}



static ListItr FindByKey(List *_list, const void *_key, EqualityFunction _equalKey)
{
    ListItr itr;
    
    PradicateContext context;
    
    context.m_equalKeyFunc = _equalKey;
    context.m_key = _key;

    itr = ListItrFindFirst(ListItrBegin(_list), ListItrEnd(_list), PradicateFucn, &context);

    return itr;
}

static int PradicateFucn(void *_element, void *_context)
{
    PradicateContext newContext = *(PradicateContext *)_context;
    Pair *elementPair = (Pair *)_element;

    return newContext.m_equalKeyFunc(newContext.m_key, elementPair->m_key);
}

static void DestroyHashKeyAndValue(HashMap *_map, 
                                void (*_keyDestroy)(void* _key), 
                                void (*_valDestroy)(void* _value))
{
    size_t i = 0;
    size_t size = _map->m_capacity;
    ListItr begin;
    ListItr end;
    ListItr prev;
    Pair *element;

    for(i = 0; i < size; ++i)
    {
        if(NULL != _map->m_hash[i])
        {
            begin = ListItrBegin(_map->m_hash[i]);
            end = ListItrEnd(_map->m_hash[i]);

            while(!ListItrEquals(begin, end))
            {
                element = ListItrGet(begin);
                prev = begin;
                _keyDestroy((void *)(element->m_key));
                _valDestroy((void *)(element->m_value));
                begin = ListItrNext(begin);
                ListItrRemove(prev);
            }
        }
    }
}

static void DestroyHashValue(HashMap *_map, void (*_valDestroy)(void* _value))
{
    size_t i = 0;
    size_t size = _map->m_capacity;
    ListItr begin;
    ListItr end;
    ListItr prev;
    Pair *element;

    for(i = 0; i < size; ++i)
    {
        if(NULL != _map->m_hash[i])
        {
            begin = ListItrBegin(_map->m_hash[i]);
            end = ListItrEnd(_map->m_hash[i]);

            while(!ListItrEquals(begin, end))
            {
                element = ListItrGet(begin);
                prev = begin;
                _valDestroy((void *)(element->m_value));
                begin = ListItrNext(begin);
                ListItrRemove(prev);
            }
        }
    }
}

static void DestroyHashKey(HashMap *_map, void (*_keyDestroy)(void* _value))
{
    size_t i = 0;
    size_t size = _map->m_capacity;
    ListItr begin;
    ListItr end;
    ListItr prev;
    Pair *element;

    for(i = 0; i < size; ++i)
    {
        if(NULL != _map->m_hash[i])
        {
            begin = ListItrBegin(_map->m_hash[i]);
            end = ListItrEnd(_map->m_hash[i]);

            while(!ListItrEquals(begin, end))
            {
                element = ListItrGet(begin);
                prev = begin;
                _keyDestroy((void *)(element->m_key));
                begin = ListItrNext(begin);
                ListItrRemove(prev);
            }
        }
    }
}

static size_t NextPrime(size_t _num)
{
    size_t checkPrime = _num;
    int found = 0;

    if (_num <= 1)
    {
        return 2;
    }

    while (!found)
    {
        checkPrime++;
        if (IsPrime(checkPrime))
        {
            found = 1;
        }
    }

    return checkPrime;
}

static int IsPrime(size_t _num)
{
	double sqr;
	int i = 2;

	sqr = sqrt(_num);

	while (i < sqr)
	{
		if (_num % i == 0)
			return 0;
		i++;
	}

	return 1;
}