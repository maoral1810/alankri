/* 	programmer: Maor Alankri
	program: named pipe using mkfifo with two seperate proccess (read)
	version: 1
	last update: 31.12.19
*/  

#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif

const char ECHO_ARGS[] = "Pong: read messages every %d msec from file%s\n";
const char ECHO_RECV[]	= "Pong received #%2d = '%s'\n";

#include <sys/types.h> 	/* fork			*/
#include <sys/stat.h>  	/* mkfifo		*/
#include <unistd.h>		/* fork, pipe	*/
#include <stdio.h>	 	/* printf		*/
#include <stdarg.h>		/* dprintf		*/
#include <sys/wait.h>  	/* waitpid 		*/
#include <errno.h>	 	/* ernno 		*/
#include <stdlib.h>	
#include <stdio.h> 		/* open 		*/
#include <fcntl.h> /* open */
#include <string.h>

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
#define BUFFER_SIZE 32

typedef struct PongArgs
{
	int verbose;
	int ConsumerTimeStamp;
	char *fileName;
} PongArgs;

int main(int argc, char *argv[])
{
	int msgNum = 0;
	int fd;
	int option;
	size_t readBytes;
	PongArgs args = {0};
	char buffer[BUFFER_SIZE];
	char *toadd = "./";

	while ((option = getopt(argc, argv, "vn:f:p:c:")) != -1)
	{
		switch (option)
		{
		case 'v':
			args.verbose = 1;
			break;

		case 'c':
			args.ConsumerTimeStamp = atoi(optarg) * 1000;
			break;

		case 'f':
			args.fileName = optarg;
			break;

		case ':':
			printf("option needs a value\n");
			break;

		case '?':
			printf("unknown option: %c\n", optopt);
			break;
		}
	}

	if (-1 == (fd = open(args.fileName, O_RDONLY)))
	{
		perror("Error open file");
		return errno;
	}

	PRINTV(args.verbose, ECHO_ARGS, args.ConsumerTimeStamp, args.fileName);

	while (readBytes = read(fd, buffer, BUFFER_SIZE))
	{
		++msgNum;
		if (args.verbose)
		{
			PRINTV(args.verbose,ECHO_RECV,msgNum,buffer);
			
/* 			printf("%s\n", buffer); */
		}

		usleep(args.ConsumerTimeStamp);
	}
	PRINTV(args.verbose,"Pong finish\n");
	close(fd);

	return 0;
}
