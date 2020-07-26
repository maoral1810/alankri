#include <string.h>     /* memset */      
#include <sys/types.h>  /* sockaddr, SOCK_DGRAM , AF_INET */
#include <sys/socket.h> /* socket */
#include <netinet/in.h> 
#include <stdio.h>      /* perror */
#include <arpa/inet.h>  /* inet_addr */

#define SIZE 1024
#define PORT_NUM 1958

int main(void)
{
    /* sendto*/
    struct sockaddr_in sin;
    ssize_t sendBytes = 0;
    ssize_t rcvBytes = 0;
    socklen_t addrLen = sizeof(sin);
    char buffer[SIZE] = "send massege: shay is fat";
    int sock = 0;
    memset(&sin, 0, sizeof(sin));

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock == -1)
    {
        perror("fail in socket");
        return 0;
    }

    sin.sin_family = AF_INET;
/*     sin.sin_addr.s_addr = inet_addr("127.0.0.1"); */
    sin.sin_addr.s_addr = inet_addr("192.168.0.17");
    sin.sin_port = htons(PORT_NUM);
    
    sendBytes = sendto(sock ,buffer, sizeof(buffer), 0, ((struct sockaddr *)&sin), sizeof(sin));
    if(sendBytes < 0)
    {
        perror("sendto in client is fail");
        return 0;
    }

    rcvBytes = recvfrom(sock ,buffer, sizeof(buffer), 0, ((struct sockaddr *)&sin), &addrLen);
    if(rcvBytes < 0)
    {
        perror("recvfrom in client fail");
        return 0;
    }
    else
    {
        printf("i recive message from %u message: %s\n",sin.sin_addr.s_addr, buffer);
    }

    close(sock);
    return 0;   
}

