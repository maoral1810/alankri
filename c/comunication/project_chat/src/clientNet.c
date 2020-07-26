#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>  /* sockaddr_in */
#include <stdlib.h> /*malloc*/
#include <string.h> /* memset */

/* debug */
#include <stdio.h>

#include "clientNet.h"
#include "ChatProtocolLimits.h"
#include "errors.h"

static ClientNet* initClientNet(ClientNet* _clinet, const char* _ip, int _port);

#define FALSE   0
#define TRUE    1
#define MAGIC_NUMBER 0x18181818
#define MAGIC_DESTROY 0xBADBEEF

struct ClientNet
{
    struct sockaddr_in 	m_serverAddr;
    int                 port;
    char                ip[MAX_LEN_IP];
    int                 m_socket;
    int                 magicNum;
};

ClientNet* ClientNetCreate(const char* _ip, int _port)
{
    ClientNet* cilNet = (ClientNet*)calloc(1,sizeof(ClientNet));
    if(NULL == cilNet)
    {
        return NULL;
    }

    return initClientNet(cilNet, _ip, _port);
}

void ClientNetDestroy(ClientNet* _netPart)
{
    if(NULL !=  _netPart && _netPart->magicNum ==MAGIC_NUMBER)
    {
        free(_netPart);
        _netPart->magicNum = MAGIC_DESTROY;
    }
}

ERR CilentNetConnect(ClientNet* _cilNet)
{
    int connectstat;

    /*create socket*/
    _cilNet->m_socket = socket(AF_INET, SOCK_STREAM, 0);

    if(  _cilNet->m_socket < 0)
    {        
        return SOCKET_FAILED;
    }

    connectstat = connect(_cilNet->m_socket,
                    (struct sockaddr *)&(_cilNet->m_serverAddr), 
                    sizeof(struct sockaddr_in));
    if( connectstat < 0 )
    {
        return CONNECTION_FAILED;
    }

    return ERR_OK;
}  

ERR ClientNetSend(void* msg, size_t msgSize, ClientNet* _netPart)
{
    if( (msg == NULL) || (msgSize == 0) || (_netPart == NULL))
    {
        return INVALID_INFO_FROM_CLIENT;
    }

    if(send(_netPart->m_socket, msg, msgSize, 0) < 0)
    {
        return SENDING_FAILED;
    }
    return ERR_OK;
} 

ERR ClientNetRecive(char* msg,ClientNet* _netPart)
{
    int resBytes;
    
    if(msg == NULL || _netPart == NULL)
    {
        return INVALID_INFO_FROM_CLIENT;
    }
    resBytes = recv(_netPart->m_socket, msg,  /*TODO?*/ MAX_TOTAL_LEN_MSG - 1, 0);
    if(resBytes)
    {
        return ERR_OK;
    }
    
    msg[resBytes] = '\0';

    return RECIVE_FAILED;
} 



/* ---------------------- static functions -------------------*/
static ClientNet* initClientNet(ClientNet* _clinet, const char* _ip, int _port)
{
    _clinet->m_serverAddr.sin_family = AF_INET;
    _clinet->m_serverAddr.sin_port = htons(_port);
    _clinet->m_serverAddr.sin_addr.s_addr = inet_addr(_ip);
    _clinet->magicNum = MAGIC_NUMBER;

    strcpy(_clinet->ip, _ip);
    _clinet->port = _port;

    return _clinet;
}