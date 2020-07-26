#include <stdio.h>  /* printf, scanf*/
#include "serverManager.h"
#include "colors.h"

int main(void)
{
    Server* myServer = CreateServer();
    int option = 1;
    int state = 0;

    printf(BOLDYELLOW"<><><><><>"BOLDBLUE"welcome to maShay Chat"BOLDYELLOW"<><><><><>\n"RESET);
    while (option)
    {
        char userName[8] = {0};
        char paswword[8] = {0};
        printf("please choose a option\n\n"GREEN"-1- registration\n-2- login\n"BOLDRED"-3- exit\n"RESET);
        scanf("%d", &state);

        switch (state)
        {
            case 1:/*reg*/
            {
                printf(BOLDGREEN"----- registration to server ------\n"RESET);
                printf("Please enter a user name and password\n"BOLDRED"(must be less then 8 characters\n"RESET);
                scanf("%s %s", userName, paswword);
                /*registration */
                break;
            }   
            case 2:/* login */
            {
                printf(BOLDGREEN"----- login server ------"RESET);
                printf("Please enter a user name and password\n"BOLDRED"(must be less then 8 characters\n"RESET);
                scanf("%s %s", userName, paswword);
                break;
            }

            case 3: /* exit */
            {
                printf("\n^GoodBye^\n");
                option = 0;
                break;
            }
            default:
            {
                printf(BOLDRED"option not valid, Please Try Again\n"RESET);
                break;
            }
        }
    }

    /* close all thing and destroy */ 
    return 0;
}