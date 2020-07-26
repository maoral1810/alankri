#ifndef __USER_MANAGER_H__
#define __USER_MANAGER_H__

#include "errors.h"
typedef struct User User;
typedef struct UserManager UserManager;

UserManager* CreateUserManager();

void DestroyUserManager(UserManager* _manager);

ERR RegistretUser(UserManager* _manager, const char* _userName, const char* _password, int _socket);

ERR Login(UserManager* _manager, const char* _userName, const char* _password, int _socket);

ERR Logout(UserManager* _manager, const char* _userName, int _socket);

ERR LogFromFile(UserManager* _manager, const char* _fileName);

ERR SaveToFile(UserManager* _manager, const char* _fileName);

ERR JoinGroup(UserManager* _manager, const char* _groupName, const char* _userName);

ERR UserLeaveGroup(UserManager* _manager, const char* _groupName, const char* _userName);








#endif /* __USER_MANAGER_H__ */