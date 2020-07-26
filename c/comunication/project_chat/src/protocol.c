#include <string.h> /*strlen*/
#include <stdlib.h>   /*malloc*/
#include "ChatProtocolLimits.h"
#include "ChatProtocol.h"

/*********************** registration ***************************************************/
ProtocolStatus RegRequestPack (const RegRequest* _request, char* _msg)
{
	unsigned char nameSize = (char) strlen(_request->m_username);
	unsigned char passSize = (char) strlen(_request->m_password);

	_msg[0] = (char)REGISTRATION;
	_msg[1]	= (char)(strlen(_request->m_username)+strlen(_request->m_password)+2);
	_msg[2]	= nameSize;
	strcpy(_msg+3,_request->m_username);
	_msg[3+nameSize] = passSize;
	strcpy(_msg+nameSize+4,_request->m_password);

	return OK;
}

ProtocolStatus RegRequestUnpack (RegRequest* _request, const char* _msg)
{
	int nameSize = (int) _msg[2];
	int passSize = (int) _msg[3 + nameSize]; /*make sure index OK*/
	memcpy(_request->m_username,&_msg[3],nameSize);
	_request->m_username[nameSize] = '\0';
	memcpy(_request->m_password,&_msg[nameSize + 4],passSize);
	_request->m_password[passSize] = '\0';

	return OK;
}

ProtocolStatus RegReplyPack (const RegReply* _reply, char* _msg)
{
	_msg[0] = (char)REGISTRATION;
	_msg[1] = (char)1;
	_msg[2] = _reply->m_requestStatus; /*reply is only one char*/
	_msg[3] = '\0';

	return OK;
}

ProtocolStatus RegReplyUnpack (RegReply* _reply, const char* _msg)
{
	_reply->m_requestStatus = _msg[2];
	return OK;
}

/*********************** log_in ***************************************************/
ProtocolStatus LogInRequestPack (const LogInRequest* _request, char* _msg)
{
	unsigned char nameSize = (char) strlen(_request->m_username);
	unsigned char passSize = (char) strlen(_request->m_password);

	_msg[0] = (char)LOG_IN;
	_msg[1]	= (char)(strlen(_request->m_username)+strlen(_request->m_password)+2);
	_msg[2]	= nameSize;
	strcpy(_msg+3,_request->m_username);
	_msg[3+nameSize] = passSize;
	strcpy(_msg+4+nameSize,_request->m_password);

	return OK;
}

ProtocolStatus LogInRequestUnpack (LogInRequest* _request, const char* _msg)
{
	int nameSize = (int) _msg[2];
	int passSize = (int) _msg[2 + nameSize]; /*make sure index OK*/
	memcpy(_request->m_username,&_msg[3],nameSize);
	_request->m_username[nameSize] = '\0';
	memcpy(_request->m_password,&_msg[nameSize + 4],passSize);
	_request->m_password[passSize] = '\0';

	return OK;
}


ProtocolStatus LogInReplyPack (const LogInReply* _reply, char* _msg)
{
	_msg[0] = (char)LOG_IN;
	_msg[1] = (char)1;
	_msg[2] = _reply->m_requestStatus; /*reply is only one char*/
	_msg[3] = '\0';

	return OK;
}


ProtocolStatus LogInReplyUnpack (LogInReply* _reply, const char* _msg)
{
	_reply->m_requestStatus = _msg[2];
	return OK;
}

/*********************** LogOut ***************************************************/

ProtocolStatus LogOutRequestPack (const LogOutRequest* _request, char* _msg)
{
	_msg[0] = (char)LOG_OUT;
	_msg[1] = (char)strlen(_request->m_username);
	strcpy(_msg + 2 , _request->m_username);
	return OK;
}

ProtocolStatus LogOutRequestUnpack (LogOutRequest* _request, const char* _msg)
{
	memcpy(_request->m_username,&_msg[2],_msg[1]);
	_request->m_username[_msg[1]] = _msg[1];
	return OK;
}

ProtocolStatus LogOutReplyPack (const LogOutReply* _reply, char* _msg)
{
	LogOutReply rep;
	_msg[0] = (char)LOG_OUT;
	_msg[1] = (char)1;
	_msg[2] = _reply->m_requestStatus;
	return OK;
}

ProtocolStatus LogOutReplyUnpack (LogOutReply* _reply, const char* _msg)
{
	_reply->m_requestStatus = _msg[2];
	return OK;
}

/*********************--JoinGroup--**********************/
ProtocolStatus JoinGrpRequestPack (const JoinGrpRequest* _request, char* _msg)
{
	_msg[0] = (char)JOIN_GROUP;
	_msg[1] = (char) (_request->m_groupNameLen + _request->m_usernameLen + 2);
	_msg[2] = (char)  _request->m_usernameLen;
	strcpy(_msg+3,_request->m_username);
	_msg[3 + _request->m_usernameLen] = _request->m_groupNameLen;
	strcpy(_msg + 4 + _request->m_usernameLen,_request->m_groupName);

	return OK;
}

ProtocolStatus JoinGrpRequestUnpack (JoinGrpRequest* _request, const char* _msg)
{
	_request->m_usernameLen = _msg[2];
	memcpy(_request->m_username,&_msg[3],_request->m_usernameLen);
	_request->m_username[_request->m_usernameLen] = '\0';

	_request->m_groupNameLen = _msg[3 + _request->m_usernameLen];
	memcpy(_request->m_groupName,&_msg[3],_request->m_groupNameLen);
	_request->m_groupName[_request->m_groupNameLen] = '\0';

	return OK;	
}

