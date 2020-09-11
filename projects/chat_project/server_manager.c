#include <stdlib.h>
#include <assert.h>
#include "server_manager.h"
#include "chat_protocol.h"
#include "chat_protocol_limits.h"
#include "users_manager.h"
#include "server_network.h"
#include "group_manager.h"

#define MAGIC_NUMBER 0xBEEFBEEF
#define MAGIC_NUMBER_AFTER_DESTROY 0xDEADBEEF

#define GROUPS_FILE_NAME "groups.txt"

static void RegistrationSendReply(ServerManager* _manager, const char* _requestMsg, int _srcFD);
static void LogInSendReply(ServerManager* _manager, const char* _requestMsg, int _srcFD);
static void RecevieRequest(const void* _activator, const char* _requestMsg, int _srcFD);
static void GetGroupsSendReply(ServerManager* _manager, const char* _requestMsg, int _srcFD);
static void JoinGroupSendReply(ServerManager* _manager, const char* _requestMsg, int _srcFD);
static void LeaveGroupSendReply(ServerManager* _manager, const char* _requestMsg, int _srcFD);
static void CreateGroupSendReply(ServerManager* _manager, const char* _requestMsg, int _srcFD);
static size_t CalcSizeOfFile(FILE* _file);
static void itoaPort(int _port, char* _str);
static int CalcDigits(int _num);
static int sendAll(ServerManager* _serverManager, const char* _buffer, int _FD, size_t _length);

struct ServerManager
{
	size_t m_magicNumber;
	UsersManager* m_userMang;
	ServerNet* m_serverNet;
	GroupManager* m_groupMang;
};

ServerManager* ServerManagerCreate(int _port)
{
	ServerManager* _serverMang = (ServerManager*)malloc(sizeof(ServerManager));
	if(_serverMang)
	{
		_serverMang->m_serverNet = ServerNetCreate(_port, RecevieRequest, _serverMang);
		if(!_serverMang->m_serverNet)
		{
			free(_serverMang);
			return NULL;
		}
		_serverMang->m_userMang = UsersManagerCreate();
		if(!_serverMang->m_userMang)
		{	
			free(_serverMang->m_serverNet);
			free(_serverMang);
			return NULL;
		}
		_serverMang->m_groupMang = GroupManagerCreate(_port);
		if(!_serverMang->m_groupMang)
		{
			free(_serverMang->m_userMang);
			free(_serverMang->m_serverNet);
			free(_serverMang);
			return NULL;			
		}
		_serverMang->m_magicNumber = MAGIC_NUMBER;
	}
	return _serverMang;
}

void ServerManagerRun(ServerManager* _manager)
{
	if(_manager && _manager->m_magicNumber == MAGIC_NUMBER)
	{
		ServerNetRun(_manager->m_serverNet);
	}
}

void ServerManagerDestroy (ServerManager* _manager)
{
	if(_manager && _manager->m_magicNumber == MAGIC_NUMBER)
	{
		_manager->m_magicNumber = MAGIC_NUMBER_AFTER_DESTROY;
		GroupManagerDestroy(_manager->m_groupMang);
		UserManagerDestroy(_manager->m_userMang);
		ServerNetDestroy(_manager->m_serverNet);
		free(_manager);
	}
}

static void RecevieRequest(const void* _activator, const char* _requestMsg, int _srcFD)
{
	ServerManager* _manager = (ServerManager*)_activator;
	char groupName[MAX_LEN_GROUP_NAME];
	char username[MAX_LEN_USERNAME];
	Tag tag;
	if(!_manager || _manager->m_magicNumber != MAGIC_NUMBER)
	{
		return;
	}
	if(!_requestMsg)
	{
		if(UserManagerGetUsername(_manager->m_userMang, _srcFD, username) == USER_OK)
		{
			while(UserManagerPopGroup(_manager->m_userMang, username, groupName) == USER_OK)
			{
				GroupManagerRemoveFromGroup(_manager->m_groupMang, groupName);
			}
			UsersManagerLogOut(_manager->m_userMang, username, _srcFD);
		}
		return;
	}
	tag = (Tag)_requestMsg[TAG_INDEX];
	switch (tag)
	{
		case REGISTRATION:
			RegistrationSendReply(_manager, _requestMsg, _srcFD);
			break;
		case LOG_IN:
			LogInSendReply(_manager, _requestMsg, _srcFD);
			break;
		case GET_GROUPS:
			GetGroupsSendReply(_manager, _requestMsg, _srcFD);
			break;
		case CREATE_GROUP:
			CreateGroupSendReply(_manager, _requestMsg, _srcFD);
		case JOIN_GROUP:
			JoinGroupSendReply(_manager, _requestMsg, _srcFD);
			break;
		case LEAVE_GROUP:
			LeaveGroupSendReply(_manager, _requestMsg, _srcFD);
			break;
		/*case LOG_OUT:
			LogOutReply(_manager, _requestMsg, _srcFD);
			break;*/
	}
}

