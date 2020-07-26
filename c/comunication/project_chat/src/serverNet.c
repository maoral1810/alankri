#include <string.h>     /* memset       */      
#include <sys/socket.h> /* socket       */
#include <netinet/in.h> 
#include <stdio.h>      /* perror       */
#include <arpa/inet.h>  /* inet_addr    */
#include <unistd.h>     /* sleep , fcntl*/
#include <fcntl.h>      /* fcntl        */
#include <stdlib.h>     /* atoi         */
#include <signal.h>     /* sigaction */
#include <errno.h>      /* errno     */
#include <sys/types.h>  /* sockaddr, SOCK_DGRAM , AF_INET,select, FD_CLR, FD_ISSET, FD_SET, FD_ZERO */
#include <sys/time.h>   /* select, FD_CLR, FD_ISSET, FD_SET, FD_ZERO */
#include <sys/select.h> /* select, FD_CLR, FD_ISSET, FD_SET, FD_ZERO */
#include "errors.h"
#include "groupManager.h"
#include "list.h"
#include "list_itr.h"
#include "serverNet.h"
#include "ChatProtocolLimits.h" /* limits macros */

#define MAGIC_NUM 0XABAB1810
#define MAGIC_DESTROY 0XDEADBEAF
#define CLIENT_FILE "clients" /* TODO ::: to add in destroy for save clients */
#define TRUE 1

static short g_run = TRUE;

struct ServerNet
{
    size_t m_magicNumber;
    struct sockaddr_in m_serverSin;
    callback m_callBFunc;
    int m_listenSocket;
    fd_set m_master;
    List* m_clientPool;
    const void* m_activitor;
};

static void NoBlocking(int _sock);
static ERR CurrentNew(ServerNet* _sn);
static int CheckActivities(fd_set* _copyMaster);
static ERR CheckCurrent(ServerNet* _sn, fd_set* _copyMaster, size_t _activities);
static ERR ServerInit(ServerNet* _sn, const char* _port);
static void CloseAllClients(List* _clientPool);
/* check param functions */
static ERR ChackParam(ServerNet* _sn);
static ERR ChackCurrentParam(ServerNet* _sn, fd_set* _cMaster);
static ERR ChackSendParam(ServerNet* _sn, const void* _msg);

ServerNet* CreateServerNet(const char* _port, callback _cbFunc, const void* _activitor)
{
    ServerNet* newSN;
    
    if(NULL == _port || NULL == _cbFunc)
    {
        return NULL;
    }

    newSN = (ServerNet*)calloc(1, sizeof(ServerNet));
    if(NULL == newSN)
    {
        return NULL;
    }

    newSN->m_clientPool = ListCreate();

    if(NULL == newSN->m_clientPool)
    {
        perror("list create failed(server)");
        free(newSN);
        return NULL;
    }

    if(ERR_OK != ServerInit(newSN, _port))
    {
        free(newSN->m_clientPool);
        free(newSN);
        return NULL;
    }

    newSN->m_callBFunc = _cbFunc;
    newSN->m_activitor = _activitor;
    newSN->m_magicNumber = MAGIC_NUM;

    return newSN;
}

void DestroyServerNet(ServerNet* _sn)
{
    if(ChackParam(_sn) == ERR_OK)
    {
        _sn->m_magicNumber = MAGIC_DESTROY;
        CloseAllClients(_sn->m_clientPool);
        free(_sn);
    }
}

ERR RunServerNet(ServerNet* _sn) /* rcev*/
{
    int run = TRUE;
    int activities = 0;
    fd_set saveMaster;    
    size_t len = sizeof(struct sockaddr_in);
    
    while(g_run)
    {
        saveMaster = _sn->m_master;
        activities = CheckActivities(&saveMaster);
        if (activities >= 1 && FD_ISSET(_sn->m_listenSocket, &saveMaster))
        {
            CurrentNew(_sn);
            --activities;
        }
        CheckCurrent(_sn, &saveMaster, activities);            
    }

    return ERR_OK;
}

ERR ServerSend(const void* _msg, int _socket)/* send*/
{
    ERR status = ERR_OK;
    ssize_t sendRes = 0;
    
    if(NULL == _msg)
    {
        status = UNINITIALIZE_VALUE;
    }
    else
    {
        sendRes = send(_socket, _msg, MAX_TOTAL_LEN_MSG ,0);
        if(sendRes < MAX_TOTAL_LEN_MSG)
        {
            status = SEND_FAILED;
        }
    }

    return status;
}

