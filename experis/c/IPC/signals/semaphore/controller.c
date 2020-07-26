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
#include <stdio.h>      /* rintf */
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

typedef struct ControllerArgs
{
    int verbose;
    int toPause;
    int toResume;
    int toDelete;
    int toUpDown;
} ControllerArgs;

typedef union semun {
    int val;               /* Value for SETVAL */
    struct semid_ds *buf;  /* Buffer for IPC_STAT, IPC_SET */
    unsigned short *array; /* Array for GETALL, SETALL */
    struct seminfo *__buf; /* Buffer for IPC_INFO
                                (Linux-specific) */
} semun;

static const int sg_DEFAULT_PERMISSIONS = (__S_IREAD | __S_IWRITE);

int main(int argc, char *argv[])
{
    int option = 0;
    int semId = 0;
    ControllerArgs args = {0};
    struct sembuf up = {0, 1, 0};
    struct sembuf down = {0, -1, 0};
    semun semctrargs = {0};

    if (-1 == (semId = semget(1, 1, (IPC_EXCL | sg_DEFAULT_PERMISSIONS))))
    {
        printf("Failed with semget\n");
        return errno;
    }

    while ((option = getopt(argc, argv, "vprdu")) != -1)
    {
        switch (option)
        {
        case 'v':
            args.verbose = 1;
            break;

        case 'p':
            args.toPause = 1;
            /*Stop == sem down*/
            break;

        case 'r':
            args.toResume = 1;
            /* sem up */
            break;

        case 'd':
            args.toDelete = 1;
            /*semctl(delete)*/
            break;

        case 'u':
            args.toUpDown = 1;
            /* semupdown */
            break;
        }
    }

    if (args.toPause)
    {
        if (-1 == semop(semId, &down, 1))
        {
            printf("Failed with semop down");
            return errno;
        }
    }

    if (args.toResume)
    {
        if (-1 == semop(semId, &up, 1))
        {
            printf("Failed with semop down");
            return errno;
        }
    }

    if (args.toDelete)
    {
        if (-1 == semctl(semId, 0, IPC_RMID, semctrargs))
        {
            printf("Failed with semop down");
            return errno;
        }
    }

    if (args.toUpDown)
    {
        struct sembuf sopbuf[2] = {{0, -1, 0}, {0, 1, 0}};
        if (-1 == semop(semId, sopbuf, 2))
        {
            printf("Failed with semop down");
            return errno;
        }
    }

    return 0;
}
