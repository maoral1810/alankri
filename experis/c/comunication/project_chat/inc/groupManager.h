#ifndef __GROUP_MANAGER_H__
#define __GROUP_MANAGER_H__

#include "list.h"
#include "list_itr.h"
#include "errors.h"

typedef struct Group Group;
typedef struct GroupManager GroupManager; 

GroupManager* CreateGroupManager();

void DestroyGroupManager(GroupManager* _manager);

ERR AddToGroup(GroupManager* _manager, const char* _groupName);/*??*/

ERR LeaveGroup(GroupManager* _manager, const char* _groupName);

ERR GetActiveGroups(GroupManager* _manager, const char* _fileName);

/* clients functions

Group* CreateGroup(GroupManager* _manager, const char* GroupName);

void DestroyGroup(GroupManager* _manager,Group* _toDestroy); */


#endif /*__GROUP_MANAGER_H__ */