/* 	programmer: Maor Alankri
	program:  singal users message Queue(reader)
	version: 1
	last update: 1.1.20
*/

#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif

#include <sys/types.h> 	/* msgget, ftok, msgsnd, msgrcv */
#include <sys/ipc.h>   	/* msgget, ftok, msgsnd, msgrcv */
#include <sys/msg.h>   	/* msgget, msgsnd, msgrcv		*/
#include <sys/stat.h>  	/* S_IREAD, S_IWRITE 			*/
#include <errno.h>	 	/* errno						*/
#include <stdlib.h>		/* malloc, free 				*/
#include <unistd.h>		/* getopt 						*/
#include <stdio.h>	 	/* printf 						*/
#include <string.h>		/* strncpy 						*/
#include "msgq.h"	  	/* msgq API						*/
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvariadic-macros"
#define PRINTV(V, ...)           \
	do                           \
	{                            \
		if (V)                   \
			printf(__VA_ARGS__); \
	} while (0)
#pragma GCC diagnostic pop

const char ECHO_SEND[] = "PID:%d Pong sends %lu bytes:'%s'\n";
const char ECHO_RCV[] = "PID:%d Pong Rcv from PID:%d %ld bytes:'%s'\n";


static const int sg_DEFAULT_PERMISSIONS = (__S_IREAD | __S_IWRITE);

typedef struct PongArgs
{
	int verbose;
	int workSimulate;
	char *fileName;
} PongArgs;

int main(int argc, char *argv[])
{
	int option = 0;
	int msgid = 0;
	key_t key = {0};
	size_t nBytes = 0;
	MsgBuffer MessageToSend;
	MsgBuffer MessageToRecive;
	PongArgs args = {0};

	while ((option = getopt(argc, argv, "vf:s:")) != -1)
	{
		switch (option)
		{
		case 'v':
			args.verbose = 1;
			break;

		case 's':
			args.workSimulate = atoi(optarg) * 1000;
			break;

		case 'f':
			args.fileName = optarg;
			break;

		case ':':
			printf("option needs a value\n");
			break;

		case '?':
			printf("unknown option: %s\n", optarg);
			break;
		}
	}

	if (-1 == (key = ftok(args.fileName, PROJ_ID)))
	{
		printf("failed to create key with ftok\n");
		return errno;
	}

	if (-1 == (msgid = msgget(key, (sg_DEFAULT_PERMISSIONS | IPC_EXCL))))
	{
		printf("failed to get a msgq with msgget\n");
		return errno;
	}

	MessageToSend.m_type = PONGS_TYPE;
	MessageToSend.m_pid = getpid();
	msgsnd(msgid, &MessageToSend, 0, IPC_NOWAIT);
	/* ???? IPC_NOWAIT */
	while ((nBytes = msgrcv(msgid, &MessageToRecive, MAX_MESSAGE_SIZE, PINGS_TYPE, 0)) >= 0 )
	{
		
			/* check eof */
			/* if not finish, wait */
/* 		if (nBytes <= 0)
		{
			break;
		} */

		memcpy(MessageToSend.m_text, MessageToRecive.m_text, nBytes - sizeof(MessageToRecive.m_pid));

		PRINTV(args.verbose, ECHO_RCV, getpid(),MessageToRecive.m_pid ,nBytes, MessageToRecive.m_text);
		PRINTV(args.verbose, ECHO_SEND, getpid(),nBytes, MessageToRecive.m_text);
		if (-1 == msgsnd(msgid, &MessageToSend, nBytes, IPC_NOWAIT))
		{
			printf("failed with msgsnd\n");
			return errno;
		}
	}

	return 0;
}
