/* 	programmer: Maor Alankri
	program:  sheaed memory
	version: 1
	last update: 1.1.20
*/

#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif

#include <unistd.h>   /* getopt */
#include <errno.h>    /* errno	*/
#include <stdio.h>    /* printf */
#include <sys/stat.h> /* S_IREAD, S_IWRITE 			*/
#include <sys/ipc.h>  /* IPC_READ, IPC_WRITE */
#include <sys/shm.h>
#include <errno.h>     /* errno						*/
#include <sys/types.h> /*shmat */
#include <sys/sem.h>   /* semget */
#include <stdlib.h>    /*atoi */

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

#define SM_KEY 1
#define PONG_KEY 2
#define PING_KEY 3

const char ECHO_SEND[] = "PID:%d ping sends %lu bytes:'%s'\n";
const char ECHO_RCV[] = "PID:%d ping Rcv from PID:%d %ld bytes:'%s'\n";
const char ECHO_MESSAGE[] = "Ping Message #%2d\n";

static const int sg_DEFAULT_PERMISSIONS = (__S_IREAD | __S_IWRITE);

typedef struct PingArgs
{
    int verbose;
    int numOfMsg;
    int toCreate;
    size_t size;
} PingArgs;

typedef union semun {
    int val;               /* Value for SETVAL */
    struct semid_ds *buf;  /* Buffer for IPC_STAT, IPC_SET */
    unsigned short *array; /* Array for GETALL, SETALL */
    struct seminfo *__buf; /* Buffer for IPC_INFO
                                (Linux-specific) */
} semun;

typedef struct Message
{
    char m_str[32];
} Message;

int main(int argc, char *argv[])
{
    PingArgs args = {0};
    int option = 0;
    int sMemoryHandler = 0;
    int pingSemId = 0;
    int PongSemId = 0;
    int i = 0;
    semun ctlArgs = {0};
    struct sembuf up = {0, 1, 0};
    struct sembuf down = {0, -1, 0};
    Message msg;

    while ((option = getopt(argc, argv, "vcn:s:")) != -1)
    {
        switch (option)
        {
        case 'v':
            args.verbose = 1;
            break;

        case 'n':
            args.numOfMsg = atoi(optarg);
            break;

        case 'c':
            args.toCreate = 1;
            break;

        case 's':
            args.size = atoi(optarg);
            break;

        case ':':
            printf("option needs a value\n");
            break;

        case '?':
            printf("unknown option: %c\n", optopt);
            break;
        }
    }

    if (args.toCreate)
    {
        sMemoryHandler = shmget(SM_KEY, args.size, sg_DEFAULT_PERMISSIONS | IPC_CREAT | IPC_EXCL);
        if (-1 == sMemoryHandler)
        {
            perror("failed with shmget");
            return errno;
        }
    }

    if (-1 == (pingSemId = semget(PING_KEY, 1, (IPC_CREAT | IPC_EXCL | sg_DEFAULT_PERMISSIONS))))
    {
        perror("Failed with semget pingSemId");
        return errno;
    }

    if (-1 == (PongSemId = semget(PONG_KEY, 1, (IPC_CREAT | IPC_EXCL | sg_DEFAULT_PERMISSIONS))))
    {
        perror("Failed with semget PongSemId");
        return errno;
    }

    ctlArgs.val = 1;
    if (-1 == semctl(pingSemId, 0, SETVAL, ctlArgs))
    {
        perror("Failed with init semaphore!");
        return errno;
    }

    while (i++ < args.numOfMsg)
    {
        if (-1 == semop(pingSemId, &down, 1))
        {
            printf("Failed with semop down");
            return errno;
        }

        sprintf(msg.m_str, ECHO_MESSAGE, i);
        PRINTV(args.verbose, ECHO_SEND, getpid(), sizeof(msg.m_str), msg.m_str);

        if (-1 == semop(pingSemId, &up, 1))
        {
            printf("Failed with semop up");
            return errno;
        }
        sleep(1);
    }

    if (-1 == semctl(pingSemId, 0, IPC_RMID, NULL))
    {
        printf("Failed with semop down");
        return errno;
    }

    if (-1 == semctl(PongSemId, 0, IPC_RMID, NULL))
    {
        printf("Failed with semop down");
        return errno;
    }

    return 0;
}