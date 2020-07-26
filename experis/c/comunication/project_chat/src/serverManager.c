#include <string.h>         /* memset       */      
#include <sys/socket.h>     /* socket       */
#include <netinet/in.h> 
#include <stdio.h>          /* perror       */
#include <stdlib.h>         /* malloc, free */
#include "ChatProtocol.h"   /* tags */
#include "ChatProtocolLimits.h"
#include "serverNet.h"
#include "serverManager.h"
#include "userManager.h"
#include "groupManager.h"
#include "list.h"
#include "list_itr.h"

#define MAGIC_NUM 0x18101989
#define MAGIC_DESTROY 0xDEADBEAF

struct Server
{
    size_t m_magicNumber;
    ServerNet* m_sn;
    GroupManager* m_Gruops;
    UserManager* m_users;
};

static short g_run = 1;

void CallBackFunc(int _socket, void* _msg, const void* _sManager);

Server *CreateServer()
{
    Server *server = (Server *)malloc(sizeof(server));

    if(NULL == server)
    {
        return NULL;
    }
    
    server->m_magicNumber = MAGIC_NUM;
    server->m_sn = CreateServerNet(SERVER_NET_PORT, CallBackFunc, server);
    if(NULL == server->m_sn)
    {
        free(server);
        return NULL;
    }

    server->m_users = CreateUserManager();
    if(NULL == server->m_users)
    {
        free(server->m_sn);
        free(server->m_users);
        return NULL;
    }

    return server;
}

ERR ServerRun(Server *_server)
{
    if(NULL != _server && MAGIC_NUM == _server->m_magicNumber)
    {
        return RunServerNet(_server->m_sn);
    }

    return UNINITIALIZE_VALUE;
}

ERR ServerStop(Server* _server)
{
    g_run = 0;
}

/*------------------------------- static functions --------------------------*/

