#include <stdio.h> /* printf*/
#include <stddef.h> /* size_t */
#include "errors.h"
#include "UI.h"
#include "colors.h"


void PrintStatus(ERR _status)
{
    switch (_status)
    {
        case ERR_OK:
        {
            printf(BOLDRED"Ok\n"RESET);
            break;
        }
        case SOCKET_FAILED:
        {
            printf(BOLDRED"Socket Failed\n"RESET);
            break;
        }
        case UNINITIALIZE_VALUE:
        {
            printf(BOLDRED"Uninitialized Value\n"RESET);
            break;
        }
        case ALLOCATION_FAILED:
        {
            printf(BOLDRED"Allocation Failed\n"RESET);
            break;
        }
        case SEND_FAILED:
        {
            printf(BOLDRED"Send Failed\n"RESET);
            break;
        }
        case OPEN_FILE_FAILED:
        {
            printf(BOLDRED"Open File Failed\n"RESET);
            break;
        }
        case GENERAL_FAILURE:
        {
            printf(BOLDRED"General Failure\n"RESET);
            break;
        }
        /* server*/
        case BIND_FAILED:
        {
            printf(BOLDRED"Bind Failed\n"RESET);
            break;
        }
        case INIT_SERVER_FAILED:
        {
            printf(BOLDRED"Init Server Failed\n"RESET);
            break;
        }
        case LISTEN_FAILED:
        {
            printf(BOLDRED"Listen Failed\n"RESET);
            break;
        }
        case SET_SOCKET_FAILED:
        {
            printf(BOLDRED"Set Socket Failed\n"RESET);
            break;
        }
        case ACCEPT_FAILED:
        {
            printf(BOLDRED"Accept Failed\n"RESET);
            break;
        }
        /* user manager */
        case USER_EXSIST:
        {
            printf(BOLDRED"User Exsist\n"RESET);
            break;
        }
        case USER_NOT_EXSIST:
        {
            printf(BOLDRED"User Not Exsist\n"RESET);
            break;
        }
        case WRONG_PASS:
        {
            printf(BOLDRED"Wrong Pass\n"RESET);
            break;
        }
        case USER_ACTIVE_ALLREADEY:
        {
            printf(BOLDRED"User Active Allreadey\n"RESET);
            break;
        }
        /*group manager*/
        case GROUP_NOT_EXSIST:
        {
            printf(BOLDRED"Group Not Exsist\n"RESET);
            break;
        }
        /*client*/
        case CONNECTION_FAILED:
        {
            printf(BOLDRED"Connection Failed\n"RESET);
            break;
        }
        case SENDING_FAILED:
        {
            printf(BOLDRED"Sending Failed\n"RESET);
            break;
        }
        case RECIVE_FAILED:
        {
            printf(BOLDRED"Recive Failed\n"RESET);
            break;
        }
        case INVALID_INFO_FROM_CLIENT:
        {
            printf(BOLDRED"Invalid Info From Client\n"RESET);
            break;
        }
        case CLIENT_ALREADY_IN_GROUP:
        {
            printf(BOLDRED"Client Allredey In Group\n"RESET);
            break;
        }
        case CLIENT_NOT_IN_GROUP:
        {
            printf(BOLDRED"Client Not In Group\n"RESET);
            break;
        }
        
        default : break;
    }
}

void GetInput(char* _requestedField, char* _buffer, size_t _maxFieldSize, char _returnChar)
{
	char c;
    size_t inputSize;

	printf("Enter %s or '%c' to return to menu:\n", _requestedField, _returnChar);
	printf ("(%s over %ld chars will be trimmed)\n", _requestedField, _maxFieldSize);
    fgets(_buffer, _maxFieldSize, stdin);
	getchar();
    
    putchar('\n');
}

ManuSelection WelcomeMenuGetSelection()
{
    int selection;
    printf("<><><><><>wellcome to maShay chat<><><><>\n ");
    printf("please choose a option\n\n"GREEN"-1- registration\n-2- login\n"BOLDRED"-3- exit\n"RESET);
    scanf("%d", &selection);
    getchar();

    return selection;
}

ManuSelection HomeMenuGetSelection()
{
    int selection;
    printf(BOLDYELLOW"--------- MANU -------\n "RESET);
    printf("please choose a option\n\n"GREEN"-4- Join Group \n"BOLDRED"-5- Leave Group\n"GREEN"-6- Get Groups\n"BOLDRED"-7- LogOut\n"RESET);
    scanf("%d", &selection);
    getchar();
    return selection;

}