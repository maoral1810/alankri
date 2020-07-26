/* 	programmer: Maor Alankri
	program:  singal semaphore
	version: 1
	last update: 1.1.20
*/

#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif

#include <sys/types.h> /* semget, semop*/
#include <sys/ipc.h>   /* semget, semop*/
#include <sys/sem.h>   /* semget, semop*/
#include <sys/stat.h>  /* __S_IREAD, __S_IWRITE*/
#include <errno.h>     /* errno	*/
#include <unistd.h>    /* getopt */
#include <stdio.h>     /* printf */
#include <stdlib.h>    /* atoi */

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

typedef union semun 
{
    int val;               /* Value for SETVAL */
    struct semid_ds *buf;  /* Buffer for IPC_STAT, IPC_SET */
    unsigned short *array; /* Array for GETALL, SETALL */
    struct seminfo *__buf; /* Buffer for IPC_INFO
                                (Linux-specific) */
}semun;

const char ECHO_MESSAGE[] = "Message #%2d\n";
static const int sg_DEFAULT_PERMISSIONS = (__S_IREAD | __S_IWRITE);

int main(int argc, char *argv[])
{
    int option = 0;
    int verbose = 0;
    int semId = 0;
    int numOfPrints = 0;
    int i = 0;
    semun ctlArgs = {0};
    struct sembuf up = {0, 1, 0};
    struct sembuf down = {0, -1, 0};

    if (-1 == (semId = semget(1, 1, (IPC_CREAT | IPC_EXCL | sg_DEFAULT_PERMISSIONS))))
    {
        printf("Failed with semget\n");
        return errno;
    }
    
    ctlArgs.val = 1;
    if (-1 == semctl(semId, 0, SETVAL, ctlArgs)) 
    {
        perror("Failed with init semaphore!");
        return errno;
    }

    while ((option = getopt(argc, argv, "vn:")) != -1)
    {
        switch (option)
        {
        case 'v':
            verbose = 1;
            break;

        case 'n':
            numOfPrints = atoi(optarg);
            break;

        case ':':
            printf("option needs a value\n");
            break;

        case '?':
            printf("unknown option: %s\n", optarg);
            break;
        }
    }

    while (i++ < numOfPrints)
    {
        if (-1 == semop(semId, &down, 1))
        {
            printf("Failed with semop down");
            return errno;
        }

        PRINTV(verbose, ECHO_MESSAGE, i);

        if (-1 == semop(semId, &up, 1))
        {
            printf("Failed with semop up");
            return errno;
        }
        sleep(1);
    }

    return 0;
}

