#include <stdlib.h>
#include "hashmap.h"
#include "list.h"
#include "list_itr.h"
#include "list_functions.h"

#define MAGIC_NUM 0xBEEFBEEF
#define NO_MAGIC_NUM 0xDEADBEEF
#define IS_FOUND 0
#define NOT_FOUND -1

typedef void (*Destroyer)(void*);

struct HashMap
{
    size_t m_magicNum;
    void** m_table;
    size_t m_size;
    EqualityFunction m_equalityFunc;
    HashFunction m_hashFunc;
};

typedef struct KVPair
{
    void* m_key;
    void* m_value;
    EqualityFunction m_equalityFunc;
} KVPair;

typedef struct KVPairDestroyer
{
    Destroyer m_keyDestroyer;
    Destroyer m_valueDestroyer;
} KVPairDestroyer;

typedef struct KVAct
{
    KeyValueActionFunction m_kvAct;
    void* m_context;
} KVAct;

/* ----------------------------------- */
static size_t  NearestLargerPrime  (size_t _capacity);
static void    InitHashMap         (HashMap* _map, size_t _size, HashFunction _hashFunc, EqualityFunction _keysEqualFunc);
static int     DestroyNode         (void* _kvPairHolder, void* _kvPairDestroyer);
static void    DestroyBasket       (void* _basket, KVPairDestroyer _kvPairDestroyer);
static KVPair* CreatePair          (void* _key, void* _value, EqualityFunction _keysEqualFunc);
static ListItr KeyItrInBasket      (HashMap *_map, size_t _index, const void *_key, void **_pValue);
static int     IsKeyAtItr          (void* _pair, void* _key);
static size_t  CountInBasket       (ListItr _begin, ListItr _end);
static int     KVAct2ListAct       (void* _element, void* _context);
/* ----------------------------------- */


HashMap* HashMapCreate (size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
    HashMap* hashMap;
    size_t size;

    if (!_hashFunc || !_keysEqualFunc)
    {
        return NULL;
    }

    hashMap = (HashMap*)malloc(sizeof(HashMap));
    if (!hashMap)
    {
        return NULL;
    }

    size = NearestLargerPrime(_capacity);
    hashMap->m_table = (void**)calloc(size, sizeof(void*));
    if (!(hashMap->m_table))
    {
    	free(hashMap);
        return NULL;
    }

    InitHashMap(hashMap, size, _hashFunc, _keysEqualFunc);
    hashMap->m_magicNum = MAGIC_NUM;
    
    return hashMap;
}


void HashMapDestroy (HashMap** _map, Destroyer _keyDestroy, Destroyer _valDestroy)
{
    size_t i;
    KVPairDestroyer kvPairDestroyer;

    if (!_map || !(*_map) || (*_map)->m_magicNum != MAGIC_NUM)
    {
        return;
    }

    (*_map)->m_magicNum = NO_MAGIC_NUM;

    kvPairDestroyer.m_keyDestroyer = _keyDestroy;
    kvPairDestroyer.m_valueDestroyer = _valDestroy;
    for (i = 0; i < (*_map)->m_size; i++)
    {
        DestroyBasket(&((*_map)->m_table[i]), kvPairDestroyer);
    }

    free((*_map)->m_table);
    free((*_map));
}


MapResult HashMapRehash (HashMap *_map, size_t _newCapacity)
{
    return MAP_SUCCESS;
}


