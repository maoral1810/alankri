#include <stdio.h> /* FILE ,fopen, fclose*/ 
#include <stddef.h> /* size_t */
#include <string.h> /* strcpy */
#include <stdlib.h> /*malloc, free */
#include "errors.h"
#include "userManager.h"
#include "list.h"
#include "list_itr.h"
#include "hashmap.h"
#include "ChatProtocolLimits.h"

#define MAGIC_NUM 0XABAB1810
#define MAGIC_DESTROY 0XDEADBEAF
#define MAX_DISCRIPTORS 1024
#define MAX_CLIENTS 100

struct UserManager
{
    size_t m_magic_number;
    HashMap *m_UserPool;
    FILE* m_ClientsFile;
    char* m_socketVsNameLUT[MAX_DISCRIPTORS];
};

struct User
{
    char m_name[MAX_LEN_USERNAME];
    char m_password[MAX_LEN_PASSWORD];
    int m_socket;
    short m_isActive;
    List* m_groups;  
};

static User* CreateUser(const char* _UserName, const char* _password, int _socket);
static void DestroyUser(User* _toDestroy);/* destroy  specific client*/
/* hash functions */
static size_t HashFunc(const void* _key);
static int EqualityFunc(const void *_firstKey, const void *_secondKey);
static int KeyValueActionFunc(const void *_key, void *_value, void *_context);
static void FreeUsers(void* _user);
static void FreeKey(void* _key);
/* ---------------------------API Functions --------------------------------*/
UserManager* CreateUserManager()
{
    UserManager* manager = (UserManager*)malloc(sizeof(UserManager));

    if(NULL == manager)
    {
        return NULL;
    }

    manager->m_UserPool = HashMapCreate(MAX_CLIENTS, HashFunc, EqualityFunc); /* TODO*/
    if(NULL == manager->m_UserPool)
    {
        free(manager);
        return NULL;
    }

    manager->m_magic_number = MAGIC_NUM;
    memset(manager->m_socketVsNameLUT,'0',sizeof(char*) * MAX_DISCRIPTORS);
    
    return manager;
}

void DestroyUserManager(UserManager* _manager)
{
    if(NULL == _manager && _manager->m_magic_number == MAGIC_NUM)
    {
        _manager->m_magic_number = MAGIC_DESTROY;
        HashMapDestroy(&_manager->m_UserPool, FreeKey,FreeUsers);
    }
}

ERR RegistretUser(UserManager* _manager, const char* _userName, const char* _password, int _socket)
{
    User* newUser = CreateUser(_userName, _password, _socket);
    char* key; 
    if(NULL == newUser)
    {
        return ALLOCATION_FAILED;
    }

    key = (char*)malloc(strlen(_userName) + 1);
    if(NULL == key)
    {
        return ALLOCATION_FAILED;
    }
    
    strcpy(key, _userName);
    
    if(MAP_SUCCESS != HashMapInsert(_manager->m_UserPool, key, newUser))
    {
        free(newUser);
        return USER_EXSIST;
    }

    _manager->m_socketVsNameLUT[_socket] = (char*)malloc(MAX_LEN_USERNAME); 
    strcpy((_manager->m_socketVsNameLUT)[_socket], _userName);

    return ERR_OK;
}

ERR Login(UserManager* _manager, const char* _userName, const char* _password, int _socket)
{
    User* user;
    void* value;
    MapResult status;
    status = HashMapFind(_manager->m_UserPool, _userName, &value);

    if(status == MAP_KEY_NOT_FOUND_ERROR)
    {
        return USER_NOT_EXSIST;
    }

    user = (User*)value;
    
    if(strcmp(user->m_password, _password))
    {
        return WRONG_PASS;
    }
    else if(user->m_isActive)
    {
        return USER_ACTIVE_ALLREADEY;
    }

    if(user->m_socket == 0)
    {
        user->m_socket = _socket;
        strcpy(_manager->m_socketVsNameLUT[_socket],user->m_name);
    }

    return ERR_OK;
}

