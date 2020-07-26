#include <stdio.h>      /* printf   */
#include <sys/types.h>  /* fork     */
#include <unistd.h>     /* fork     */
#include "colors.h"

int g_var = 0;

int main(void)
{
    int l_var = 0;
    pid_t n;
    size_t i;

    n = fork();
    if(n < 0)
    {
        printf("failed in fork\n");
    }

    else
    {
        if(n > 0)/* parent procsses*/
        {
            printf(BOLDBLUE"i am parent\n"RESET);
            for(i = 0; i < 30; ++i)
            {
                printf(BLUE"g_var = %d\n"RESET,++g_var);
                printf(BLUE"l_var = %d\n"RESET,++l_var);
                sleep(1);
            }
            wait();
        }

        else
        {
            printf(BOLDYELLOW"i am child\n"RESET);
            for(i = 0; i < 30; ++i)
            {
                printf(YELLOW"g_var = %d\n"RESET,--g_var);
                printf(YELLOW"l_var = %d\n"RESET,--l_var);
                sleep(1);
            }
        }
    }
    
    return 0;
}