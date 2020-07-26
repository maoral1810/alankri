/* debug */
#include <stdio.h> /* printf */

#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* strcpy, strlen */
#include "UI.h"
#include "clientManager.h"
#include "clientNet.h"
#include "chatMan.h"

/* #include "clientGroupManager.h" */
#include "ChatProtocol.h"
#include "ChatProtocolLimits.h"

#define MAGIC_NUM 0x18101989
#define MAGIC_DESTROY 0xDEADBEAF
#define FALSE 0
#define TRUE !FALSE

/* static functions */
static ERR ClientReg(ClientManager* _manager);
static ERR ClientLogin(ClientManager* _manager);
static ERR ClientJoinGroup(ClientManager* _manager);
static ERR GetGroups(ClientManager* _manager,char* _groups);

static int g_terminate = FALSE;

struct ClientManager
{
    size_t      m_magicNumber;
    ClientNet*  m_clientNet;
    char*       m_clientName;
    ChatMan*    m_ChatMan;

/*     CGroupManager* m_clientGroups; */
};

ClientManager* ClientManagerCreate(const char* _ip, const char* _port)
{
    ClientManager* Cmanager = (ClientManager*)malloc(sizeof(ClientManager));

    if(NULL == Cmanager)
    {
        return NULL;
    }
    
/*     Cmanager->m_clientGroups = CreateCGroupManager();
    if(NULL == Cmanager->m_clientGroups)
    {
        free(Cmanager);
        return NULL;
    } */

    Cmanager->m_clientNet = ClientNetCreate(_ip, atoi(_port));
    if(NULL == Cmanager->m_clientNet)
    {
/*         CGroupManagerDestroy(Cmanager->m_clientGroups); */
        free(Cmanager);
        return NULL;
    }

    Cmanager->m_clientName = (char*) malloc(sizeof(char)*(MAX_LEN_USERNAME +1));
    if(NULL == Cmanager->m_clientName)
    {
        ClientNetDestroy(Cmanager->m_clientNet);
        free(Cmanager);
        return NULL;
    }

    Cmanager->m_ChatMan = ChatManCreate();
    if(NULL == Cmanager->m_ChatMan)
    {
        ClientNetDestroy(Cmanager->m_clientNet);
        free(Cmanager->m_clientName);
        free(Cmanager);
        return NULL;
    }
    Cmanager->m_magicNumber = MAGIC_NUM;

    return Cmanager;
}


void ClientManagerCreateDestroy(ClientManager* _manager)
{
    if(_manager != NULL && MAGIC_NUM == _manager->m_magicNumber)
    {
/*         CGroupManagerDestroy(_manager->m_clientGroups); */
        _manager->m_magicNumber = MAGIC_DESTROY; 
        ClientNetDestroy(_manager->m_clientNet);
        free(_manager->m_clientName);
        free(_manager);
    }
}

ERR ClientManagerRun(ClientManager* _manager)
{
    ERR status = ERR_OK;
    int loginFlag = FALSE;
    char msgRep[MAX_TOTAL_LEN_MSG+1];

    status = CilentNetConnect(_manager->m_clientNet);
	if (status == CONNECTION_FAILED)
	{
		PrintStatus(CONNECTION_FAILED);
		return;
	}

    while (!g_terminate)
    {
        if (!loginFlag)
        {
            switch (WelcomeMenuGetSelection())
            {
                case CLIENT_REGITRATE:
                {
                    status = ClientReg(_manager);
                    printf("Client Registrasion: ");
                    PrintStatus(status);
                    break;
                }   

                case CLIENT_LOGIN:
                {
                    loginFlag = ClientLogin(_manager);
                    printf("Client login: ");
                    PrintStatus(status);
                    if(status == ERR_OK)
                    {
                        loginFlag = TRUE;
                    }
                    break;
                }

                case EXIT:
                {
                    printf("GOOD BYE :)\n");
                    g_terminate = TRUE;
                    break;
                }
            }
        }
        else
        {
            switch (HomeMenuGetSelection())
            {
                case CLIENT_JOIN_GROUP:
                {
                    char groupName[MAX_LEN_GROUP_NAME +1];
                    int port = -1;
                    char Ip[MAX_LEN_IP];
                    status = GetGroups(_manager,msgRep);
                    if(status != ERR_OK)
                    {
                        PrintStatus(status);
                    }
                    printf("groups in sys: %s\n",msgRep);
                    printf("enter group name: ");
                    getchar();
                    fgets(groupName, MAX_LEN_GROUP_NAME, stdin);

                    status = joinGroup(_manager,groupName);
                    /*get port and ip from server*/
                    ChatManOpenChat(_manager->m_ChatMan,Ip,port,_manager->m_clientName);
                    /*TODOCHAT*/
                    /* OpenChat(groupName); */
                    break;
                }

                case CLIENT_LEAVE_GROUP:
                {
                
                    break;
                }	

                case CLIENT_GET_GROUPS:
                {
                    break;
                }

                case CLIENT_LOGUOT:
                {
                    break;
                }

                default: printf("invaid input, please try again\n");
            }  
        }
    }
}