static void RegistrationSendReply(ServerManager* _manager, const char* _requestMsg, int _srcFD)
{
	char msgReply[MAX_TOTAL_LEN_MSG];
	RegRequest requestStruct;
	RegReply replyStruct;
	UserManagerResult result;
	RegRequestUnpack(&requestStruct, _requestMsg);
	result = UsersManagerRegistration(_manager->m_userMang, requestStruct.m_username, requestStruct.m_password);
	switch(result) /*What if allocation failed?*/
	{
		case USER_OK:
			replyStruct.m_requestStatus = (unsigned char)OK;
			break;
		case USERNAME_EXIST_ERROR:
			replyStruct.m_requestStatus = (unsigned char)USERNAME_ALREADY_EXISTS;
			break;
		default:
			replyStruct.m_requestStatus = (unsigned char)GENERAL_ERROR;
			break;
	}
	RegReplyPack(&replyStruct, msgReply);
	ServerNetReply(_manager->m_serverNet, msgReply, _srcFD, msgReply[LEN_INDEX] + VAL_INDEX);
}

static void LogInSendReply(ServerManager* _manager, const char* _requestMsg, int _srcFD)
{
	char msgReply[MAX_TOTAL_LEN_MSG];
	LogInRequest requestStruct;
	LogInReply replyStruct;
	UserManagerResult result;
	LogInRequestUnpack(&requestStruct, _requestMsg);
	result = UsersManagerLogIn(_manager->m_userMang, requestStruct.m_username, requestStruct.m_password, _srcFD);
	switch(result)
	{
		case USER_OK:
			replyStruct.m_requestStatus = (unsigned char)OK;
			break;
		case USERNAME_NOT_EXIST_ERROR:
			replyStruct.m_requestStatus = (unsigned char)USERNAME_DOESNT_EXIST;
			break;
		case USER_PASSWORD_NOT_MATCH_ERROR:
			replyStruct.m_requestStatus = (unsigned char)WRONG_PASSWORD;
			break;
		case USER_ALREADY_CONNECTED:
			replyStruct.m_requestStatus = (unsigned char)USER_ALREADY_CONNECTED;
			break;
		default:
			replyStruct.m_requestStatus = (unsigned char)GENERAL_ERROR;
			break;
	}
	LogInReplyPack(&replyStruct, msgReply);
	ServerNetReply(_manager->m_serverNet, msgReply, _srcFD, msgReply[LEN_INDEX] + VAL_INDEX);	
}