MapResult HashMapInsert (HashMap* _map, const void* _key, const void* _value)
{
    KVPair* kvPair;
    size_t hashIndex;
    List* list;
    ListItr keyItr, end;

    if (!_map || _map->m_magicNum != MAGIC_NUM)
    {
        return MAP_UNINITIALIZED_ERROR;
    }

    if (!_key || !_value) /* Prevent null values, otherwise will have to check it everywhere */
    {
        return MAP_KEYVALUE_NULL_ERROR;
    }

    kvPair = CreatePair((void*)_key, (void*)_value, _map->m_equalityFunc);
    if (!kvPair)
    {
        return MAP_ALLOCATION_ERROR;
    }

    hashIndex = (_map->m_hashFunc)(_key) % _map->m_size;
    if (!(_map->m_table[hashIndex]))
    {
        list = ListCreate(); /* Will not destroy list once basket is empty, since will probably have to reuse it */
        if (!list)
        {
        	free(kvPair);
            return MAP_ALLOCATION_ERROR;
        }
        _map->m_table[hashIndex] = list;
    }
    else
    {
        end = ListItrEnd(_map->m_table[hashIndex]);

        keyItr = KeyItrInBasket(_map,hashIndex,(void*)_key,NULL);
        if(keyItr==NULL || keyItr == end)
        {
            free(kvPair);
            return MAP_KEY_DUPLICATE_ERROR;
        }
    }

    if(ListPushHead(_map->m_table[hashIndex], kvPair) == LIST_ALLOCATION_ERROR)
    {
        return MAP_ALLOCATION_ERROR;
    }
    
    return MAP_SUCCESS;
}


MapResult HashMapRemove (HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue)
{
    size_t hashIndex;
    ListItr keyItr, end;
    KVPair* pairToRemove;

    if (!_map || _map->m_magicNum != MAGIC_NUM)
    {
        return MAP_UNINITIALIZED_ERROR;
    }

    if (!_searchKey || !_pKey || !_pValue)
    {
        return MAP_KEYVALUE_NULL_ERROR;
    }

    hashIndex = (_map->m_hashFunc)(_searchKey) % _map->m_size;
    if (!(_map->m_table[hashIndex]))
    {
        return MAP_KEY_NOT_FOUND_ERROR;
    }

        end = ListItrEnd(_map->m_table[hashIndex]);
        keyItr = KeyItrInBasket(_map,hashIndex,(void*)_pKey,NULL);
        if(keyItr==NULL || keyItr == end)
        {
            return MAP_KEY_NOT_FOUND_ERROR;
        }


	/* Func: RemovePair */
    pairToRemove = ListItrGet(keyItr);
    ListItrRemove(keyItr);	/* pairToRemove = (KVPair*)ListItrRemove(keyItr); -> check returned status of this func */
    *_pKey = pairToRemove->m_key;
    *_pValue = pairToRemove->m_value;
    free(pairToRemove);		/* DestroyPair */

    return MAP_SUCCESS;
}


MapResult HashMapFind(const HashMap* _map, const void* _searchKey, void** _pValue)
{
    size_t hashIndex;
    ListItr keyItr, end;
    KVPair* foundPair;

    if (!_map || _map->m_magicNum != MAGIC_NUM)
    {
        return MAP_UNINITIALIZED_ERROR;
    }

    if (!_searchKey || !_pValue)
    {
        return MAP_KEYVALUE_NULL_ERROR;
    }

    hashIndex = (_map->m_hashFunc)(_searchKey) % _map->m_size;
    if(!(_map->m_table[hashIndex]))
    {
        return MAP_KEY_NOT_FOUND_ERROR;
    }

    end = ListItrEnd(_map->m_table[hashIndex]);

        keyItr = KeyItrInBasket((HashMap*)_map,hashIndex,(void*)_searchKey,NULL);
        if(keyItr==NULL || keyItr == end)
        {
            return MAP_KEY_NOT_FOUND_ERROR;
        }
    
    

    foundPair = ListItrGet(keyItr);
    *_pValue = foundPair->m_value;    
    return MAP_SUCCESS;
}


size_t HashMapSize (const HashMap* _map)
{
    size_t i, size = 0;
    ListItr begin, end;

    if (!_map || _map->m_magicNum != MAGIC_NUM)
    {
        return 0;
    }

    for (i = 0; i < _map->m_size; i++)
    {
        begin = ListItrBegin(_map->m_table[i]);
        end = ListItrEnd(_map->m_table[i]);
        if (ListItrEquals(begin, g_wrongItr) || ListItrEquals(begin, end)) /* If list was not created or is empty (pairs removed) */
        {
            continue;
        }

        size += CountInBasket(begin, end); /* ListSize !!! */
        /* Keep in loop only: size += ListSize(...); */
    }
    return size;
}


