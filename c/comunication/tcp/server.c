#include <string.h>     /* memset */      
#include <sys/types.h>  /* sockaddr, SOCK_DGRAM , AF_INET */
#include <sys/socket.h> /* socket */
#include <netinet/in.h> 
#include <stdio.h>      /* perror */
#include <arpa/inet.h>  /* inet_addr */
#include <unistd.h> /* sleep */
#include <stdlib.h> /* atoi */

#define SIZE 1024
#define BACK_LOG 8

int main(int argc, char* argv[])
{
    int listenSock = 0;    
    int optval = 1;
    int clientSock = 0;
    struct sockaddr_in serverSin;
    struct sockaddr_in clientSin;
    char buffer[SIZE] = {0};
    char msg[] = "i am server #";
    socklen_t len = sizeof(buffer);
    ssize_t resBytes = 0;
    int i = 4;
    /* char* seq[] = {"0", "1","2","3","4","5","6","7","8","9","10"}; */
    if(argc != 3)
    {
        printf("invalid parmeters\n");
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

    clientSock = accept(listenSock, (struct sockaddr *)&clientSin, &len);
    if(clientSock < 0)
    {
        perror("accept fail (server)");
        return 0;
    }
    
    while(i--)
    {
        resBytes = recv(clientSock, buffer, sizeof(buffer), 0);
        if(resBytes == 0)
        {
            printf("client was close => disconected from client\n");
            sleep(2);
            close(clientSock);
            return 0;
        }
        else if(resBytes < 0)
        {
            perror("fail in recv(server)");
            return 0;
        }
        else
        {
            buffer[resBytes] = '\0';
            printf("server recive:%s\n", buffer);
        }
        sleep(1);
        if((send(clientSock, msg, sizeof(msg), 0)) < 0)
        {
            perror("fail in send(client)");
            return 0;
        }
    }

    close(clientSock);
    close(listenSock);

    return 0;
}
