/* 	programmer: Maor Alankri
	program:  singal users message Queue(hfile)
	version: 1
	last update: 31.12.19
*/  

#ifndef MESSAGE_Q_SINGAL_USERS
#define MESSAGE_Q_SINGAL_USERS

#define PROJ_ID 18101989
#define PINGS_TYPE 1
#define EOF_TYPE 4
#define PONGS_TYPE 8
#define MESSAGE_TYPE 3
#define MAX_MESSAGE_SIZE 100

typedef struct MsgBuffer
{
	long m_type;
	pid_t m_pid;
	char m_text[MAX_MESSAGE_SIZE];
}MsgBuffer;


#endif /* MESSAGE_Q_SINGAL_USERS */







