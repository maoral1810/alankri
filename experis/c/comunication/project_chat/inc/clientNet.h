#ifndef  __CLIENT_NET_H__
#define __CLIENT_NET_H__
#include "errors.h"

typedef struct ClientNet ClientNet;

/*connect to a server*/
ClientNet* ClientNetCreate(const char* _ip, int _port);

void ClientNetDestroy(ClientNet* _netPart);
/*get ip and porn and connect to a server*/

ERR CNetConnect(ClientNet* _cilNet);

/**/
ERR ClientNetSend(void* msg, size_t msgSize, ClientNet* _netPart);

/**/
ERR ClientNetRecive(char* msg,ClientNet* _netPart);

#endif /*__CLIENT_NET_H__*/