#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 700
#endif

#include <sys/types.h>	/* fork									*/
#include <unistd.h>			/* fork, pipe						*/
#include <stdio.h>			/* printf								*/ 
#include <stdarg.h>			/* dprintf								*/
 #include <sys/wait.h>		/* waitpid 							*/
#include <stdlib.h>

typedef struct BashArgs
{
	int verbose;
	int numOfWrites;
	int ProducerTimeStamp;
	int CounsomerTimeStamp;
	int readBufferSize;
}BashArgs;

int main(int argc, char *argv[])
{
	int pid = 0;
	int option;
	int fd[2] = {0};
	int status;
	size_t readBytes;
	BashArgs args = {0};

    while((option = getopt(argc, argv, "vn:p:c:r:")) != -1)
	{
		switch (option)
		{
			case 'v':
				args.verbose = 1;
				break;
				
			case 'n':
				args.numOfWrites = atoi(optarg);
				break;
				
			case 'p':
				args.ProducerTimeStamp = atoi(optarg);
				break;
				
			case 'c':
				args.CounsomerTimeStamp = atoi(optarg);
				break;
				
			case 'r':
				args.readBufferSize = atoi(optarg);
				break;
				
			case ':':
            	printf("option needs a value\n");
           		break;
           		
         	case '?':
            	printf("unknown option: %c\n", optopt);
            	break;
		}
	}
	
	if(pipe(fd))
	{
		printf("failed in piping\n");
		return 0;
	}
	
	pid = fork();
	
	/* failed fork */
	if (0 > pid) 
	{ 
		printf("\nfork failed\n"); 
		return 1; 
	} 
	/* child */
	if (0 == pid)
	{
		char *readBuffer = (char *)malloc(args.readBufferSize + 1);
		printf("enter to child\n");
		close(fd[1]); /* close write */
		while(readBytes = read(fd[0], readBuffer, args.readBufferSize)) /* run until write will finish */
		{
			if(args.verbose)
			{
				printf("read from buffer %lu bytes\n", readBytes);
			}
			
			usleep(args.CounsomerTimeStamp);
		}
		
		printf("child finish\n");
	}
	
	/* parent */
	if (0 < pid)
	{
		int i = 0;
		close(fd[0]);
		for(i = 0; i < args.numOfWrites; ++i)
		{
			if(args.verbose)
			{
				printf("write message #%d\n",i);
			}
			
			usleep(args.ProducerTimeStamp);
			dprintf(fd[1], "%s%d", "write message #",i);
		}
		printf("parent finish\n");
		close(fd[1]);
		waitpid(pid,&status,0);
	}

	return 0;
}
