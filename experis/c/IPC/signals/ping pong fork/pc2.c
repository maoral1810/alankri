#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif

#include <signal.h>     /* SGIUSER1, SGIUSER2 */
#include <sys/types.h>  /* fork               */
#include <unistd.h>     /* fork               */
#include <stdio.h>      /* printf             */ 
#include <stdlib.h>

void User1Handler(); 
void User2Handler(); 

int main(int argc, char *argv[])
{
	int pid = 0;
	int option ,psig, csig;
	struct sigaction sa1 = {0};
	struct sigaction sa2 = {0};
    
	while((option = getopt(argc, argv, "p:c:")) != -1)
	{
		switch (option)
		{
			case 'p':
/*				printf("parent optarg: %s\n", optarg);*/
				psig = atoi(optarg);
				break;
				
			case 'c':
/*				printf("child optarg: %s\n", optarg);*/
				csig = atoi(optarg);
				break;
			case ':':
            	printf("option needs a value\n");
           		break;
         	case '?':
            	printf("unknown option: %c\n", optopt);
            	break;
		}
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
		sa1.sa_handler = User1Handler;
		sigaction(psig, &sa1, NULL);
		pause();
		kill(getppid(), csig);
	}
	/* parent */
	if (0 < pid)
	{
		sa2.sa_handler = User2Handler;
		sigaction(csig, &sa2, NULL);
/* 		usleep(100); */
		kill(pid, psig);
		pause();
	}

	return 0;
}  
           
void User1Handler(void) 
{ 
	write(0,"\nPING From Parant--->\n", 25);
} 

void User2Handler(void) 
{ 
	write(0, "\n<---PONG From Child\n", 25);
} 
    