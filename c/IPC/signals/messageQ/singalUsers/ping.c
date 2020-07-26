/* 	programmer: Maor Alankri
	program:  singal users message Queue(Writer)
	version: 1
	last update: 1.1.20
*/
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif

#include <sys/types.h> /* msgget, ftok, msgctl	*/
#include <sys/ipc.h>   /* msgget, ftok, msgctl	*/
#include <sys/msg.h>   /* msgget, msgctl			*/
#include <sys/stat.h>  /* S_IREAD, S_IWRITE */
#include <errno.h>	 /* errno							*/
#include "msgq.h"	  /* msgq API					*/
#include <stdio.h>	 /* printf 							*/
#include <stdlib.h>	/*malloc, free */
#include <unistd.h>	/* getpid */
#include <string.h>	/* strlen */
/* verbose print macro  */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvariadic-macros"
#define PRINTV(V, ...)           \
	do                           \
	{                            \
		if (V)                   \
			printf(__VA_ARGS__); \
	} while (0)
#pragma GCC diagnostic pop

static const int sg_DEFAULT_PERMISSIONS = (__S_IREAD | __S_IWRITE);
const char ECHO_MSG[] = "Message #%2d";
const char ECHO_ARGS[] = "Ping: send %d messages every %d msec to msgq %d\n";
const char ECHO_SEND[] = "PID:%d Ping sends %lu bytes:'%s'\n";
const char ECHO_RCV[] = "Ping Rcv from PID:%d Message:'%s'\n";
const char ECHO_EOF[] = "Ping send from PID:%d EOF Message:'%s'\n";

typedef struct PingArgs
{
	int verbose;
	int numOfmsg;
	int workSimulate;
	int toCreateMsgq;
	int toDeleteMsgq;
	int eof;
	char *fileName;
} PingArgs;

int main(int argc, char *argv[])
{
	int i = 0;
	int option = 0;
	int msgid = 0;
	size_t nBytes;
	key_t key = {0};
	PingArgs args = {0};
	MsgBuffer SendMessage;
	MsgBuffer ReciveMessage;

	while ((option = getopt(argc, argv, "vn:f:p:cde")) != -1)
	{
		switch (option)
		{
		case 'v':
			args.verbose = 1;
			break;

		case 'n':
			args.numOfmsg = atoi(optarg);
			break;

		case 'p':
			args.workSimulate = atoi(optarg) * 1000;
			break;

		case 'f':
			args.fileName = optarg;
			break;

		case 'c':
			args.toCreateMsgq = 1;
			break;

		case 'd':
			args.toDeleteMsgq = 1;
			break;

		case 'e':
			args.eof = 1;
			break;

		case ':':
			printf("option needs a value\n");
			break;

		case '?':
			printf("unknown option: %c\n", optopt);
			break;
		}
	}

	if (-1 == (key = ftok(args.fileName, PROJ_ID)))
	{
		printf("failed to create key with ftok\n");
		return errno;
	}

	if (args.toCreateMsgq)
	{

		if (-1 == (msgid = msgget(key, (sg_DEFAULT_PERMISSIONS | IPC_CREAT | IPC_EXCL))))
		{
			printf("failed to get a msgq with msgget\n");
			return errno;
		}
	}

	SendMessage.m_type = PINGS_TYPE;
	SendMessage.m_pid = getpid();
	/* 	msgsnd(msgid, SendMessage, 0, IPC_NOWAIT); */

	PRINTV(args.verbose, ECHO_ARGS, args.numOfmsg, args.workSimulate, msgid);

	while (i++ < args.numOfmsg)
	{
		sprintf(SendMessage.m_text, ECHO_MSG, i);
		/* printf("%s\n",SendMessage->m_text); */
		nBytes = sizeof(SendMessage.m_pid) + strlen(SendMessage.m_text);
		PRINTV(args.verbose, ECHO_SEND, getpid(), nBytes, SendMessage.m_text);

		if (-1 == msgsnd(msgid, &SendMessage, nBytes, IPC_NOWAIT))
		{
			printf("failed with msgsnd\n");
			return errno;
		}

		usleep(args.workSimulate);
		if (-1 == (nBytes = msgrcv(msgid, &ReciveMessage, MAX_MESSAGE_SIZE, PONGS_TYPE, 0))) /* ???? */
		{
			printf("failed with msgrcv\n");
			return errno;
		}
		PRINTV(args.verbose, ECHO_RCV, ReciveMessage.m_pid, ReciveMessage.m_text);
	}

	/* send eof */
	sprintf(SendMessage.m_text, ECHO_EOF,getpid(),"Finish" );
	SendMessage.m_type = EOF_TYPE;
	if (-1 == msgsnd(msgid, &SendMessage, strlen(SendMessage.m_text), IPC_NOWAIT))
	{
		printf("failed with msgsnd\n");
		return errno;
	}

	/* if("i am the last")*/
	if (-1 == msgctl(msgid, IPC_RMID, NULL))
	{
		printf("failed to destroy message with msgctl\n");
		return errno;
	}

	return 0;
}
