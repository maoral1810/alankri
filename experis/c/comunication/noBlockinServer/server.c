#include <string.h>     /* memset       */      
#include <sys/types.h>  /* sockaddr, SOCK_DGRAM , AF_INET */
#include <sys/socket.h> /* socket       */
#include <netinet/in.h> 
#include <stdio.h>      /* perror       */
#include <arpa/inet.h>  /* inet_addr    */
#include <unistd.h>     /* sleep , fcntl*/
#include <fcntl.h>      /* fcntl        */
#include <stdlib.h>     /* atoi         */
#include <signal.h>     /* sigaction */
#include <errno.h>
#include "../../advanceC/include/dllist.h"
#include "../../advanceC/include/listitr.h"

#define SIZE 32
#define BACK_LOG 20
#define MAX_CLIENTS 1000

static void NoBlocking(int _sock);
static void CheckCurrent(List *_clientPool);
static void CurrentNew(int _listenSock, struct sockaddr* _clientSin, socklen_t* _len, List* _clientpool);
static void CloseAllClients(List* _clientPool);
static void SignalInit();
void TurnOffWhile();
void DestroyClient(void* _client);

static int g_run = 1;
static int msgCount = 0;

int main(int argc, char* argv[])
{
    int listenSock = 0;    
    int optval = 1;
    struct sockaddr_in serverSin;
    struct sockaddr_in clientSin;
    socklen_t len = sizeof(clientSin);

    List *clientPool = ListCreate();

    if(NULL == clientPool)
    {
        printf("fail in listcreate\n");
        return 0;
    }

    if(argc != 3)
    {
        printf("invalid parmeters\n");
        return 0;
    }

    memset(&serverSin, 0, sizeof(serverSin));
    memset(&clientSin, 0, sizeof(clientSin));
    
    listenSock = socket(AF_INET, SOCK_STREAM, 0);
    if(listenSock == -1)
    {
        perror("fail in socket(server)");
        return 0;
    }

    if(setsockopt(listenSock, SOL_SOCKET, SO_REUSEADDR,&optval, sizeof(optval)) < 0)
    {
        perror("reuse failed(server)");
        return 0;
    }

    serverSin.sin_family = AF_INET;
    serverSin.sin_addr.s_addr = INADDR_ANY;
    serverSin.sin_port = htons(atoi(argv[2]));

    clientSin.sin_family = AF_INET;
    clientSin.sin_addr.s_addr = inet_addr(argv[1]);
    clientSin.sin_port = htons(atoi(argv[2]));

    if(bind(listenSock,(struct sockaddr *)&serverSin, sizeof(serverSin)) < 0)
    {
        perror("fail in bind");
        return 0;
    }

    if(listen(listenSock, BACK_LOG) < 0)
    {
        perror("listen fail (server)");
        return 0;
    }
    NoBlocking(listenSock);
    SignalInit();

    while(g_run)
    {
        CurrentNew(listenSock, (struct sockaddr *)&clientSin, &len, clientPool);
        CheckCurrent(clientPool);       
    }

    CloseAllClients(clientPool);
    
    return 0;
}

static void NoBlocking(int _sock)
{
    int flags = 0;
    flags = fcntl(_sock, F_GETFL);
    fcntl(_sock, F_SETFL, flags | O_NONBLOCK);
}

static void CurrentNew(int _listenSock, struct sockaddr *_clientSin, socklen_t *_len, List *_clientpool)
{
    int newClientSock = accept(_listenSock, _clientSin, _len);
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
        NoBlocking(newClientSock);
        if(LIST_SUCCESS != ListPushTail(_clientpool, newClientSockPTR))
        {
            printf("fail to push new client to pool");
        }
    }
}

static void CheckCurrent(List *_clientPool)
{
    ListItr itr = ListItrBegin(_clientPool);
    ssize_t resBytes = 0;
    int clientSock = 0;
    char buffer[SIZE] = {0};
    char msg[SIZE] = {0};
    size_t poolsize = ListSize(_clientPool);

    while(poolsize--)
    {
        clientSock = *((int*)ListItrGet(itr));

        resBytes = recv(clientSock, buffer, sizeof(buffer) - 1, 0);
        if(resBytes <= 0)
        {
            if((errno != EAGAIN) && (errno != EWOULDBLOCK) || resBytes == 0)
            {
                printf("disconect client\n");
                close(clientSock);
/*                 itr = ListItrNext(itr);
                ListItrRemove(ListItrPrev(itr)); */
                ListItrRemove((itr));
            }
        }

        else
        {
            buffer[resBytes] = '\0';
            printf("server recive:%s\n", buffer);
            snprintf(msg,SIZE,"server msg# %d", msgCount++);
            send(clientSock, msg, strlen(msg), 0);
        }
        
        itr = ListItrNext(itr);

    }   
}

static void CloseAllClients(List* _clientPool)
{
    ListDestroy(&_clientPool ,DestroyClient);
}

static void SignalInit()
{
    struct sigaction sig;
    sig.sa_handler = TurnOffWhile;
    sig.sa_flags = 0;
    sigemptyset(&sig.sa_mask);

    if (sigaction(SIGINT, &sig, NULL) == -1)
    {
        perror("sigaction");
        exit(1);
    }
}

void TurnOffWhile()
{
    g_run = 0;
}

void DestroyClient(void* _client)
{
    close(*(int*)_client);
    free(_client);
}