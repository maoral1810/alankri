#include <stdlib.h>
#include <string.h>
#include "clientGroupManager.h"
#include "errors.h"
#include "hashmap.h"
#include "ChatProtocolLimits.h"

#define FALSE 0
#define TRUE !FALSE
#define MAGIC_NUM 0x18101989
#define MAGIC_DESTROY 0xDEADBEAF

struct CGroupManager
{
    size_t m_magicNumber;
    HashMap* m_clientGroups;

};

static size_t HashFunc (const void* _groupName);
static int EqualityGroupName (const void* _firstGroupName, const void* _secondGroupName);
static void GroupDestroyer(void* _group);
static void GroupNameDestroyer(void* _groupName);

/* -------------- */

CGroupManager* CGroupManagerCreate ()
{
	CGroupManager* cilGroupManager = (CGroupManager*)malloc(sizeof(CGroupManager));
	if (!cilGroupManager)
	{
		return NULL;
	}
	
	cilGroupManager->m_clientGroups = HashMapCreate(MAX_GROUPS, HashFunc, EqualityGroupName);
	if (!cilGroupManager->m_clientGroups)
	{
		free(cilGroupManager);
		return NULL;
	}
	
	return cilGroupManager;
}

void CGroupManagerDestroy(CGroupManager* _gManager)
{
	if(_gManager && MAGIC_NUM == _gManager->m_magicNumber)
	{
		_gManager->m_magicNumber = MAGIC_DESTROY;
        HashMapDestroy(&(_gManager->m_clientGroups), GroupNameDestroyer, GroupDestroyer);
		free(_gManager);
	}
}

ERR AddNewGroup (CGroupManager* _gManager, const char* _groupName, int _groupSocket)
{
    char* HashgroupName;
    int* HashgroupSocket;
	MapResult status;

    if(NULL == _gManager || MAGIC_NUM != _gManager->m_magicNumber)
    {
        return UNINITIALIZE_VALUE;
    }

    HashgroupName = (char*)malloc(sizeof(char) * strlen(_groupName) + 1);
	if(NULL == HashgroupName)
	{
		return ALLOCATION_FAILED;
	}

	HashgroupSocket = (int*)malloc(sizeof(int));
	if(NULL== HashgroupSocket)
	{
		free(HashgroupName);
		return ALLOCATION_FAILED;
	}

	strcpy(HashgroupName, _groupName);

   	status = HashMapInsert(_gManager->m_clientGroups, HashgroupName ,HashgroupSocket);

	if(status != MAP_SUCCESS)
	{
		free(HashgroupName);
		free(HashgroupSocket);
		return (status == MAP_KEY_DUPLICATE_ERROR) ? CLIENT_ALREADY_IN_GROUP : GENERAL_FAILURE;
	}

	return ERR_OK;
}

int HasGroupExsist (CGroupManager* _gManager, const char* _groupName)
{
	void* GroupValue;

	return (HashMapFind(_gManager->m_clientGroups, _groupName, &GroupValue) == MAP_SUCCESS);
}


ERR CGroupMngrRemoveGroup (CGroupManager* _gManager, const char* _groupName, int* _groupSocket)
{
	void* removedGroupName = NULL;
	void* removedGroupSocket;
	MapResult status;

	status = HashMapRemove(_gManager->m_clientGroups, _groupName, &removedGroupName, &removedGroupSocket);
	if (status != MAP_SUCCESS)
	{
		return (status == MAP_KEY_NOT_FOUND_ERROR) ? CLIENT_NOT_IN_GROUP : GENERAL_FAILURE;
	}

	free(removedGroupName);
	*_groupSocket = *(int *)removedGroupSocket;
	free(removedGroupSocket);

	return ERR_OK;
}

/*-------------------------- static functions -------------------*/
static size_t HashFunc (const void* _groupName)
{
	char* str = (char*)_groupName;
	int numOfChars = strlen(str);
	int sumOfChars = 0;
	int i = 0;

	while(*str != '\0')
	{
		sumOfChars += *str;
	}
	return sumOfChars * numOfChars;
}

static int EqualityGroupName(const void* _firstGroupName, const void* _secondGroupName)
{
	return (!strcmp((char*)_firstGroupName, (char*)_secondGroupName));
}

static void GroupNameDestroyer(void* _groupName)
{
	free(_groupName);
}

static void GroupDestroyer(void* _groupSocket)
{
	free(_groupSocket);
}