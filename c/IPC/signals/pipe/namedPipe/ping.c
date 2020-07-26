/* 	programmer: Maor Alankri
	program: named pipe using mkfifo with two seperate proccess (write)
	version: 1
	last update: 31.12.19
*/  

#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif

#include <sys/types.h>		/* fork				*/
#include <sys/stat.h> 		/* mkfifo			*/
#include <unistd.h>			/* fork, pipe		*/
#include <stdio.h>			/* printf			*/ 
#include <stdarg.h>			/* dprintf			*/
#include <sys/wait.h>		/* waitpid 			*/
#include <errno.h>			/* ernno 			*/
#include <stdlib.h>
#include <stdio.h>			/* open */
#include <fcntl.h>			/* open */
#include <string.h>			/* strcyp, strcat */

const char ECHO_ARGS[]	= "Ping: write %d messages every %d msec to file%s";
const char ECHO_SEND[]	= "PID:%d Ping sends:'%s'%d\n";
const char ECHO_MSG[]	= "Message #%2d";
/* verbose print macro  */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvariadic-macros"
#define PRINTV(V,...) do { if (V) printf(__VA_ARGS__); } while(0)
#pragma GCC diagnostic pop

typedef struct PingArgs
{
	int verbose;
	int numOfmsg;
	int ProducerTimeStamp;
	int toCreateFile;
	int toDeleteFile;
	char *fileName;
}PingArgs;

int main(int argc, char *argv[])
{
    int i = 0;
    int fd;
    int option;
    PingArgs args = {0};
    char *toadd = "./";
    
    while((option = getopt(argc, argv, "vn:f:p:cd")) != -1)
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
				args.ProducerTimeStamp = atoi(optarg) * 1000;
				break;
			
			case 'f':
				args.fileName = optarg;
				break;
				
			case 'c':
				args.toCreateFile = 1;
				break;
				
			case 'd':
				args.toDeleteFile = 1;
				break;
				
			case ':':
            	printf("option needs a value\n");
           		break;
           		
         	case '?':
            	printf("unknown option: %c\n", optopt);
            	break;
		}
	}
	
	if(args.fileName)
	{
		if(-1 == mkfifo(args.fileName, 0666))
		{
			printf("this name is allready exsist\n");
			return errno;
		}
	}
	
	if(args.toCreateFile)
	{
		if(-1 == (fd = open(args.fileName, O_WRONLY)))
		{
			perror("Error open file");
			return errno;
		}
	}
	
	PRINTV(args.verbose, ECHO_ARGS, args.numOfmsg, args.ProducerTimeStamp, args.fileName);
			
	for(i = 0; i < args.numOfmsg; ++i)
	{
		usleep(args.ProducerTimeStamp);
		
		dprintf(fd, "%s%d", "write message #",i);
		PRINTV(args.verbose,ECHO_SEND,getpid(),"write message #",i);
	}
	
	printf("ping finish\n");
	
	close(fd);
	
	if(args.toDeleteFile)
	{
		if(remove(args.fileName)) /* can do unlink */
		{
			perror("Error remove file");
			return errno;
		}
	}
			
	return 0;
}
    


