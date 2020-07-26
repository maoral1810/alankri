#include <stddef.h> /* size_t */
#include <stdio.h>  /* printf, scanf */
#include <stdlib.h> /* free */
#include "ADerr.h"
#include "ad.h" /* API functions */

static calender_t *MyCreateAD(void);
static meeting_t *MyCreateMeeting(void);

static void PrintMenu(void);
static void PrintErr(ADerr _status);
static ADerr DestroyMeeting(meeting_t *_meeting);

int main(void)
{
    int operasion = 0;
    calender_t *ad = NULL;
    meeting_t *meeting = NULL;
    ADerr status = 0;
    size_t index = 0;
    float beginTime = 0;

    printf(BOLDYELLOW "\n-<>-<>-<>-<>-" BOLDWHITE "Wellcome to Maor dairy" BOLDYELLOW "-<>-<>-<>-<>-\n");
    printf(RESET "please enter a number for choosing function\n");

    while (11 != operasion)
    {
        putchar('\n');

        PrintMenu();
        scanf("%d", &operasion);

        switch (operasion)
        {
        case 1:

            if (ad == NULL)
            {
                ad = MyCreateAD();
            }
            else
            {
                printf(BOLDBLUE "you have allredey AD\n");
            }
            break;

        case 2:

            if(ad == NULL)
            {
                printf(BOLDBLUE"there is no ad to destroy\n"RESET);
                break;
            }
            
            DestroyAD(ad);
            ad = NULL;
            printf(BOLDRED "ad destroy!!!\n" RESET);
            break;

        case 3:

            if (NULL == meeting)
            {
                meeting = MyCreateMeeting();
            }
            else
            {
                printf(BOLDBLUE "you have allredey meeting\n");
            }

            break;

        case 4:

            DestroyMeeting(meeting);
            printf(BOLDBLUE"meeting is destroyed!!\n"RESET);
            meeting = NULL;
            break;
                       
            break;

        case 5:

            status = InsertAppointment(ad, meeting);
            if(status == ERR_OK)
            {
                meeting = NULL;
                printf(BOLDGREEN"insert sucsses\n"RESET);
            }
            else if(status == OVELAPPING)
            {
                printf("Insert failed with ");
                PrintErr(status);
                putchar('\n');
                PrintAd(ad);
                printf("do you really want to insert this meeting??\nyou need to remove the overlap meeting!!\n");
            }
            else
            {
                printf("Insert failed with ");
                PrintErr(status);
                putchar('\n');
            }
            
            break;

        case 6:

            beginTime = 0;

            PrintAd(ad);
            printf("whitch meeting do you want to remove???\n enter her begin hour\n");
            scanf("%f", &beginTime);

            status = RemoveAppointment(ad, beginTime);
            if (status != ERR_OK)
            {
                PrintErr(status);
                putchar('\n');
            }
            else
            {
                printf(BOLDBLUE"sucsses to remove meeting\n"RESET);
            }
            
            break;       
            
        case 7:

            PrintAd(ad);
            break;

        case 8:

            beginTime = 0;

            printf("please insert begin time to find\n");
            scanf("%f", &beginTime);
            status = FindAppointment(ad, beginTime);

            if (status != ERR_OK)
            {
                PrintErr(status);
                putchar('\n');
            }
            break;

        case 9:

            status = SaveDiary(ad,"meetings");
            
            if(status == ERR_OK)
            {
                printf(BOLDGREEN"Calander saved\n"RESET);
            }

            else
            {
                PrintErr(status);
                putchar('\n');
            }
                       
            break;
            
        case 10:


            status = LoadDiary(ad,"meetings");
            if(status == ERR_OK)
            {
                printf(BOLDGREEN"Calander Load\n"RESET);
            }

            else
            {
                PrintErr(status);
                putchar('\n');
            }
            
            break;


        default:
            if(isalpha(operasion) || operasion > 11)
            {
                printf(" please enter a valid number\n");
            }
            break;
        }
    }

    DestroyAD(ad);



    return 0;
}

static void PrintMenu(void)
{
    printf(BOLDWHITE "1)" BOLDGREEN "Create AD\t\t" RESET);
    printf(BOLDWHITE "2)" BOLDRED "Destroy AD\n" RESET);
    printf(BOLDWHITE "3)" BOLDGREEN "Create Meeting\t" RESET);
    printf(BOLDWHITE "4)" BOLDRED "Destroy meeting\n" RESET);
    printf(BOLDWHITE "5)" BOLDCYAN "Insert Appointment\t" RESET);
    printf(BOLDWHITE "6)" BOLDRED "Remove Appointment\n" RESET);
    printf(BOLDWHITE "7)" BOLDGREY "Print Ad\n" RESET);
    printf(BOLDWHITE "8)" BOLDMAGENTA "Find Appointment\t" RESET);
    printf(BOLDWHITE "9)" BOLDGREEN "SaveDiary\t\t" RESET);
    printf(BOLDWHITE "10)"BOLDBLUE "LoadDiary\n" RESET);
    printf(BOLDWHITE "11)" BOLDYELLOW "Exit\n" RESET);
    
}

static calender_t *MyCreateAD(void)
{
    int size = 0;
    int incSize = 0;
    calender_t *ad = NULL;

    printf("please insert a positive cal size\n");
    scanf("%d", &size);

    printf("please insert a positive increment block Size\n");
    scanf("%d", &incSize);

    ad = CreateAD(size, incSize);

    if (ad != NULL)
    {
        printf(GREEN "ad create Sucsses\n" RESET);
    }
    else
    {
        printf(RED "ad create Fail with size = %d and increment size = %d\n" RESET,
               size, incSize);
    }

    return ad;
}

static meeting_t *MyCreateMeeting(void)
{
    float beginTime = 0;
    float endTime = 0;
    int room = 0;
    meeting_t *meeting = NULL;

    printf("please insert a begin time (between 0 - 23.99)\n");
    scanf("%f", &beginTime);

    printf("please insert end time (between 0 - 23.99)\n");
    scanf("%f", &endTime);

    printf("please insert room number\n");
    scanf("%d", &room);

    meeting = CreateMeeting(beginTime, endTime, room);

    if (NULL != meeting)
    {
        printf(GREEN "meeting create Sucsses\n" RESET);
        return meeting;
    }
    else
    {
        printf(RED "meeting create Fail with beginTime = %.2f end time = %.2f\n" RESET,
               beginTime, endTime);

        return NULL;
    }
}

static void PrintErr(ADerr _status)
{
    if (ERR_OK == _status)
    {
        printf(GREEN "Sucsses\n" RESET);
    }
    else if (NOT_INITILIZE == _status)
    {
        printf(RED "Not Initilize\n" RESET);
    }
    else if (REALLOC_FAILED == _status)
    {
        printf(RED "Realloc Failed\n" RESET);
    }
    else if (APPOINTMENT_NOT_FOUND == _status)
    {
        printf(RED "Appointmet Not Found\n" RESET);
    }
    else if (APPOINTMENT_FOUND == _status)
    {
        printf(GREEN "Appointmet Found\n" RESET);
    }
    else if (INVALIV_INPUT == _status)
    {
        printf(RED "Invalid Input\n" RESET);
    }
    else if (OVELAPPING == _status)
    {
        printf(RED "Overlapping\n" RESET);
    }
    else if (OVERFLOW == _status)
    {
        printf(RED "Overflow\n" RESET);
    }
    else
    {
        printf(RED "UNDERFLOW\n" RESET);
    }
}

static ADerr DestroyMeeting(meeting_t *_meeting)
{
    if (_meeting != NULL)
    {
        free(_meeting);
    }
}
