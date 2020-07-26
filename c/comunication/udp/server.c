#include <string.h>     /* memset */      
#include <sys/types.h>  /* sockaddr, SOCK_DGRAM , AF_INET */
#include <sys/socket.h> /* socket */
#include <netinet/in.h> 
#include <stdio.h>      /* perror */
#include <arpa/inet.h>  /* inet_addr */

#define SIZE 32
#define PORT_NUM 1989

int main(void)
{
    struct sockaddr_in rcv;
    ssize_t resBytes = 0;
    ssize_t sendBytes = 0;
    char buffer[SIZE] = "send massege: server";
    socklen_t addrLen = sizeof(rcv);
    int sock = 0;
    memset(&rcv, 0, sizeof(rcv));
    
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock == -1)
    {
        perror("fail in socket");
        return 0;
    }
    
    rcv.sin_family = AF_INET;
    rcv.sin_addr.s_addr = INADDR_ANY;
    rcv.sin_port = htons(PORT_NUM);
    
    if(bind(sock,(struct sockaddr *)&rcv, sizeof(rcv)) < 0)
    {
        perror("fail in bind");
        return 0;
    }

    resBytes = recvfrom(sock ,buffer, sizeof(buffer), 0, ((struct sockaddr *)&rcv), &addrLen);
    if(resBytes < 0)
    {
        perror("recvfrom in server is fail");
        return 0;
    }
    else
    {
        printf("i recive message from %u message: %s\n",rcv.sin_addr.s_addr, buffer);
    }

    sendto(sock ,buffer, sizeof(uint16_t) * SIZE, 0, ((struct sockaddr *)&rcv), sizeof(rcv));
    if(sendBytes < 0)
    {
        perror("sendto in server is fail");
        return 0;
    }

    close(sock);
    return 0;  
}
