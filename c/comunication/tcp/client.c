#include <string.h>     /* memset */      
#include <sys/types.h>  /* sockaddr, SOCK_DGRAM , AF_INET */
#include <sys/socket.h> /* socket */
#include <netinet/in.h> 
#include <stdio.h>      /* perror */
#include <arpa/inet.h>  /* inet_addr */
#include <unistd.h>     /* sleep */
#include <stdlib.h>     /* atoi */

#define SIZE 1024

int main(int argc, char* argv[])
{
    int sock = 0;    
    struct sockaddr_in clientSin;
    char buffer[SIZE] = {0};
    char msg[SIZE] = "i am client #";
    ssize_t resBytes = 0;
    int i = 10;
    char* seq[] = {"0","1","2","3","4","5","6","7","8","9","10"};
    if(argc != 3)
    {
        printf("invalid parmeters\n");
    }

    memset(&clientSin, 0, sizeof(clientSin));

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1)
    {
        perror("fail in socket(client)");
        return 0;
    }

    clientSin.sin_family = AF_INET;
    clientSin.sin_addr.s_addr = inet_addr(argv[1]);
    clientSin.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr *)&clientSin, sizeof(clientSin)) < 0)
    {
        perror("fail in conect(client)");
        return 0;
    }
    
    printf("client conected\n");
    while(i--)
    {
        if(send(sock, msg, sizeof(msg), 0) < 0) /* if == 0 sleep() */
        {
            perror("fail in send(client)");
            return 0;
        }

        resBytes = recv(sock, buffer, sizeof(buffer), 0);
        if(resBytes == 0)
        {
            printf("prerepe for closing => server was close\n");
            sleep(2);
            close(sock);
            return 0;
        }
        else if(resBytes < 0)
        {
            perror("fail in recv(client)");
            return 0;
        }
        else
        {
            buffer[resBytes] = '\0';
            printf("client recive: %s\n", buffer);
        }
    }
    
    close(sock);
    
    return 0;
}