void CallBackFunc(int _socket, void* _msg, const void* _sManager)
{
    unsigned char tag;
    char msgReplay[MAX_TOTAL_LEN_MSG] = {0};
    ssize_t sendRes = 0;
    ERR status;
    Server* serverManager = (Server*)_sManager;

    if(NULL == _msg)
    {
        /* disconnet client (by socket )*/
        return;
    }

    tag = *((char *)_msg);
    printf("tag = %d\n",tag);

    switch (tag)
    {
        case REGISTRATION:
        {
            RegRequest regReq;
            RegReply regReply;

            RegRequestUnpack(&regReq ,_msg);
            status = RegistretUser(serverManager->m_users, regReq.m_username, regReq.m_password, _socket);
                   
            if(status == USER_EXSIST)
            {
                regReply.m_requestStatus = (unsigned char)USERNAME_ALREADY_EXISTS;
                printf("USERNAME_ALREADY_EXISTS\n");
            }
            else if(status == ALLOCATION_FAILED)
            {
                regReply.m_requestStatus = (unsigned char)GENERAL_ERROR;
                printf("ALLOCATION_FAILED\n");
            }
            else
            {
                regReply.m_requestStatus = (unsigned char)OK;
                printf("REGISTRATION sucsses\n");     
            }

            RegReplyPack(&regReply, msgReplay);
            sendRes = send(_socket, msgReplay,msgReplay[1] + 2, 0);

            break;
        }

        case LOG_IN:
        {
            LogInRequest loginReq;
            LogInReply loginReply;

            LogInRequestUnpack(&loginReq, _msg);
            status = Login(serverManager->m_users, loginReq.m_username, loginReq.m_password, _socket);
            
            if(status == USER_NOT_EXSIST)
            {
                printf("login:user not exsist\n");
                loginReply.m_requestStatus = (unsigned char)USERNAME_DOESNT_EXIST;
            }
            else if (status == WRONG_PASS)
            {
                printf("login: Wrong password\n");
                loginReply.m_requestStatus = (unsigned char)WRONG_PASSWORD;
            }

            else if(status == USER_ACTIVE_ALLREADEY)
            {
                printf("login:USER_ALREADY_CONNECTED\n");
                loginReply.m_requestStatus = (unsigned char)USER_ALREADY_CONNECTED;
            }
            else
            {
                printf("login sucsses\n");
                loginReply.m_requestStatus = (unsigned char)OK;
            }

            LogInReplyPack(&loginReply, msgReplay);
            sendRes = send(_socket, msgReplay, msgReplay[1] + 2, 0);

            break;
        }

        case LOG_OUT:
        {
            LogOutRequest logOutReq;
            LogOutReply logOutReply;

            status = Logout(serverManager->m_users, logOutReq.m_username, _socket);
            
            if(status == USER_NOT_EXSIST)
            {
                logOutReply.m_requestStatus = (unsigned char)USERNAME_DOESNT_EXIST;
                LogOutReplyPack(&logOutReply, msgReplay);
            }
            else
            {
                logOutReply.m_requestStatus = (unsigned char)OK;
                LogOutReplyPack(&logOutReply, msgReplay);
            }
            
            sendRes = send(_socket, msgReplay, msgReplay[1] + 2, 0);
   
            break;
        } 

        case GET_GROUPS:
        {
            GetGrpsReply getGroups;
            FILE* fp = NULL;
            ERR status = GetActiveGroups(serverManager->m_Gruops,"groups");
            
            fp = fopen("groups", "r");
            if(NULL == fp || status == OPEN_FILE_FAILED)
            {
                getGroups.m_requestStatus = (unsigned char)GENERAL_ERROR;
            }
            else
            {
                getGroups.m_requestStatus = (unsigned char)OK;
            }
            fscanf(fp, "%s", getGroups.m_groupList);

            GetGrpsReplyPack(&getGroups, msgReplay);

            sendRes = send(_socket, msgReplay, msgReplay[1] + 2, 0);
  
            break;
        }

        case JOIN_GROUP:
        {
            JoinGrpRequest joinReq;
            JoinGrpReply joinReply;
            ERR status;

            JoinGrpRequestUnpack(&joinReq, _msg);
            
            status = AddToGroup(serverManager->m_Gruops,joinReq.m_groupName);
            if(status == GROUP_NOT_EXSIST)
            {
                joinReply.m_requestStatus = (unsigned char)GROUP_NOT_EXSIST;
            }

            JoinGroup(serverManager->m_users,joinReq.m_groupName, joinReq.m_username);
            if(status == USER_NOT_EXSIST)
            {
                joinReply.m_requestStatus = (unsigned char)USERNAME_DOESNT_EXIST;
            }
            JoinGrpReplyPack(&joinReply, msgReplay);
            sendRes = send(_socket, msgReplay, msgReplay[1] + 2 , 0);
            break;
        }

        case LEAVE_GROUP:
        {
            LeaveGrpRequest leaveReq;
            LeaveGrpReply leaveReply;
            ERR status;

            LeaveGrpRequestUnpack(&leaveReq, _msg);

            status = LeaveGroup(serverManager->m_Gruops, leaveReq.m_groupName);
            if(status == GROUP_NOT_EXSIST)
            {
                leaveReply.m_requestStatus = (unsigned char)GROUP_NOT_EXSIST;
            }

            status = UserLeaveGroup(serverManager->m_users, leaveReq.m_groupName, leaveReq.m_username);
            if(status == USER_NOT_EXSIST)
            {
                leaveReply.m_requestStatus = (unsigned char)USER_NOT_EXSIST;
            }
            else if(status == GROUP_NOT_EXSIST)
            {
                leaveReply.m_requestStatus = (unsigned char)GROUP_NOT_EXSIST;
            }
            else
            {
                leaveReply.m_requestStatus = (unsigned char)OK;
            }

            LeaveGrpReplyPack(&leaveReply, msgReplay);
            sendRes = send(_socket, msgReplay, msgReplay[1] + 2 , 0);
            break;
        } 
        
        default:
            break;
    }
}



