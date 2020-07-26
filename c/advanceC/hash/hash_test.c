#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc , free */
#include "hash.h"
#include "dllist.h"
#include "listitr.h"
#include "listfunctions.h"
#include "colors.h"

#define ARR_LENGTH(x) (sizeof(x) / sizeof(x[0]))
static void PrintResualt(char *_testName, char *_scenario, int err);

static int IsEqualKeyFunction(const void* _firstKey, const void* _secondKey);
/* static int IsKeyValue(const void* _key, void* _value, void* _context); */
static size_t HashFunc(const void *_key);
/* static void DestroyValue(void* _toDestroy);
static void DestroyKey(void* _toDestroy); */


static void TestHashMapCreateHashFuncNULL(void);
static void TestHashMapCreateKeyFuncNULL(void);
static void TestHashMapCreateCapcityZero(void);
static void TestHashMapCreate(void);

static void TestHashMapDestroyKeyAndValueNull(void);
/* static void TestHashMapDestroyKeyNull(void);
static void TestHashMapDestroyValueNull(void);
static void TestHashMapDestroyKeyAndValue(void); */

static void TestHashMapInsertMapNull(void);
static void TestHashMapInsertValueNull(void);
static void TestHashMapInsertkeyNull(void);
static void TestHashMapInsertDuplicatedKey(void);
static void TestHashMapInsertNotDuplicateKey(void);

static void TestHashMapFindMapNull(void);
static void TestHashMapFindSearchKeyNull(void);
static void TestHashMapFindPValueNull(void);
static void TestHashMapFindExsistKey(void);
static void TestHashMapFindNotExsistKey(void);

static void TestHashMapSizeMapNULL(void);
static void TestHashMapSizeMapEmpty(void);
static void TestHashMapSize10Elements(void);

static void TestHashMapRemoveMapNULL(void);
static void TestHashMapRemoveValueNULL(void);
static void TestHashMapRemoveSearchKeyNULL(void);
static void TestHashMapRemovePKeyNULL(void);
static void TestHashMapRemoveSearchKeyNotExsist(void);
static void TestHashMapRemoveSearchKeyExsist(void);

int main(void)
{
    TestHashMapCreateHashFuncNULL();
    TestHashMapCreateKeyFuncNULL();
    TestHashMapCreateCapcityZero();
    TestHashMapCreate();

    TestHashMapDestroyKeyAndValueNull();
/*     TestHashMapDestroyKeyNull();
    TestHashMapDestroyValueNull();
    TestHashMapDestroyKeyAndValue(); */

    TestHashMapInsertMapNull();
    TestHashMapInsertValueNull();
    TestHashMapInsertkeyNull();
    TestHashMapInsertDuplicatedKey();
    TestHashMapInsertNotDuplicateKey();

    TestHashMapFindMapNull();
    TestHashMapFindSearchKeyNull();
    TestHashMapFindPValueNull();
    TestHashMapFindExsistKey();
    TestHashMapFindNotExsistKey();

    TestHashMapSizeMapNULL();
    TestHashMapSizeMapEmpty();
    TestHashMapSize10Elements();

    TestHashMapRemoveMapNULL();
    TestHashMapRemoveValueNULL();
    TestHashMapRemoveSearchKeyNULL();
    TestHashMapRemovePKeyNULL();
    TestHashMapRemoveSearchKeyNotExsist();
    TestHashMapRemoveSearchKeyExsist();
    
    return 0;
}


static void TestHashMapCreateHashFuncNULL(void)
{
    char *testNmae = "TestHashMapCreate";
    char *scenario = "HashFuncNULL";
    int err = 0;


    if (NULL != HashMapCreate(10, NULL, IsEqualKeyFunction))
    {
        ++err;
    }

    PrintResualt(testNmae, scenario, err);
}

static void TestHashMapCreateKeyFuncNULL(void)
{
    char *testNmae = "TestHashMapCreate";
    char *scenario = "KeyFuncNULL";
    int err = 0;


    if (NULL != HashMapCreate(10, HashFunc, NULL))
    {
        ++err;
    }

    PrintResualt(testNmae, scenario, err);
}

static void TestHashMapCreateCapcityZero(void)
{
    char *testNmae = "TestHashMapCreate";
    char *scenario = "CapcityZero";
    int err = 0;


    if (NULL != HashMapCreate(0, HashFunc, IsEqualKeyFunction))
    {
        ++err;
    }

    PrintResualt(testNmae, scenario, err);
}

