#include <stdio.h>  /* snprintf ,printf*/
#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* strlen */
#include "groupManager.h"
#include "hashmap.h"

#define MAGIC_NUM 0XABAB1810
#define BAD_MAGIC 0XDEADBEAF
#define GROUPS_FILE "groups"
#define FIRST_HOST 1
#define LAST_HOST 50
#define IP_LENGTH 17
#define CHAT_NAME_LENGTH 32
#define MAX_GROUP 50
#define NETWORK_ADD "224.0.0."
#define FALSE 0
#define TRUE !FALSE

static int InitIpPool(List* _ipPool);
static void DestroyIp(void* _ip);
static char* GetGroupIp(GroupManager* _manager);
static void Create4Groups(GroupManager* _manager);

/* hash functions */
static size_t HashFunc(const void* _key);
static int EqualityFunc(const void *_firstKey, const void *_secondKey);
static int KeyValueActionFunc(const void *_key, void *_value, void *_context);

struct GroupManager
{
    size_t magic_number;
    HashMap* GroupsPool;
    List* GroupsIpPool;
};

struct Group
{
    char m_groupName[CHAT_NAME_LENGTH];
    char* m_groupIP;
    int m_port;
    size_t m_NumOfClients;
};

GroupManager* CreateGroupManager()
{
    GroupManager* manager = (GroupManager*)malloc(sizeof(GroupManager));

    if(NULL == manager)
    {
        return NULL;
    }

    manager->GroupsIpPool = ListCreate();
    if(NULL == manager->GroupsIpPool)
    {
        free(manager);
        return NULL;
    }

    manager->GroupsPool = HashMapCreate(MAX_GROUP,HashFunc, EqualityFunc);
    if(NULL == manager->GroupsPool)
    {
        free(manager->GroupsIpPool);
        free(manager);
        return NULL;
    }

    InitIpPool(manager->GroupsIpPool);
    manager->magic_number = MAGIC_NUM;

    Create4Groups(manager);

    return manager;
}

void DestroyGroupManager(GroupManager* _manager)
{
    if(_manager != NULL && _manager->magic_number == MAGIC_NUM)
    {
        ListDestroy(&_manager->GroupsIpPool,DestroyIp);
        HashMapDestroy(&_manager->GroupsPool, NULL, NULL);/*?destroy group?*/
    }
}

ERR GetActiveGroups(GroupManager* _manager, const char* _fileName)
{
    size_t hashSize = HashMapSize(_manager->GroupsPool);
    FILE* fp = fopen(_fileName, "w");

    if(NULL == fp)
    {
        return OPEN_FILE_FAILED;
    }

/*     if(hashSize != HashMapForEach(_manager->GroupsPool, KeyValueActionFunc, &fp))
    {
        return GENERAL_FAILURE;
    } */

    fprintf(fp,"%s %s %s %s","Chat1", "Chat2", "Chat3", "Chat4");

    return ERR_OK;
}

ERR AddToGroup(GroupManager* _manager, const char* _groupName)
{
    void* groupPTR;
    MapResult status = HashMapFind(_manager->GroupsPool, _groupName, &groupPTR);

    if(MAP_SUCCESS != status || groupPTR == NULL)
    {
        return GROUP_NOT_EXSIST;
    }

    ++(*((Group **)groupPTR))->m_NumOfClients;

    return ERR_OK;
}

ERR LeaveGroup(GroupManager* _manager, const char* _groupName)
{
    void* groupPTR;
    MapResult status = HashMapFind(_manager->GroupsPool, _groupName, &groupPTR);

    if(MAP_SUCCESS != status || groupPTR == NULL)
    {
        return GROUP_NOT_EXSIST;
    }

    --(*((Group **)groupPTR))->m_NumOfClients;

    return ERR_OK;
}

/* ----------------------- static functions ----------------------------*/
static int InitIpPool(List* _ipPool)
{
    char* ipAdd = NULL;
    size_t i = FIRST_HOST;
    void* res;

    while(i < LAST_HOST)
    {
        ipAdd = (char*)malloc(sizeof(IP_LENGTH));
        if(NULL == ipAdd)
        {
            return FALSE;
        }
        snprintf(ipAdd, IP_LENGTH, NETWORK_ADD "%lu", i++);
        ListPushHead(_ipPool, ipAdd);
    }

    return TRUE;
}

static void DestroyIp(void* _ip)
{
    free(_ip);
}

/* -------------------- hash functions ----------------- */
static size_t HashFunc(const void* _key)
{
    size_t res = 0;
    char* str = (char*)_key;
    size_t len = strlen(str);
    size_t i = 0;

    while(i++ < len)
    {
        res += *str * i;
        ++str;
    }

    return res;
}

static int EqualityFunc(const void *_firstKey, const void *_secondKey)
{
    return (strcmp((char*)_firstKey, (char*)_secondKey) == 0);
}

static int KeyValueActionFunc(const void *_key, void *_value, void *_context)
{
    fprintf((FILE*)_context,"%s", ((Group*)_value)->m_groupName);
    return TRUE;
}

static void Create4Groups(GroupManager* _manager)
{
    Group* newChat1;
    Group* newChat2;
    Group* newChat3;
    Group* newChat4;
    
    newChat1 = (Group*)malloc(sizeof(Group));
    newChat2 = (Group*)malloc(sizeof(Group));
    newChat3 = (Group*)malloc(sizeof(Group));
    newChat4 = (Group*)malloc(sizeof(Group));

    newChat1->m_groupIP = GetGroupIp(_manager);
    strcpy(newChat1->m_groupName, "Chat1");

    newChat2->m_groupIP = GetGroupIp(_manager);
    strcpy(newChat2->m_groupName, "Chat2");

    newChat3->m_groupIP = GetGroupIp(_manager);
    strcpy(newChat3->m_groupName, "Chat3");

    newChat4->m_groupIP = GetGroupIp(_manager);
    strcpy(newChat4->m_groupName, "Chat4");

    HashMapInsert(_manager->GroupsPool, "Chat1",newChat1);
    HashMapInsert(_manager->GroupsPool, "Chat2",newChat2);
    HashMapInsert(_manager->GroupsPool, "Chat3",newChat3);
    HashMapInsert(_manager->GroupsPool, "Chat4",newChat4);

    return;
}

static char* GetGroupIp(GroupManager* _manager)
{
    void* ip;
    ListPopHead(_manager->GroupsIpPool,&ip);
    return *(char**)ip;
}