/* ------------------- static functions -----------------*/
static ERR ClientReg(ClientManager* _manager)
{
    int status = -1;
    char msg[MAX_LEN_USERNAME + MAX_LEN_PASSWORD + 3]; /*maxSize of pass and name +one char for type and 2 chars for length of pass and name*/
    char userName [MAX_LEN_USERNAME];
    char password [MAX_LEN_PASSWORD];

    RegRequest cliData;
    RegReply cilReply;

    GetInput("User Name", userName, MAX_LEN_USERNAME - 1, '#');
    GetInput("Password", password, MAX_LEN_PASSWORD - 1, '#');
    strcpy(_manager->m_clientName,userName); 

    strncpy(cliData.m_username, userName, strlen(userName));
    strncpy(cliData.m_password, password, strlen(password));
    cliData.m_username[strlen(userName)] = '\n';
    cliData.m_password[strlen(password)] = '\n';


    printf("user name = %s\n",userName);
    printf("password = %s\n", password);
    /*here prob*/
    password[strlen(password)] = '\0';
    printf("user name = %s\n",cliData.m_username);
    printf("password = %s\n", cliData.m_password);
    printf("passeord len = %lu\n", strlen(cliData.m_password));
    printf("passeord len = %lu\n", strlen(password));

    
    status =   RegRequestPack(&cliData, msg);
    status =   ClientNetSend(msg, msg[1] + 1, _manager->m_clientNet);
    if(status)
    {
        return status;
    }
    msg[0] = '\0';
    
    status = ClientNetRecive(msg, _manager->m_clientNet);
    RegRequestUnpack(&cliData , msg);

    if(cilReply.m_requestStatus == REGISTRATION)
    {
        printf("registration success \n");
    }
    
    return ERR_OK;
}

static ERR ClientLogin(ClientManager* _manager)
{
    char msg[MAX_TOTAL_LEN_MSG];
    LogInRequest logIn;
    LogInReply reply;
    ProtocolStatus stat;
    ERR sendStat;
    char userName [MAX_LEN_USERNAME];
    char password [MAX_LEN_PASSWORD];
    
    GetInput("User Name", userName, MAX_LEN_USERNAME, '#');
    GetInput("Password", password, MAX_LEN_PASSWORD, '#');
    
    /* pack struct */
    strcpy(logIn.m_username, userName);
    strcpy(logIn.m_password, password);
    logIn.m_usernameLen = strlen(userName);
    logIn.m_passwordLen = strlen(password);

    printf("LogIn in prog\n");
    stat = LogInRequestPack(&logIn,msg);
    if(stat)
    {
        printf("CONNECTION_FAILED\n");
        return CONNECTION_FAILED;
    }
    
    sendStat = ClientNetSend(msg,msg[1],_manager->m_clientNet);
    if(sendStat)
    {
        printf("SEND_FAILED\n");
        return sendStat;
    }
    
    sendStat = ClientNetRecive(msg, _manager->m_clientNet);
    if(sendStat)
    {
        printf("RECV_FAILED\n");
        return sendStat;
    }
    
    sendStat = LogInReplyUnpack(&reply, msg);
    if(sendStat)
    {
        return ACCEPT_FAILED;
    }
    
    return ERR_OK;
}

static ERR GetGroups(ClientManager* _manager,char* _groups)
{
    GetGrpsReply* reply;
    char msg[MAX_TOTAL_LEN_MSG];
    ERR sendStat;
    GetGrpsRequest gr;
    /*fill struct*/
    strcpy(gr.m_username,_manager->m_clientName);
    GetGrpsRequestPack(&gr,msg);
    
    /*send struct*/
    sendStat = ClientNetSend(msg,msg[1],_manager->m_clientNet);
    if(sendStat)
    {
        printf("RECV_FAILED\n");
        return sendStat;
    }
    /*reciv msg*/
    strcpy(gr.m_username,"");

    sendStat = ClientNetRecive(msg, _manager->m_clientNet);
    if(sendStat)
    {
        printf("RECV_FAILED\n");
        return sendStat;
    }
    sendStat = GetGrpsReplyPack(reply, msg);
    if(sendStat || reply->m_requestStatus != OK )
    {
        return ACCEPT_FAILED;
    }
    strcpy(_groups,reply->m_groupList);

    return ERR_OK;     
}


static ERR joinGroup(ClientManager* _manager,char* _groupName)
{
    JoinGrpRequest request;
    JoinGrpReply reply;
    char msg[MAX_TOTAL_LEN_MSG];
    RequestStatus REQstat = OK;
    ERR ERRStat = ERR_OK;

    strcpy(request.m_groupName,_groupName);
    request.m_groupNameLen = strlen(_groupName);
    strcpy(request.m_username,_manager->m_clientName);
    request.m_usernameLen = strlen(_manager->m_clientName);

    REQstat = JoinGrpRequestPack(&request,msg);
    if(!REQstat)
    {
        return SENDING_FAILED;
    }
    ERRStat = ClientNetSend(&msg,strlen(msg),_manager->m_clientNet);
    if(!ERRStat)
    {
        PrintStatus(ERRStat);
        return ERRStat;
    }
    REQstat = JoinGrpReplyPack(&reply,msg);
    if(!REQstat)
    {
        ERRStat = RECIVE_FAILED;
        PrintStatus(ERRStat);
        return ERRStat;
    }
    /*push 2 group DS*/

}










