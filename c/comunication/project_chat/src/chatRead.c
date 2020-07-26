#include <stdio.h> /*openfile*/
#include <sys/types.h>/*pid*/
#include <unistd.h>/*pid*/
#include <sys/socket.h>  /*sockfd*/
#include <netinet/in.h> /*sockaddr_in*/
#include <sys/types.h>  /*bind , sockaddr*/
#include <netinet/ip.h> /*ip_mreq*/
#include <stdlib.h>/*atoi*/
#include <string.h>
#include <arpa/inet.h>
#include "ChatProtocolLimits.h"
/*first args:
ip
port
username
file
*/
/*MultiCastAdd.sin_addr.s_addr = _Ip;*/
void ReadConnect(const char* _Ip, int _Port,const char* _uName);

int main(int argc, char const *argv[]) 
{
    FILE *fp;
    pid_t pid;
    int port = -1;

    if(argc < 5)
    {
        printf("not enough arguments");
        return 0;
    }

    if((pid = getpid()) <= 0)
    {
        perror("pid failed");
        return 1;
    }

    fp = fopen(argv[3],"w+");
    if(fp == NULL)
    {
        perror("file open failed");
        return 1;
    }
    fprintf(fp,"%d",pid);
    fclose(fp);

    port = atoi(argv[2]);
    ReadConnect(argv[1] , port , argv[4]);

    return 0;
}

void ReadConnect(const char* _Ip, int _Port,const char* _uName)
{
    int socketId;
     size_t yes = 1; 
    struct sockaddr_in MultiCastAdd;
    struct ip_mreq     mreq;
    char buff[MAX_TOTAL_LEN_MSG];
    size_t byteRead = 0;
    socklen_t len = sizeof(MultiCastAdd);



    socketId = socket(AF_INET, SOCK_DGRAM, 0);
    if(socketId < 0)
    {
        perror("socket failed");
        return;
    }

    memset(&MultiCastAdd, 0, sizeof(MultiCastAdd));
    MultiCastAdd.sin_family      = AF_INET; 
    MultiCastAdd.sin_addr.s_addr = inet_addr(_Ip); 
    MultiCastAdd.sin_port        = htons(_Port);


    memset(&mreq, 0, sizeof(mreq));
    mreq.imr_multiaddr = MultiCastAdd.sin_addr;
    mreq.imr_interface.s_addr = INADDR_ANY;

    if( (setsockopt (socketId, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq))) < 0)
    {
        perror("setsockopt failed");
        close(socketId);
        return;
    }

     if (setsockopt(socketId, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0) {
         perror("reuseaddr setsockopt");
         exit(1);
     }

    if( (bind(socketId,(struct sockaddr*) &MultiCastAdd,sizeof(MultiCastAdd))) < 0 )
    {
        perror("bind failed"); 
        return;
    }

  
    printf(" Read only! \n\n");
    while (1)
    {
        byteRead = recvfrom(socketId, buff, MAX_TOTAL_LEN_MSG -1 , 0,(struct sockaddr *)&MultiCastAdd , &len);
        buff[byteRead] ='\0';
        printf("%s : %s",_uName,buff);
    }
    
}
