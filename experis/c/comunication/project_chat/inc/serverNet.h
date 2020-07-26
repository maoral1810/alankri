#ifndef __SERVER_NET_H__
#define __SERVER_NET_H__

#define MAX_CLIENTS 1000
#define MAX_DISCRIPTORS 1024
#define BACK_LOG 20

#include "errors.h"

typedef struct ServerNet ServerNet;

typedef void(*callback)(int _socket, void* _msg, const void* _activiator);/* all back send  null msg when rcv == 0 */

ServerNet* CreateServerNet(const char* _port, callback _cbFunc, const void* _activitor);
/*

    inputs:
        _port - port of the server
        _cbFunc - call back function

    output:
        ServerNet on sucsses

    error:
        return NULL on failure 
*/
void DestroyServerNet(ServerNet* _sn);
/*
    
*/
ERR RunServerNet(ServerNet* _sn); /* rcev*/
/*

*/
ERR ServerSend(const void* _msg, int _socket);/* send*/
/*

*/

#endif /* __SERVER_NET_H__ */