static void GetGroupsSendReply(ServerManager* _manager, const char* _requestMsg, int _srcFD)
{
	FILE* fileOfGroupsNames;
	char replyBuffer[MAX_TOTAL_LEN_MSG + 1];
	char tempStr[MAX_LEN_GROUP_NAME + 1]; 
	GetGrpsRequest requestStruct;
	GetGrpsReply replyStruct;
	GroupManagerResult resultGroupMang;
	size_t fileLength;

	char rcvBuffer[MAX_TOTAL_LEN_MSG + 1];


	assert(PROTOCOL_SUCCESS == GetGrpsRequestUnpack(&requestStruct, _requestMsg));
	resultGroupMang = GroupManagerGetGroups(_manager->m_groupMang, GROUPS_FILE_NAME);
	if(resultGroupMang == GROUP_OK && (fileOfGroupsNames = fopen(GROUPS_FILE_NAME, "r")))
	{
		fileLength = CalcSizeOfFile(fileOfGroupsNames);

		if(!fileLength)
		{
			replyStruct.m_requestStatus = NO_GROUPS;
			replyStruct.m_totalPayloadsLen = fileLength;

			fclose(fileOfGroupsNames);
		}
		else
		{	
			char* groupsBuffer = (char*)calloc(1, fileLength + 1);
			if(groupsBuffer == NULL) {
				replyStruct.m_requestStatus = GENERAL_ERROR;
				replyStruct.m_totalPayloadsLen = 0;
				fclose(fileOfGroupsNames);
			}
			else 
			{
				size_t lineSize = 0;
				char* tempBuffer = NULL;
				size_t tempBufferSize = 0;

				replyStruct.m_requestStatus = OK;
				replyStruct.m_totalPayloadsLen = fileLength;

				while ((lineSize = getline(&tempBuffer, &tempBufferSize, fileOfGroupsNames)) != -1)
				{
					if(tempBuffer == NULL) {
						break;
					}
					strcat(groupsBuffer, tempBuffer);
				}
				
				GetGrpsReplyPack(&replyStruct, replyBuffer);
				
				printf("reply buffer tag = %d \n", replyBuffer[TAG_INDEX]);

				ServerNetReply(_manager->m_serverNet, replyBuffer, _srcFD, replyBuffer[LEN_INDEX] + VAL_INDEX);
				
				/* */
				sendAll(_manager, groupsBuffer, _srcFD, fileLength);
				free(groupsBuffer);
				if(tempBuffer != NULL) {
					free(tempBuffer);
				}
				
				fclose(fileOfGroupsNames);
				return;	
			}
		}
	}
	else
	{	
		replyStruct.m_requestStatus = GENERAL_ERROR;
		replyStruct.m_totalPayloadsLen = 0;

	}

	GetGrpsReplyPack(&replyStruct, replyBuffer);
	ServerNetReply(_manager->m_serverNet, replyBuffer, _srcFD, replyBuffer[LEN_INDEX] + VAL_INDEX);
}

static void CreateGroupSendReply(ServerManager* _manager, const char* _requestMsg, int _srcFD)
{
	char msgReply[MAX_TOTAL_LEN_MSG];
	char groupIP[MAX_LEN_IP + 1];
	int groupPort;
	CreateGrpRequest requestStruct;
	CreateGrpReply replyStruct;
	UserManagerResult resultUserMang;
	GroupManagerResult resultGroupMang;
	CreateGrpRequestUnpack(&requestStruct, _requestMsg);
	resultGroupMang = GroupManagerCreateGroup(_manager->m_groupMang, requestStruct.m_groupName, groupIP, &groupPort);
	switch(resultGroupMang)
	{
		case GROUP_EXIST:
			replyStruct.m_requestStatus = GROUP_ALREADY_EXISTS;
			replyStruct.m_mcastIPLen = 0;
			replyStruct.m_mcastPortLen = 0;
			break;
		case GROUP_MAX_ERROR:
			replyStruct.m_requestStatus = MAX_GROUP_ERROR;
			replyStruct.m_mcastIPLen = 0;
			replyStruct.m_mcastPortLen = 0;
			break;
		case GROUP_OK:
			if(UserManagerAddGroup(_manager->m_userMang, requestStruct.m_username, requestStruct.m_groupName) == USER_OK)
			{
				replyStruct.m_requestStatus = OK;
				replyStruct.m_mcastIPLen = strlen(groupIP);
				strncpy(replyStruct.m_mcastIP, groupIP, replyStruct.m_mcastIPLen);
				replyStruct.m_mcastPortLen = CalcDigits(groupPort);
				itoaPort(groupPort,replyStruct.m_mcastPort);
				break;
			}
		default:
			replyStruct.m_requestStatus = GENERAL_ERROR;
			replyStruct.m_mcastIPLen = 0;
			replyStruct.m_mcastPortLen = 0;
	}
	CreateGrpReplyPack(&replyStruct, msgReply);
	ServerNetReply(_manager->m_serverNet, msgReply, _srcFD, msgReply[LEN_INDEX] + VAL_INDEX);
}