ProtocolStatus JoinGrpReplyPack(const JoinGrpReply* _reply, char* _msg)
{
	_msg[0] = (char)JOIN_GROUP; 
	_msg[1] = (char) (3 + _reply->m_mcastIPLen + _reply->m_mcastPortLen);
	_msg[2] = _reply->m_requestStatus;
	_msg[3] = _reply->m_mcastIPLen;
	strncpy(_msg + 4, _reply->m_mcastIP,_reply->m_mcastIPLen);
	_msg[4 + _reply->m_mcastIPLen] = _reply->m_mcastPortLen;
	strncpy(_msg + 5 + _reply->m_mcastIPLen,_reply->m_mcastPort,_reply->m_mcastPortLen);

	return OK;
}

ProtocolStatus JoinGrpReplyUnpack (JoinGrpReply* _reply, const char* _msg)
{
	_reply->m_requestStatus = _msg[2];
	_reply->m_mcastIPLen 	= _msg[3];
	memcpy(_reply->m_mcastIP,&_msg[4], _reply->m_mcastIPLen);
	_reply->m_mcastPortLen	= _msg[4 + _reply->m_mcastIPLen + 1];
	_reply->m_mcastIP[_reply->m_mcastIPLen] = '\0';
	memcpy(_reply->m_mcastPort, &_msg[5 + _reply->m_mcastIPLen], _reply->m_mcastPortLen);
	_reply->m_mcastPort[ _reply->m_mcastPortLen] = '\0';

	return OK;
}

/**********************--LeaveGroup--*********************/

ProtocolStatus LeaveGrpRequestPack (const LeaveGrpRequest* _request, char* _msg)
{
	_msg[0] = (char)LEAVE_GROUP;
	_msg[1] = (char) 2 + _request->m_usernameLen + _request->m_groupNameLen;
	_msg[2] = (char) _request->m_usernameLen;
	strcpy(&_msg[3],_request->m_username);
	_msg[3 + _request->m_usernameLen] = _request->m_groupNameLen;
	strcpy(&_msg[4 +  _request->m_usernameLen] , _request->m_groupName);

	return OK;
}

ProtocolStatus LeaveGrpRequestUnpack (LeaveGrpRequest* _request, const char* _msg)
{
	_request->m_usernameLen = _msg[2];
	memcpy(_request->m_username,&_msg[3],_request->m_usernameLen);
	_request->m_username[_request->m_usernameLen] = '\0';

	_request->m_groupNameLen =_msg[3 + _request->m_usernameLen];
	memcpy(_request->m_groupName , &_msg[4 +  _request->m_usernameLen], _request->m_groupNameLen);
	_request->m_groupNameLen[_request->m_groupName] = '\0';

	return OK;
}

ProtocolStatus LeaveGrpReplyPack(const LeaveGrpReply* _reply, char* _msg)
{
	_msg[0] = (char)LEAVE_GROUP;
	_msg[1] = (char)1;
	_msg[2] = (char)_reply->m_requestStatus;

	return OK;
}

ProtocolStatus LeaveGrpReplyUnpack (LeaveGrpReply* _reply, const char* _msg)
{
	_reply->m_requestStatus = _msg[2];

	return OK;
}

/***********************************--GetGroups--*********************/

ProtocolStatus GetGrpsRequestPack ( const GetGrpsRequest* _request, char* _msg)
{
	_msg[0] = (char)GET_GROUPS;
	_msg[1] = strlen(_request->m_username);
	strcpy(&_msg[2],_request->m_username);

	return OK;
}

ProtocolStatus GetGrpsRequestUnpack ( GetGrpsRequest* _request, const char* _msg)
{
	int size = (int) _msg[1];
	memcpy(_request->m_username,&_msg[2],size);
	_request->m_username[size] = '\0';

	return OK;
}

ProtocolStatus GetGrpsReplyPack (const GetGrpsReply* _reply, char* _msg)
{
	_msg[0] = (char)GET_GROUPS;
	_msg[1] = (char) 1 + strlen(_reply->m_groupList);
	_msg[2] = (char)_reply->m_requestStatus;
	_msg[3] = (char) strlen(_reply->m_groupList);
	strcpy(&_msg[4],_reply->m_groupList);

	return 0;
}

ProtocolStatus GetGrpsReplyUnpack (GetGrpsReply* _reply, const char* _msg)
{
	int size = (int)_msg[3];
	_reply->m_requestStatus = _msg[2];
	memcpy(_reply->m_groupList,&_msg[3],size);
	_reply->m_groupList[size] = '\0';

	return OK;
}


/*
ProtocolStatus GetGrpsRequestPack( const GetGrpsRequest* _request, char* _msg)
{
	_msg[0] = (char) GET_GROUPS;
	_msg[1] = (char) strlen(_request->m_username);
	strcpy(&_msg[2],_request->m_username);

	return OK;
}

ProtocolStatus GetGrpsRequestUnpack(GetGrpsRequest* _request, const char* _msg)
{
	int size = (int) _msg[1];
	memcpy(_request->m_username,&_msg[2],size);
	_request->m_username[size] = '\0';

	return OK;
}
*/
