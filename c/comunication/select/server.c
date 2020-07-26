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
#include "../../advanceC/include/dllist.h"
#include "../../advanceC/include/listitr.h"

#define SIZE 32
#define BACK_LOG 20
#define MAX_CLIENTS 1000
#define MAX_DISCRIPTORS 1024

static void CheckCurrent(List *_clientPool, fd_set* _master, fd_set* _copyMaster, size_t activities);
static void CurrentNew(int _listenSock, struct sockaddr *_serverSin, socklen_t *_len, List *_clientpool, fd_set* _master);
static void CloseAllClients(List* _clientPool);
static void SignalInit();
void TurnOffWhile();
void DestroyClient(void* _client);
static void NoBlocking(int _sock);
static int CheckActivities(fd_set* _copyMaster);

static int g_run = 1;
static int msgCount = 0;

int main(int argc, char* argv[])
{
    int listenSock = 0;
    int activities = 0;    
    int optval = 1;
    struct sockaddr_in serverSin;
    socklen_t len = sizeof(serverSin);
    fd_set master;
    fd_set copyMaster;
    List *clientPool = ListCreate();

    FD_ZERO(&master);
    FD_ZERO(&copyMaster);

    if(NULL == clientPool)
    {
        printf("fail in listcreate\n");
        return 0;
    }

    if(argc != 2)
    {
        printf("invalid parmeters\n");
        return 0;
    }

    memset(&serverSin, 0, sizeof(serverSin));
    
    listenSock = socket(AF_INET, SOCK_STREAM, 0);
    if(listenSock == -1)
    {
        perror("fail in socket(server)");
        return 0;
    }
    
    NoBlocking(listenSock);

    if(setsockopt(listenSock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
    {
        perror("reuse failed(server)");
        return 0;
    }

    /* TODO one struct */

    serverSin.sin_family = AF_INET;
    serverSin.sin_addr.s_addr = INADDR_ANY;
    serverSin.sin_port = htons(atoi(argv[1]));

    if(bind(listenSock,(struct sockaddr *)&serverSin, len) < 0)
    {
        perror("fail in bind");
        return 0;
    }

    if(listen(listenSock, BACK_LOG) < 0)
    {
        perror("listen fail (server)");
        return 0;
    }

    FD_SET(listenSock, &master);
    SignalInit();

    while(g_run)
    {
        copyMaster = master;
        activities = CheckActivities(&copyMaster);
        if (activities >= 1 && FD_ISSET(listenSock,&copyMaster))
        {
            CurrentNew(listenSock, (struct sockaddr *)&serverSin, &len, clientPool, &master);
            --activities;
        }
        CheckCurrent(clientPool, &master,&copyMaster, activities);            
    }

    CloseAllClients(clientPool);
    
    return 0;
}

static void CurrentNew(int _listenSock, struct sockaddr *_serverSin, socklen_t *_len, List *_clientpool, fd_set* _master)
{
    int newClientSock = accept(_listenSock, _serverSin, _len);
    int* newClientSockPTR;
    size_t poolSize = ListSize(_clientpool);
    
    if(poolSize >= MAX_CLIENTS)
    {
        close(newClientSock);
        printf("client been dumpt by server\n");
    }
    if(newClientSock < 0)
    {
        if((errno != EAGAIN) && (errno != EWOULDBLOCK))
        {
            printf("accept fail (server)");
        }
    }
    else
    {
        newClientSockPTR = (int*)malloc(sizeof(int));
        *newClientSockPTR = newClientSock;
        printf("server accept new socket: %d\n", newClientSock);
        FD_SET(newClientSock, _master);
        if(LIST_SUCCESS != ListPushTail(_clientpool, newClientSockPTR))
        {
            printf("fail to push new client to pool");
        }
    }
}

static void CheckCurrent(List *_clientPool, fd_set* _master, fd_set* _copyMaster, size_t activities)
{
    ListItr itr = ListItrBegin(_clientPool);
    ssize_t resBytes = 0;
    int clientSock = 0;
    char buffer[SIZE] = {0};
    char msg[SIZE] = {0};

    while(activities)
    {
        clientSock = *((int*)ListItrGet(itr));
        if(FD_ISSET(clientSock, _copyMaster))
        {
            resBytes = recv(clientSock, buffer, sizeof(buffer) - 1, 0);
            if(resBytes <= 0)
            {
                    printf("disconect client\n");
                    FD_CLR(clientSock, _master);
                    close(clientSock);
/*                     itr = ListItrPrev(itr);
                    ListItrRemove(ListItrNext(itr)); */
                    ListItrRemove(itr);
            }

            else
            {
                buffer[resBytes] = '\0';
                printf("server recive:%s\n", buffer);
                snprintf(msg, SIZE, "server msg# %d", msgCount++);
                send(clientSock, msg, strlen(msg), 0);
            }
            
            --activities;
        }
        itr = ListItrNext(itr);
        
    }   
}

static void CloseAllClients(List* _clientPool)
{
    ListDestroy(&_clientPool ,DestroyClient);
}

void TurnOffWhile()
{
    g_run = 0;
}

void DestroyClient(void* _client)
{
    printf("disconect from client. socket#%d\n", *(int*)_client);
    close(*(int*)_client);
    free(_client);
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