/*-------------------------- static function ----------------*/
static ERR ServerInit(ServerNet* _sn, const char* _port)
{
    int optval = 1;
    size_t len = sizeof(struct sockaddr_in);

    _sn->m_listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(_sn->m_listenSocket == -1)
    {
        perror("socket failed(server)");
        return SOCKET_FAILED;
    }
    
    NoBlocking(_sn->m_listenSocket);
    FD_SET(_sn->m_listenSocket, &_sn->m_master); 
    if(setsockopt(_sn->m_listenSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
    {
        perror("reuse failed(server)");
        return SET_SOCKET_FAILED;
    }
    
    _sn->m_serverSin.sin_family = AF_INET;
    _sn->m_serverSin.sin_addr.s_addr = INADDR_ANY;
    _sn->m_serverSin.sin_port = htons(atoi(_port));

    if(bind(_sn->m_listenSocket,(struct sockaddr *)&_sn->m_serverSin, len) < 0)
    {
        perror("fail in bind");
        return BIND_FAILED;
    }

    if(listen(_sn->m_listenSocket, BACK_LOG) < 0)
    {
        perror("listen fail (server)");
        return LISTEN_FAILED;
    }

    return ERR_OK;
}

static void NoBlocking(int _sock)
{
    int flags = 0;
    flags = fcntl(_sock, F_GETFL);
    fcntl(_sock, F_SETFL, flags | O_NONBLOCK);
}

static int CheckActivities(fd_set* _copyMaster)
{
    return select(MAX_DISCRIPTORS, _copyMaster, NULL, NULL, NULL);
}

static ERR CurrentNew(ServerNet* _sn)
{
    int* newClientSockPTR = NULL;
    socklen_t len = 0;
    size_t poolSize = 0;
    int newClientSock = 0;
    ERR status = ChackParam(_sn);
    
    if(status == ERR_OK)
    {
        poolSize = ListSize(_sn->m_clientPool);
        len = sizeof(struct sockaddr_in);
        
        newClientSock = accept(_sn->m_listenSocket , 
                                (struct sockaddr *)&_sn->m_serverSin, 
                                &len);
        
        if(poolSize >= MAX_CLIENTS)
        {
            close(newClientSock);
        }
        else if(newClientSock < 0)
        {
            perror("accept fail (server)");
            status = ACCEPT_FAILED;
        }
        else
        { 
            /* add client to clients pool*/
            newClientSockPTR = (int*)malloc(sizeof(int));
            *newClientSockPTR = newClientSock;
            printf("new client accept! socket: %d\n", newClientSock);
            FD_SET(newClientSock, &_sn->m_master);
            if(LIST_SUCCESS != ListPushTail(_sn->m_clientPool, newClientSockPTR))
            {
                perror("fail to push new client to pool\n");
            }
        }
    }

    return status;
}

static ERR CheckCurrent(ServerNet* _sn, fd_set* _copyMaster, size_t _activities)
{
    ListItr itr;
    ssize_t resBytes = 0;
    int clientSock = 0;
    char buffer[256];
    ERR status = ChackCurrentParam(_sn, _copyMaster);

    if(status == ERR_OK)
    {
        itr = ListItrBegin(_sn->m_clientPool);
        while(_activities && !ListItrEquals(itr, ListItrEnd(_sn->m_clientPool)))
        {
            clientSock = *((int*)ListItrGet(itr));
            if(FD_ISSET(clientSock, _copyMaster))
            {
                resBytes = recv(clientSock, buffer, sizeof(buffer) - 1, 0);
                if(resBytes <= 0)
                {
                    ListItr itrPrev = ListItrPrev(itr);
                    _sn->m_callBFunc(clientSock, NULL, _sn->m_activitor); /* send to server null msg for closing this client */
                    close(clientSock);
                    printf("disconect client socket: %d\n", clientSock);
                    FD_CLR(clientSock, &_sn->m_master);
                    ListItrRemove(itr);
                    itr = itrPrev;
                }

                else
                {
                    _sn->m_callBFunc(clientSock, buffer, _sn->m_activitor); /* send to server the msg from client */
                }
                
                --_activities;
            }
            itr = ListItrNext(itr);
        }
    }   

    return status;
}

static void CloseAllClients(List* _clientPool)
{
    ListDestroy(&_clientPool ,NULL/* DestroyClient */);
}

static ERR ChackParam(ServerNet* _sn)
{
    if(NULL == _sn || MAGIC_NUM != _sn->m_magicNumber)
    {
        return UNINITIALIZE_VALUE;
    }

    return ERR_OK;
}

static ERR ChackCurrentParam(ServerNet* _sn, fd_set* _cMaster)
{
    if(NULL == _sn || MAGIC_NUM != _sn->m_magicNumber || NULL == _cMaster)
    {
        return UNINITIALIZE_VALUE;
    }

    return ERR_OK;
}

static ERR ChackSendParam(ServerNet* _sn, const void* _msg)
{
    if(NULL == _sn || MAGIC_NUM != _sn->m_magicNumber || NULL == _msg)
    {
        return UNINITIALIZE_VALUE;
    }

    return ERR_OK;
}