static void JoinGroupSendReply(ServerManager* _manager, const char* _requestMsg, int _srcFD)
{
	char msgReply[MAX_TOTAL_LEN_MSG];
	char groupIP[MAX_LEN_IP + 1];
	int groupPort;
	JoinGrpRequest requestStruct;
	JoinGrpReply replyStruct;
	UserManagerResult resultUserMang;
	GroupManagerResult resultGroupMang;
	JoinGrpRequestUnpack(&requestStruct, _requestMsg);
	resultGroupMang = GroupManagerAddToGroup(_manager->m_groupMang, requestStruct.m_groupName, groupIP, &groupPort);
	if(resultGroupMang == GROUP_NOT_EXIST)
	{
		replyStruct.m_requestStatus = GROUP_DOESNT_EXIST;
		replyStruct.m_mcastIPLen = 0;
		replyStruct.m_mcastPortLen = 0;
	}
	else
	{
		if(UserManagerAddGroup(_manager->m_userMang, requestStruct.m_username, requestStruct.m_groupName) != USER_OK)
		{
			replyStruct.m_requestStatus = GENERAL_ERROR;
			replyStruct.m_mcastIPLen = 0;
			replyStruct.m_mcastPortLen = 0;
		}
		else
		{
			replyStruct.m_requestStatus = OK;
			replyStruct.m_mcastIPLen = strlen(groupIP);
			strncpy(replyStruct.m_mcastIP, groupIP, replyStruct.m_mcastIPLen);
			replyStruct.m_mcastPortLen = CalcDigits(groupPort);
			itoaPort(groupPort,replyStruct.m_mcastPort);
		}
	}
	JoinGrpReplyPack(&replyStruct, msgReply);
	ServerNetReply(_manager->m_serverNet, msgReply, _srcFD, msgReply[LEN_INDEX] + VAL_INDEX);
}

static void LeaveGroupSendReply(ServerManager* _manager, const char* _requestMsg, int _srcFD)
{
	char msgReply[MAX_TOTAL_LEN_MSG];
	LeaveGrpRequest requestStruct;
	LeaveGrpReply replyStruct;
	GroupManagerResult groupResult;
	UserManagerResult userResult;
	LeaveGrpRequestUnpack(&requestStruct, _requestMsg);
	if(GroupManagerRemoveFromGroup(_manager->m_groupMang, requestStruct.m_groupName) == GROUP_OK &&
	  UserManagerRemoveGroup(_manager->m_userMang, requestStruct.m_username, requestStruct.m_groupName) == USER_OK)
	{
		replyStruct.m_requestStatus = (unsigned char)OK;
	}
	else
	{
		replyStruct.m_requestStatus = (unsigned char)LEAVE_FAILED;
	}
	LeaveGrpReplyPack(&replyStruct, msgReply);
	ServerNetReply(_manager->m_serverNet, msgReply, _srcFD, msgReply[LEN_INDEX] + VAL_INDEX);	
}

static size_t CalcSizeOfFile(FILE* _file)
{
	size_t fileLength;
	size_t currentPosition = ftell(_file);

	fseek(_file, 0, SEEK_END);
	fileLength = ftell(_file);
	fseek(_file, currentPosition, SEEK_SET);

	return fileLength;
}

static void itoaPort(int _port, char* _str)
{ 
    int i = CalcDigits(_port) - 1; 
    while(i >= 0)
    { 
        _str[i--] = _port % 10 + '0'; 
        _port /= 10;
    }
}

static int CalcDigits(int _num)
{
	int digits = 1;
	while(_num/10)
	{
		digits++;
		_num /= 10;
	}
	return digits;
}

static int sendAll(ServerManager* _serverManager, const char* _buffer, int _FD, size_t _length)
{
    const char* ptr = _buffer;
	int bytesSent = 0;

    while(_length > 0)
    {
        bytesSent = ServerNetReply(_serverManager->m_serverNet, ptr, _FD, _length);
        if (bytesSent < 1) {
			break;
		}
        ptr += bytesSent;
        _length -= bytesSent;
    }

    return bytesSent;
}