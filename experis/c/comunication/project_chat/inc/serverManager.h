#ifndef __SERVER_H__
#define __SERVER_H__

#define SERVER_NET_PORT "1989"
#include "errors.h"
typedef struct Server Server;

Server *CreateServer();

void DestroyServer(Server *_server);

ERR ServerRun(Server *_server);

ERR ServerStop(Server* _server);

#endif /* __SERVER_H__ */