ERR Logout(UserManager* _manager, const char* _userName, int _socket)
{
    char* userNameLut = (_manager->m_socketVsNameLUT)[_socket];
    void* value;
    User* getUser = NULL;
    MapResult status;

    if(!strcmp(userNameLut, _userName))
    {
        return USER_NOT_EXSIST;
    }

    status = HashMapFind(_manager->m_UserPool, _userName, &value);

    getUser = (User *)value;

    getUser->m_isActive = 0;

    return ERR_OK;
}

ERR SaveToFile(UserManager* _manager, const char* _fileName)
{
    User* curUser = NULL;
    size_t hashSize = HashMapSize(_manager->m_UserPool);
    FILE* fp = fopen(_fileName, "w");

    if(NULL == fp)
    {
        return OPEN_FILE_FAILED;
    }

    /* copy all users to file*/
    if(hashSize != HashMapForEach(_manager->m_UserPool, KeyValueActionFunc,fp))
    {
        printf("hash for each failed\n");
    }
    
    memset(_manager->m_UserPool, '0', sizeof(char *)* MAX_DISCRIPTORS);

    fclose(fp);

    return ERR_OK;
}

ERR LogFromFile(UserManager* _manager, const char* _fileName)
{
    FILE* fp = fopen(_fileName, "r");
    User* curUser = NULL;

    if(NULL == fp)
    {
        return OPEN_FILE_FAILED;
    }

    /* copy all users from file*/
    while(!feof(fp))
    {
        char userName[MAX_LEN_USERNAME];
        char passwrod[MAX_LEN_PASSWORD];

        fscanf(fp,"%s %s\n",userName,passwrod);
        curUser =  CreateUser(userName, passwrod, 0);
        HashMapInsert(_manager->m_UserPool,userName, curUser);
    }

    fclose(fp);

    return ERR_OK;
}

ERR JoinGroup(UserManager* _manager, const char* _groupName, const char* _userName)
{
    void* user;

    if(MAP_SUCCESS != HashMapFind(_manager->m_UserPool,_userName, &user) || NULL == user)
    {
        return USER_NOT_EXSIST;
    }

    ListPushHead(((User *)user)->m_groups, (void *)_groupName);

    return ERR_OK;
}

ERR UserLeaveGroup(UserManager* _manager, const char* _groupName, const char* _userName)
{
    void* user;
    void* curGroup = NULL;
    ListItr current;
    ListItr end;

    if(MAP_SUCCESS != HashMapFind(_manager->m_UserPool,_userName, &user) || NULL == user)
    {
        return USER_NOT_EXSIST;
    }
    
    current = ListItrBegin(((User*)user)->m_groups);
    end = ListItrEnd(((User*)user)->m_groups);
    
    while(!ListItrEquals(current, end))
    {
        curGroup = ListItrGet(current);
        if(strcmp((char *)curGroup, _groupName) == 0)
        {
            ListItrRemove(current);
            return ERR_OK;
        }
    }

    return GROUP_NOT_EXSIST;
}

/*---------------------------- static functions -------------------------*/
static User* CreateUser(const char* _UserName, const char* _password, int _socket)
{
    size_t poolSize;
    
    User* newUser = (User*)malloc(sizeof(User));
    if(NULL == newUser)
    {
        return NULL;
    }

    newUser->m_groups = ListCreate();
    if(NULL == newUser->m_groups)
    {
        free(newUser);
        return NULL;
    }

    newUser->m_isActive = 0;
    newUser->m_socket = _socket;
    strcpy(newUser->m_name, _UserName);
    strcpy(newUser->m_password, _password);

    return newUser;
}

static void FreeUsers(void* _user)
{
    free(_user);
}

static void FreeKey(void* _key)
{
    free(_key);
}

static ERR CheckParam(UserManager* _manager)
{
    if(NULL == _manager && _manager->m_magic_number == MAGIC_NUM)
    {
        return ERR_OK;
    }

    return UNINITIALIZE_VALUE;
}

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
    User* curUser = (User*)_value;
    return fprintf((FILE*)_context,"%s %s\n",curUser->m_name, curUser->m_password);
}
