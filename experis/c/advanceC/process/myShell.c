#include <stdio.h>      /* printf   */
#include <sys/types.h>  /* fork     */
#include <unistd.h>     /* fork     */
#include <sys/wait.h>   /* waitpid  */
#include <string.h>     /* strtok   */
#include <stdlib.h>     /* exit */
#include "colors.h"

#define COMMEND_SIZE 100

static void Promp(void);
static void GetCommend(char **_args );

int main(void)
{
    int status = 0;
    pid_t n;
    char *args[100] = {0};
    char *commend;
    
    Promp();
    
    while (1)
    {
        n = fork();
        if(n < 0)
        {
            printf("failed in fork\n");
        }
        else
        {
            if(n > 0)/* parent procsses*/
            {
                waitpid(-1, &status, 0);
            }
            else /* i am chiled */
            {
                GetCommend(args);
                if(execvp(args[0], args))
                {
                    exit(1);
                }
            }
        }
    }

    
    return 0;
}

static void Promp(void)
{
    printf(BOLDYELLOW"<-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><->\n"RESET);
    printf(BOLDGREEN" Wellcome to Maor Shell\n"RESET);
    printf(BOLDYELLOW"<-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><->\n"RESET);
}

static void GetCommend(char **_args)
{
    char userCommend[COMMEND_SIZE];
    char *token;

    size_t i = 0;
    size_t j = 0;
    
    printf(BOLDCYAN"MaorShell >>"RESET);
    scanf("%[^\n]s", userCommend);
    getchar();

    _args[i] = strtok(userCommend, " ");
    
    while((_args[++i] = strtok(NULL, " ")) != NULL){};
}