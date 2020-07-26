#ifndef __CLIENT_MANAGER_H__
#define __CLIENT_MANAGER_H__

#include "errors.h"

typedef struct ClientManager ClientManager;

ClientManager* ClientManagerCreate(const char* _ip, const char* _port);

void ClientManagerCreateDestroy(ClientManager* _manager);

ERR ClientManagerRun(ClientManager* _manager);

static ERR GetGroups(ClientManager* _manager,char* _groups);

static ERR joinGroup(ClientManager* _manager,char* _groupName);
#endif /* __CLIENT_MANAGER_H__*/