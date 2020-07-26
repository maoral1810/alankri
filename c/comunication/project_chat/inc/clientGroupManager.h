#ifndef __CLIENT_GROUP_MANAGER_H__
#define __CLIENT_GROUP_MANAGER_H__

#include "errors.h"

typedef struct CGroupManager CGroupManager;

CGroupManager* CreateCGroupManager();

void CGroupManagerDestroy(CGroupManager* _gManager);

ERR AddNewGroup (CGroupManager* _gManager, const char* _groupName, int _groupSocket);

int HasGroupExsist (CGroupManager* _gManager, const char* _groupName);

#endif /*__CLIENT_GROUP_MANAGER_H__ */