static void TestHashMapCreate(void)
{
    char *testNmae = "TestHashMapCreate";
    char *scenario = "";
    int err = 0;
    HashMap *newHash;

    newHash = HashMapCreate(10, HashFunc, IsEqualKeyFunction);
    if (NULL == newHash)
    {
        ++err;
    }

    HashMapDestroy(&newHash, NULL , NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestHashMapDestroyKeyAndValueNull(void)
{
    char *testNmae = "TestHashMapDestroy";
    char *scenario = "KeyAndValueNull";
    int err = 0;
    HashMap *newHash;

    newHash = HashMapCreate(10, HashFunc, IsEqualKeyFunction);

    HashMapDestroy(&newHash, NULL , NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestHashMapInsertMapNull(void)
{
    char *testNmae = "TestHashMapInsert";
    char *scenario = "MapNull";
    int err = 0;
    int value = 100;
    int key = 1;

    if(MAP_UNINITIALIZED_ERROR != HashMapInsert(NULL, &key, &value))
    {
        ++err;
    }

    PrintResualt(testNmae, scenario, err); 
}

static void TestHashMapInsertValueNull(void)
{
    char *testNmae = "TestHashMapInsert";
    char *scenario = "ValueNull";
    int err = 0;
    int key = 1;
    HashMap *newHash;

    newHash = HashMapCreate(10, HashFunc, IsEqualKeyFunction);
    
    if(MAP_UNINITIALIZED_ERROR != HashMapInsert(newHash, &key, NULL))
    {
        ++err;
    }
    
    HashMapDestroy(&newHash, NULL , NULL);
    PrintResualt(testNmae, scenario, err); 
}

static void TestHashMapInsertkeyNull(void)
{
    char *testNmae = "TestHashMapInsert";
    char *scenario = "keyNull";
    int err = 0;
    int value = 10;
    HashMap *newHash;

    newHash = HashMapCreate(10, HashFunc, IsEqualKeyFunction);
    
    if(MAP_KEY_NULL_ERROR != HashMapInsert(newHash, NULL, &value))
    {
        ++err;
    }
    
    HashMapDestroy(&newHash, NULL , NULL);
    PrintResualt(testNmae, scenario, err); 
}

static void TestHashMapInsertDuplicatedKey(void)
{
    char *testNmae = "TestHashMapInsert";
    char *scenario = "DuplicatedKey";
    int err = 0;
    int value[] = {10,20,30,40,50};
    size_t size = ARR_LENGTH(value);
    size_t key[] = {1,2,3,4,1};
    size_t i;
    HashMap *newHash;

    newHash = HashMapCreate(size * 2, HashFunc, IsEqualKeyFunction);
    
    for(i = 0; i < size - 1; ++i)
    {
        if(MAP_SUCCESS != HashMapInsert(newHash, &key[i], &value[i]))
        {
            ++err;
        }
    }

    if(MAP_KEY_DUPLICATE_ERROR != (HashMapInsert(newHash, &key[i], &value[i])))
    {
        ++err;
    }
    
    HashMapDestroy(&newHash, NULL , NULL);
    PrintResualt(testNmae, scenario, err); 
}

static void TestHashMapInsertNotDuplicateKey(void)
{
    char *testNmae = "TestHashMapInsert";
    char *scenario = "NotDuplicatedKey";
    int err = 0;
    int value[] = {10,20,30,40,50};
    size_t size = ARR_LENGTH(value);
    size_t key[] = {1,2,3,4,5};
    size_t i;
    HashMap *newHash;

    newHash = HashMapCreate(size * 2, HashFunc, IsEqualKeyFunction);
    
    for(i = 0; i < size; ++i)
    {
        if(MAP_SUCCESS != HashMapInsert(newHash, &key[i], &value[i]))
        {
            ++err;
        }
    }

    HashMapDestroy(&newHash, NULL , NULL);
    PrintResualt(testNmae, scenario, err); 
}

static void TestHashMapFindMapNull(void)
{
    char *testNmae = "TestHashMapFind";
    char *scenario = "MapNull";
    int err = 0;
    size_t key = 1;
    void *value;

    if(MAP_UNINITIALIZED_ERROR != HashMapFind(NULL, &key, &value))
    {
        ++err;
    }
    
    PrintResualt(testNmae, scenario, err); 
}

static void TestHashMapFindSearchKeyNull(void)
{
    char *testNmae = "TestHashMapFind";
    char *scenario = "SearchKeyNull";
    int err = 0;
    void *value;
    HashMap *newHash;

    newHash = HashMapCreate(10, HashFunc, IsEqualKeyFunction);

    if(MAP_KEY_NULL_ERROR != HashMapFind(newHash, NULL, &value))
    {
        ++err;
    }
    
    HashMapDestroy(&newHash, NULL , NULL);
    PrintResualt(testNmae, scenario, err); 
}

static void TestHashMapFindPValueNull(void)
{
    char *testNmae = "TestHashMapFind";
    char *scenario = "PValueNull";
    int err = 0;
    size_t key = 10;
    HashMap *newHash;

    newHash = HashMapCreate(10, HashFunc, IsEqualKeyFunction);

    if(MAP_UNINITIALIZED_ERROR != HashMapFind(newHash, &key, NULL))
    {
        ++err;
    }
    
    HashMapDestroy(&newHash, NULL , NULL);
    PrintResualt(testNmae, scenario, err); 
}

static void TestHashMapFindExsistKey(void)
{
    char *testNmae = "TestHashMapInsert";
    char *scenario = "NotDuplicatedKey";
    int err = 0;
    int value[] = {10,20,30,40,50};
    void *returnData;
    size_t size = ARR_LENGTH(value);
    size_t key[] = {1,2,3,4,5};
    size_t i;
    HashMap *newHash;

    newHash = HashMapCreate(size * 2, HashFunc, IsEqualKeyFunction);
    
    for(i = 0; i < size; ++i)
    {
        if(MAP_SUCCESS != HashMapInsert(newHash, &key[i], &value[i]))
        {
            ++err;
        }
    }

    if(MAP_SUCCESS != HashMapFind(newHash, &key[2], &returnData) || *(int *)returnData != value[2])
    {
        ++err;
    }

    HashMapDestroy(&newHash, NULL , NULL);
    PrintResualt(testNmae, scenario, err); 
}
static void TestHashMapFindNotExsistKey(void)
{
    char *testNmae = "TestHashMapInsert";
    char *scenario = "NotDuplicatedKey";
    int err = 0;
    int value[] = {10,20,30,40,50};
    void *returnData;
    size_t notValidKey = 6;
    size_t size = ARR_LENGTH(value);
    size_t key[] = {1,2,3,4,5};
    size_t i;
    HashMap *newHash;

    newHash = HashMapCreate(size * 2, HashFunc, IsEqualKeyFunction);
    
    for(i = 0; i < size; ++i)
    {
        if(MAP_SUCCESS != HashMapInsert(newHash, &key[i], &value[i]))
        {
            ++err;
        }
    }

    if(MAP_KEY_NOT_FOUND_ERROR != HashMapFind(newHash, &notValidKey, &returnData))
    {
        ++err;
    }

    HashMapDestroy(&newHash, NULL , NULL);
    PrintResualt(testNmae, scenario, err); 
}

static void TestHashMapSizeMapNULL(void)
{
    char *testNmae = "TestHashMapSize";
    char *scenario = "MapNULL";
    int err = 0;

    if(0 != HashMapSize(NULL))
    {
        ++err;
    }
    
    PrintResualt(testNmae, scenario, err); 
}

static void TestHashMapSizeMapEmpty(void)
{
    char *testNmae = "TestHashMapSize";
    char *scenario = "MapEmpty";
    int err = 0;
    HashMap *newHash;

    newHash = HashMapCreate(2, HashFunc, IsEqualKeyFunction);

    if(0 != HashMapSize(newHash))
    {
        ++err;
    }
    
    HashMapDestroy(&newHash, NULL , NULL);
    PrintResualt(testNmae, scenario, err); 
}

static void TestHashMapSize10Elements(void)
{
    char *testNmae = "TestHashMapSize";
    char *scenario = "10Elements";
    int err = 0;
    HashMap *newHash;
    int value[] = {10,20,30,40,50,60,70,80,90,100};
    size_t size = ARR_LENGTH(value);
    size_t i;
    size_t key[] = {1,2,3,4,5,6,7,8,9,10};
    newHash = HashMapCreate(size * 2, HashFunc, IsEqualKeyFunction);

    for(i = 0; i < size; ++i)
    {
        HashMapInsert(newHash, &key[i], &value[i]);
    }

    if(size != HashMapSize(newHash))
    {
        ++err;
    }
    
    HashMapDestroy(&newHash, NULL , NULL);
    PrintResualt(testNmae, scenario, err); 
}

static void TestHashMapRemoveMapNULL(void)
{
    char *testNmae = "TestHashMapRemove";
    char *scenario = "MapNULL";
    int err = 0;
    void *pKey;
    void *pValue;
    size_t key = 1;

    if(MAP_UNINITIALIZED_ERROR != HashMapRemove(NULL, &key, &pKey, &pValue))
    {
        ++err;
    }
    
    PrintResualt(testNmae, scenario, err); 
}

static void TestHashMapRemoveValueNULL(void)
{
    char *testNmae = "TestHashMapRemove";
    char *scenario = "ValueNULL";
    int err = 0;
    void *pKey;
    size_t key = 1;
    HashMap *newHash;

    newHash = HashMapCreate(20, HashFunc, IsEqualKeyFunction);
    
    if(MAP_UNINITIALIZED_ERROR != HashMapRemove(newHash, &key, &pKey, NULL))
    {
        ++err;
    }
    
    HashMapDestroy(&newHash, NULL , NULL);
    PrintResualt(testNmae, scenario, err); 
}

static void TestHashMapRemoveSearchKeyNULL(void)
{
    char *testNmae = "TestHashMapRemove";
    char *scenario = "SearchKeyNULL";
    int err = 0;
    void *pKey;
    void *pValue;
    HashMap *newHash;

    newHash = HashMapCreate(20, HashFunc, IsEqualKeyFunction);
    
    if(MAP_KEY_NULL_ERROR != HashMapRemove(newHash, NULL, &pKey, &pValue))
    {
        ++err;
    }
    
    HashMapDestroy(&newHash, NULL , NULL);
    PrintResualt(testNmae, scenario, err); 
}

static void TestHashMapRemovePKeyNULL(void)
{
    char *testNmae = "TestHashMapRemove";
    char *scenario = "PKeyNULL";
    int err = 0;
    void *pValue;
    size_t key = 1;
    HashMap *newHash;

    newHash = HashMapCreate(20, HashFunc, IsEqualKeyFunction);
    
    if(MAP_UNINITIALIZED_ERROR != HashMapRemove(newHash, &key, NULL, &pValue))
    {
        ++err;
    }
    
    HashMapDestroy(&newHash, NULL , NULL);
    PrintResualt(testNmae, scenario, err); 
}

static void TestHashMapRemoveSearchKeyNotExsist(void)
{
    char *testNmae = "TestHashMapRemove";
    char *scenario = "SearchKeyNotExsist";
    int err = 0;
    void *pValue;
    void *pKey;
    HashMap *newHash;
    int value[] = {10,20,30,40,50,60,70,80,90,100};
    size_t size = ARR_LENGTH(value);
    size_t i;
    size_t key[] = {1,2,3,4,5,6,7,8,9,10};
    size_t notExsistKey = 11;
    newHash = HashMapCreate(size * 2, HashFunc, IsEqualKeyFunction);

    for(i = 0; i < size; ++i)
    {
        HashMapInsert(newHash, &key[i], &value[i]);
    }

    newHash = HashMapCreate(20, HashFunc, IsEqualKeyFunction);
    
    if(MAP_KEY_NOT_FOUND_ERROR != HashMapRemove(newHash, &notExsistKey, &pKey, &pValue))
    {
        ++err;
    }
    
    HashMapDestroy(&newHash, NULL , NULL);
    PrintResualt(testNmae, scenario, err); 
}

static void TestHashMapRemoveSearchKeyExsist(void)
{
    char *testNmae = "TestHashMapRemove";
    char *scenario = "SearchKeyExsist";
    int err = 0;
    void *pValue;
    void *pKey;
    HashMap *newHash;
    int value[] = {10,20,30,40,50,60,70,80,90,100};
    size_t size = ARR_LENGTH(value);
    size_t i;
    size_t key[] = {1,2,3,4,5,6,7,8,9,10};
    newHash = HashMapCreate(size * 2, HashFunc, IsEqualKeyFunction);

    for(i = 0; i < size; ++i)
    {
        HashMapInsert(newHash, &key[i], &value[i]);
    }

    if(MAP_SUCCESS != HashMapRemove(newHash, &key[7], &pKey, &pValue) && *(int *)pValue != value[7])
    {
        ++err;
    }

    HashMapDestroy(&newHash, NULL , NULL);
    PrintResualt(testNmae, scenario, err); 
}

/* 
static void TestHashMapDestroyKeyNull(void)
{
    char *testNmae = "TestHashMapDestroy";
    char *scenario = "KeyNull";
    int err = 0;
    HashMap *newHash;
    size_t i ;
    int data[] = {1,2,3,4,5,6,7,8,9,10};
    size_t size = ARR_LENGTH(data);
    void **values = (void **)malloc(sizeof(void *) * 10);
    if(values == NULL)
    {
        return;
    }

    newHash = HashMapCreate(10, HashFunc, IsEqualKeyFunction);

    for(i = 0; i < size; ++i)
    {
        values[i] = &data[i];
        HashMapInsert(newHash,&i, values[i]);
    }

    HashMapDestroy(&newHash, NULL, DestroyValue);
    free(values);
    PrintResualt(testNmae, scenario, err);
}

static void TestHashMapDestroyValueNull(void)
{
    char *testNmae = "TestHashMapDestroy";
    char *scenario = "ValueNull";
    int err = 0;
    HashMap *newHash;
    size_t i ;
    int data[] = {1,2,3,4,5,6,7,8,9,10};
    size_t size = ARR_LENGTH(data);
    void **keys = (void **)malloc(sizeof(void *) * 10);
    if(keys == NULL)
    {
        return;
    }

    newHash = HashMapCreate(10, HashFunc, IsEqualKeyFunction);

    for(i = 0; i < size; ++i)
    {
        keys[i] = &data[i];
        HashMapInsert(newHash, keys[i],&i);
    }

    HashMapDestroy(&newHash, DestroyKey, NULL);
    free(keys);
    PrintResualt(testNmae, scenario, err);
}

static void TestHashMapDestroyKeyAndValue(void)
{
    char *testNmae = "TestHashMapDestroy";
    char *scenario = "KeyAndValue";
    int err = 0;
    HashMap *newHash;
    size_t i;
    int key[] = {1,2,3,4,5,6,7,8,9,10};
    int value[] = {10,20,30,40,50,60,70,80,90,100};
    size_t size = ARR_LENGTH(key);
    void **values = (void **)malloc(sizeof(void *) * 10);
    void **keys = NULL;
    if(values == NULL)
    {
        return;
    }
    keys = (void **)malloc(sizeof(void *) * 10);
    if(keys == NULL)
    {
        free(values);
        return;
    }

    newHash = HashMapCreate(10, HashFunc, IsEqualKeyFunction);

    for(i = 0; i < size; ++i)
    {
        values[i] = &value[i];
        keys[i] = &key[i];
        HashMapInsert(newHash, keys[i], values[i]);
    }

    HashMapDestroy(&newHash, DestroyKey , DestroyValue);
    free(keys);
    free(values);
    PrintResualt(testNmae, scenario, err);
} */


/* --------------------helpful functions ----------------------------*/
static void PrintResualt(char *_testName, char *_scenario, int err)
{
    if (err)
    {
        printf(BOLDCYAN "%s" BOLDYELLOW ":%s: " BOLDRED "FAIL!\n" RESET,
               _testName, _scenario);
    }
    else
    {
        printf(BOLDCYAN "%s" BOLDYELLOW ":%s: " BOLDGREEN "SUCSSES \n" RESET, _testName, _scenario);
    }
}

static size_t HashFunc(const void *_key)
{
    return *(size_t *)_key;
}

static int IsEqualKeyFunction(const void* _firstKey, const void* _secondKey)
{
    return *(size_t *)_firstKey == *(size_t *)_secondKey;
}

/* static int IsKeyValue(const void* _key, void* _value, void* _context)
{
    return 1;
} */

/* static void DestroyValue(void* _toDestroy)
{
   free(_toDestroy);
}

static void DestroyKey(void* _toDestroy)
{
   free(_toDestroy);
} */