size_t HashMapForEach (const HashMap* _map, KeyValueActionFunction _action, void* _context)
{
    size_t i, actionCalls = 0;
    ListItr begin, end, itrOut;
    KVAct kvAct;

    if (!_map || _map->m_magicNum != MAGIC_NUM || !_action)
    {
        return 0;
    }

    kvAct.m_kvAct = _action;
    kvAct.m_context = _context;
    for (i = 0; i < _map->m_size; i++)
    {
        begin = ListItrBegin(_map->m_table[i]);
        end = ListItrEnd(_map->m_table[i]);
        if (ListItrEquals(begin, g_wrongItr) || ListItrEquals(begin, end))
        {
            continue;
        }

        itrOut = ListItrForEach(begin, end, KVAct2ListAct, &kvAct);
        actionCalls += CountInBasket(begin, itrOut);
    }
    return actionCalls;
}

/* ----------------------------------- */

static size_t NearestLargerPrime (size_t _capacity)
{
    size_t i, currentNum, NLPrime;

    currentNum = NLPrime = _capacity;
    
    while (NLPrime == _capacity)
    {
        currentNum++;
        for (i = 2; i < currentNum; i++)
        {
            if (currentNum % 2 == 0)
            {
                break;
            }
            else
            {
                NLPrime = currentNum;
            }
        }
    }

    return NLPrime;
}

static void InitHashMap (HashMap* _map, size_t _size, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
    _map->m_size = _size;
    _map->m_hashFunc = _hashFunc;
    _map->m_equalityFunc = _keysEqualFunc;
}

static void DestroyBasket (void* _basket, KVPairDestroyer _kvPairDestroyer)
{
    List* list = (List*)_basket;
    ListItr begin = ListItrBegin(list), end = ListItrEnd(list);

    if (ListItrEquals(begin, g_wrongItr))
    {
        return;
    }

    if (!ListItrEquals(begin, end))
    {
        ListItrForEach(begin, end, DestroyNode, &_kvPairDestroyer);
    }

    free(list);
}

static int DestroyNode (void* _kvPairHolder, void* _kvPairDestroyer)
{
    ListItr kvPairHolder = (ListItr)_kvPairHolder;
    KVPairDestroyer* kvPairDestroyer = (KVPairDestroyer*)_kvPairDestroyer;
    KVPair* kvPair = ListItrGet(_kvPairHolder);

    if (kvPairDestroyer->m_keyDestroyer)
    {
        (kvPairDestroyer->m_keyDestroyer)(kvPair->m_key);
    }

    if (kvPairDestroyer->m_valueDestroyer)
    {
        (kvPairDestroyer->m_valueDestroyer)(kvPair->m_value);
    }

    free(kvPair);
    free(kvPairHolder);

    return 1;
}

static KVPair* CreatePair(void* _key, void* _value, EqualityFunction _keysEqualFunc)
{
    KVPair* kvPair = (KVPair*)malloc(sizeof(KVPair));
    if (!kvPair)
    {
        return NULL;
    }

    kvPair->m_key = _key;
    kvPair->m_value = _value;
    kvPair->m_equalityFunc = _keysEqualFunc;

    return kvPair;
}



static ListItr KeyItrInBasket(HashMap *_map, size_t _index, const void *_key, void **_pValue)
{
   ListItr itr, endItr;
    KVPair *pair = NULL;

    itr = ListItrBegin(_map->m_table[_index]);
    endItr = ListItrEnd(_map->m_table[_index]);

    while((ListItrEquals(itr, endItr) == 0))
    {
        pair = (KVPair *)ListItrGet(itr);

        if (_map->m_equalityFunc(pair->m_key, _key) == 1)
        {
            if (_pValue)
            {
                *_pValue = pair->m_value;
            }
            return itr;
        }
        itr = ListItrNext(itr);
    }
    return NULL;
}



static size_t CountInBasket (ListItr _begin, ListItr _end)
{
    size_t count = 0;

    while (!ListItrEquals(_begin, _end))
    {
        count++;
        _begin = ListItrNext(_begin);
    }
    return count;
}

static int KVAct2ListAct (void* _element, void* _context)
{
    KVPair* kvPair = ListItrGet(_element);

    return (((KVAct*)_context)->m_kvAct)(kvPair->m_key, kvPair->m_value, ((KVAct*)_context)->m_context);
}
