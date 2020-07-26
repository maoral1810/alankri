#include <string.h>     /* memset       */
#include <sys/types.h>  /* sockaddr, SOCK_DGRAM , AF_INET */
#include <sys/socket.h> /* socket       */
#include <netinet/in.h>
#include <stdio.h>     /* perror        */
#include <arpa/inet.h> /* inet_addr     */
#include <unistd.h>    /* sleep         */
#include <stdlib.h>    /* atoi ,rand    */
#include <time.h>      /* time(srand)   */

#define SIZE 32
#define CLIENTS_NUM 1000
#define DISCONNECTED 0

static int msgCount = 0;

int main(int argc, char *argv[])
{
    int sock = 0;
    int sockRes = 0;
    struct sockaddr_in clientSin;
    char buffer[SIZE] = {0};
    char msg[SIZE] = {0};
    int clients[CLIENTS_NUM] = {0};
    ssize_t resBytes = 0;
    size_t i = 0;
    int num = 0;

    if (argc != 3)
    {
        printf("invalid parmeters\n");
        return 0;
    }
    
    memset(&clientSin, 0, sizeof(clientSin));

    clientSin.sin_family = AF_INET;
    clientSin.sin_addr.s_addr = inet_addr(argv[1]);
    clientSin.sin_port = htons(atoi(argv[2]));
    srand(time(0));

    while (1)
    {
        num = (rand() % 100) + 1;
        
        if(clients[i] == DISCONNECTED)
        {
            if (num < 30)
            {
                sockRes = socket(AF_INET, SOCK_STREAM, 0);
                if (sockRes == -1)
                {
                    perror("fail in socket(client)");
                    clients[i] = DISCONNECTED;
                }
                
                else
                {
                    clients[i] = sockRes;
                    if(connect(clients[i], (struct sockaddr *)&clientSin, sizeof(clientSin)) < 0)
                    {
                        perror("failed to connect\n");
                    }
                    else
                    {
                        printf("client %ld is connect\n", i);
                    }
                }            
            }
        }

        else /* client coneceted allready*/
        {
            if(num <= 40) /*disconected client*/
            {
                printf("client is disconected! socket: %u\n",clients[i]);
                close(clients[i]);
                clients[i] = 0;
            }

            else if(num <= 80) /* send & rcv */
            {
                
                snprintf(msg,SIZE,"client %ld send: msg# %d", i ,msgCount++);
                if(send(clients[i], msg, strlen(msg), 0) > 0)
                {
                    printf("send msg from socket %d\n", clients[i]);
                }
                else
                {
                    close(clients[i]);
                    clients[i] = DISCONNECTED;
                    continue;
                }
                
                resBytes = recv(clients[i], buffer, sizeof(buffer) - 1, 0);
                if (resBytes > 0)
                {
                    buffer[resBytes] = '\0';
                    printf("client recive: %s\n", buffer);
                }
                else if (resBytes < 0)
                {
                    printf("fail to rcv to socket %d\n", clients[i]);
                }
            }
        }
        i = (i + 1) % CLIENTS_NUM;
    }

    printf("server was disconected! goodbye :)\n");
    return 0;
}

