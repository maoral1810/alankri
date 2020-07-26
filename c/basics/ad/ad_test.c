#include <stdio.h>      /* printf   */
#include <stdlib.h>     /* free     */
#include "ad.h"         /* ad API   */
#include "ADerr.h"      /* errors   */

#define ARR_LEN(x)(sizeof(x) / sizeof(x[0]));

static void TestCreateAd(void);
static void TestCreatAdvalidInputs(void);           /* create ad valid sizes */
static void TestCreatAdIncSizeZeroSizeNotZero(void);/* create ad inc size = 0 size != 0 */
static void TestCreatAdIncSizeNotZeroSizeZero(void);/* create ad inc size != 0 size = 0 */
static void TestCreatAdInvalidSizes(void);          /* create ad inc size 0 & size = 0  */

static void TestDestroyAd(void);
static void TestDestroyCalenderNulls(void);         /* destroy NULL*/
static void TestDestroyEmptyCalender(void);         /* destroy empty calander */
static void TestDestroyCalenderDubleFree(void);     /* duable free */

static void TestCreateMeeting(void);
static void TestCreateMeetingValidBeginTimeInvalidEndTime(void);    /* valid begin time invalid end time*/
static void TestCreateMeetingInvalidBeginTimeValidEndTime(void);    /* invalid begin time valid end time*/ 
static void TestCreateMeetingInvalidBeginTimeInvalidEndTime(void);  /* invalid begin & end time*/
static void TestCreateMeetingValidInputs(void);                     /* valid inputs */
static void TestCreateMeetingBeginTimeBiggerThenEndTime(void);      /* begin > end */

static void TestInsert(void);
static void TestInsertAppointmentNULLS(void);                /* Ad & metting NULLs */
static void TestInsertAppointmentAdNull(void);               /* Ad NULL metting !NULL*/
static void TestInsertAppointmentMeetingNull(void);          /* Ad !NULL metting NULL*/
static void TestInsertAppointmentFullCalIncSizeZero(void);   /* overflow*/
static void TestInsertAppointmentFullCalIncSizeNotZero(void);/* realloc*/
static void TestInsertAppointmentValidMeeting(void);         /* valid meeting(increment by one)*/
static void TestInsertAppointmentSameMeeting(void);          /* insert exist meeting (overlap)*/
static void TestInsertAppointmentOverlapping(void);          /* insert invalid time for meeting */

static void TestRemove(void);
static void TestRemoveAppointmentAdNull(void);
static void TestRemoveAppointmentValidMeeting(void);
static void TestRemoveAppointmentInValidMeeting(void);
static void TestRemoveAppointmentEmptyCalender(void);

static void TestFind(void);
static void TestFindAppointmenttAdNull(void);
static void TestFindAppointmenttMeetingExists(void);
static void TestFindAppointmenttMeetingNotExists(void);
static void TestFindAppointmenttEmptyCalender(void);

static void TestSaveDiary(void);
static void TestLoadDiary(void);

static void PrintResualt(char *_testName, char *_scenario , int err);

int main(void)
{
    TestCreateAd();
    TestDestroyAd(); 
    TestCreateMeeting();
    TestInsert();
    TestRemove();
    TestFind(); 
    TestSaveDiary();
    TestLoadDiary();

    return 0;
}

static void TestCreateAd(void)
{
    printf(BOLDGREY"TestCreateAd\n"RESET);
    TestCreatAdvalidInputs();
    TestCreatAdIncSizeZeroSizeNotZero();
    TestCreatAdIncSizeNotZeroSizeZero();
    TestCreatAdInvalidSizes();
    putchar('\n');
}

static void TestCreatAdvalidInputs(void)
{
    calender_t *ad = NULL;
    int err = 0;
    char *testName = "TestCreatAd";
    char *scenario = "validInputs";

    ad = CreateAD(5, 2);
    
    if(NULL == ad)
    {
        ++err;
    }

    DestroyAD(ad);
    ad = NULL;

    PrintResualt(testName, scenario, err);
}

static void TestCreatAdIncSizeZeroSizeNotZero(void)
{
    calender_t *ad = NULL;
    int err = 0;
    char *testName = "TestCreatAd";
    char *scenario = "IncSizeZeroSizeNotZero";

    ad = CreateAD(5, 0);
    
    if(ad == NULL)
    {
        ++err;
    }

    DestroyAD(ad);
    ad = NULL;

    PrintResualt(testName, scenario, err);
}

static void TestCreatAdIncSizeNotZeroSizeZero(void)
{
    calender_t *ad = NULL;
    int err = 0;
    char *testName = "TestCreatAd";
    char *scenario = "IncSizeNotZeroSizeZero";

    ad = CreateAD(0, 2);
    
    if(ad == NULL)
    {
        ++err;
    }

    DestroyAD(ad);
    ad = NULL;

    PrintResualt(testName, scenario, err);
}

static void TestCreatAdInvalidSizes(void)
{
    calender_t *ad = NULL;
    int err = 0;
    char *testName = "TestCreatAd";
    char *scenario = "InvalidSizes";

    ad = CreateAD(0, -2);
    
    if(ad != NULL)
    {
        ++err;
    }

    DestroyAD(ad);
    ad = NULL;

    PrintResualt(testName, scenario, err);
}


static void TestDestroyAd(void)
{
    printf(BOLDGREY"TestDestroyAd\n"RESET);
    
    TestDestroyCalenderNulls();
    TestDestroyEmptyCalender();
    TestDestroyCalenderDubleFree();
    putchar('\n');
}

static void TestDestroyCalenderNulls(void)
{
    char *testName = "TestDestroy";
    char *scenario = "CalenderNulls";
        
    DestroyAD(NULL);

    PrintResualt(testName, scenario, 0); 
}

static void TestDestroyEmptyCalender(void)
{
    calender_t *ad = NULL;
    char *testName = "TestDestroy";
    char *scenario = "CalenderNulls";
    
    ad = CreateAD(5, 5);
    
    DestroyAD(ad);

    PrintResualt(testName, scenario, 0); 
}


static void TestDestroyCalenderDubleFree(void)
{
    calender_t *ad = NULL;
    char *testName = "TestDestroy";
    char *scenario = "CalenderNulls";
    
    ad = CreateAD(5, 5);
    
    DestroyAD(ad);
    DestroyAD(ad);

    PrintResualt(testName, scenario, 0);     
}



static void TestCreateMeeting(void)
{
    printf(BOLDGREY"TestCreateMeeting\n"RESET);

    TestCreateMeetingValidBeginTimeInvalidEndTime();
    TestCreateMeetingInvalidBeginTimeValidEndTime();
    TestCreateMeetingInvalidBeginTimeInvalidEndTime();
    TestCreateMeetingValidInputs();
    TestCreateMeetingBeginTimeBiggerThenEndTime();
    putchar('\n');
}
/* valid begin time invalid end time*/
static void TestCreateMeetingValidBeginTimeInvalidEndTime(void)
{
    meeting_t *meeting = CreateMeeting(23, 24.5, 55);
    char *testName = "TestCreateMeeting";
    char *scenario = "ValidBeginTimeInvalidEndTime";
    int err = 0;

    if(NULL != meeting)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);     
}

/* invalid begin time valid end time*/ 
static void TestCreateMeetingInvalidBeginTimeValidEndTime(void)
{
    meeting_t *meeting = CreateMeeting(24.5, 23.5, 22);
    char *testName = "TestCreateMeeting";
    char *scenario = "InvalidBeginTimeValidEndTime";
    int err = 0;

    if(NULL != meeting)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);     
}
/* invalid begin & end time */
static void TestCreateMeetingInvalidBeginTimeInvalidEndTime(void)
{
    meeting_t *meeting = CreateMeeting(24.5, 77.5, 2);
    char *testName = "TestCreateMeeting";
    char *scenario = "InvalidBeginTimeInvalidEndTime";
    int err = 0;

    if(NULL != meeting)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);     
}

/* valid inputs */
static void TestCreateMeetingValidInputs(void)
{
    meeting_t *meeting = CreateMeeting(12.5, 13.5, 2);
    char *testName = "TestCreateMeeting";
    char *scenario = "ValidInputs";
    int err = 0;

    if(NULL == meeting)
    {
        ++err;
    }

    free(meeting);
    PrintResualt(testName, scenario, err);     
}

/* begin > end */
static void TestCreateMeetingBeginTimeBiggerThenEndTime(void)
{
    meeting_t *meeting = CreateMeeting(11.5, 7.5, 2);
    char *testName = "TestCreateMeeting";
    char *scenario = "BeginTimeBiggerThenEndTime";
    int err = 0;

    if(NULL != meeting)
    {
        ++err;
    }

    free(meeting);
    PrintResualt(testName, scenario, err);
}


static void TestInsert(void)
{
    printf(BOLDGREY"TestInsert\n"RESET);

    TestInsertAppointmentNULLS();                
    TestInsertAppointmentAdNull();             
    TestInsertAppointmentMeetingNull();        
    TestInsertAppointmentFullCalIncSizeZero();  
    TestInsertAppointmentFullCalIncSizeNotZero();
    TestInsertAppointmentValidMeeting();         
    TestInsertAppointmentSameMeeting();
    TestInsertAppointmentOverlapping();
    putchar('\n');
}
/* Ad & metting NULLs */
static void TestInsertAppointmentNULLS(void)
{
    int err = 0;
    char *testName = "TestInsertAppointment";
    char *scenario = "NULLS";
    
    if( NOT_INITILIZE != InsertAppointment(NULL, NULL))
    {
        ++err;
    }
    
    PrintResualt(testName, scenario, err);
}

/* Ad NULL metting !NULL*/
static void TestInsertAppointmentAdNull(void)
{
    int err = 0;
    char *testName = "TestInsertAppointment";
    char *scenario = "AdNull";
    meeting_t *meeting = CreateMeeting(12,13,14);
    
    if( NOT_INITILIZE != InsertAppointment(NULL, meeting))
    {
        ++err;
    }
    
    free(meeting);

    PrintResualt(testName, scenario, err);
}             
/* Ad !NULL metting NULL*/
static void TestInsertAppointmentMeetingNull(void)
{
    int err = 0;
    char *testName = "TestInsertAppointment";
    char *scenario = "MeetingNull";
    calender_t *ad = NULL;
    
    ad = CreateAD(5,2);
    
    if(NOT_INITILIZE != InsertAppointment(ad, NULL))
    {
        ++err;
    }
    
    DestroyAD(ad);

    PrintResualt(testName, scenario, err);    
}
/* overflow*/
static void TestInsertAppointmentFullCalIncSizeZero(void)
{
    int err = 0;
    char *testName = "TestInsertAppointment";
    char *scenario = "FullCalIncSizeZero";
    float time = 2.3;
    calender_t *ad = NULL;
    meeting_t *meeting [3] = {0};
    size_t i = 0;
    size_t size = ARR_LEN(meeting);

    
    ad = CreateAD(2, 0);

    for(; i < size; ++i, time *= 2.23)
    {
        meeting[i] = CreateMeeting(time, time * 2, i + 1);

    }

    for(i = 0; i < (size - 1); ++i)
    {
        if(ERR_OK != InsertAppointment(ad, meeting[i]))
        {
            ++err;
        }
    }

    if(OVERFLOW != InsertAppointment(ad, meeting[i]))
    {
        ++err;
    }

    DestroyAD(ad);

    PrintResualt(testName, scenario, err);   
}

/* realloc*/
static void TestInsertAppointmentFullCalIncSizeNotZero(void)
{
    int err = 0;
    char *testName = "TestInsertAppointment";
    char *scenario = "CalIncSizeNotZero";
    float time = 2.3;
    calender_t *ad = NULL;
    meeting_t *meeting [3] = {0};
    size_t i = 0;
    size_t size = ARR_LEN(meeting);

    
    ad = CreateAD(2,2);
    
    for(; i < size; ++i, time *= 2.23)
    {
        meeting[i] = CreateMeeting(time, time * 2, i + 1);
    }

    for(i = 0; i < 2; ++i)
    {
        if(ERR_OK != InsertAppointment(ad, meeting[i]))
        {
            ++err;
        }
    }

    if(ERR_OK != InsertAppointment(ad, meeting[i]))
    {
        ++err;
    }

    DestroyAD(ad);

    PrintResualt(testName, scenario, err);   
}
/* valid meeting(increment by one)*/

static void TestInsertAppointmentValidMeeting(void)
{
    int err = 0;
    char *testName = "TestInsertAppointment";
    char *scenario = "ValidMeeting";
    float time = 2.3;
    calender_t *ad = NULL;
    meeting_t *meeting [3] = {0};
    size_t i = 0;
    size_t size = ARR_LEN(meeting);

    
    ad = CreateAD(2,1);
    
    for(; i < size; ++i, time *= 2.23)
    {
        meeting[i] = CreateMeeting(time, time * 2, i + 1);
    }

    for(i = 0; i < 2; ++i)
    {
        if(ERR_OK != InsertAppointment(ad, meeting[i]))
        {
            ++err;
        }
    }

    if(ERR_OK != InsertAppointment(ad, meeting[i]))
    {
        ++err;
    }
    
    DestroyAD(ad);

    PrintResualt(testName, scenario, err);    
}

static void TestInsertAppointmentSameMeeting(void)
{
    int err = 0;
    char *testName = "TestInsertAppointment";
    char *scenario = "SameMeeting";
    float time = 2.3;
    calender_t *ad = NULL;
    meeting_t *meeting [3] = {0};
   
    ad = CreateAD(2,1);

    meeting[0] = CreateMeeting(time, time * 2, 1);

    if(ERR_OK != InsertAppointment(ad, meeting[0]))
    {
        ++err;
    }

    if(OVELAPPING != InsertAppointment(ad, meeting[0]))
    {
        ++err;
    }
    
    DestroyAD(ad);

    PrintResualt(testName, scenario, err);    
}         

static void TestInsertAppointmentOverlapping(void)
{
    int err = 0;
    char *testName = "TestInsertAppointment";
    char *scenario = "Overlapping";
    calender_t *ad = NULL;
    meeting_t *meeting [3] = {0};
   
    ad = CreateAD(2,1);

    meeting[0] = CreateMeeting(2.3, 3.9, 1);
    meeting[1] = CreateMeeting(3.3, 4.9, 2);

    if(ERR_OK != InsertAppointment(ad, meeting[0]))
    {
        ++err;
    }

    if(OVELAPPING != InsertAppointment(ad, meeting[1]))
    {
        ++err;
    }
    
    DestroyAD(ad);

    PrintResualt(testName, scenario, err);    
}

static void TestRemove(void)
{
    printf(BOLDGREY"TestRemove\n"RESET);

    TestRemoveAppointmentAdNull();
    TestRemoveAppointmentValidMeeting();
    TestRemoveAppointmentInValidMeeting();
    TestRemoveAppointmentEmptyCalender();
    putchar('\n');
}
static void TestRemoveAppointmentAdNull(void)
{
    int err = 0;
    char *testName = "TestRemoveAppointment";
    char *scenario = "AdNull";
    float time = 2.3;
    meeting_t *meeting [3] = {0};
   
    meeting[0] = CreateMeeting(time, time * 2, 1);

    if(NOT_INITILIZE != RemoveAppointment(NULL, time))
    {
        ++err;
    }
    
    free(meeting[0]);
    
    PrintResualt(testName, scenario, err);    
}

static void TestRemoveAppointmentValidMeeting(void)
{
    int err = 0;
    char *testName = "TestRemoveAppointment";
    char *scenario = "ValidMeeting";
    float time = 2.3;
    calender_t *ad = NULL;
    meeting_t *meeting = NULL;
   
    ad = CreateAD(2,2);
    meeting = CreateMeeting(time, time * 2, 1);
   
    InsertAppointment(ad, meeting);

    if(ERR_OK != RemoveAppointment(ad, time))
    {
        ++err;
    }
    
    DestroyAD(ad);

    PrintResualt(testName, scenario, err);    
}

static void TestRemoveAppointmentInValidMeeting(void)
{
    int err = 0;
    char *testName = "TestRemoveAppointment";
    char *scenario = "InValidMeeting";
    calender_t *ad = NULL;
    meeting_t *meeting1 = NULL;
    meeting_t *meeting2 = NULL;
   
    ad = CreateAD(2,2);
    meeting1 = CreateMeeting(1.2, 3.6, 1);
    
    InsertAppointment(ad, meeting1);
    PrintAd(ad);

    meeting2 = CreateMeeting(7.3, 8.5, 2);
    PrintAd(ad);

    if(APPOINTMENT_NOT_FOUND != RemoveAppointment(ad, 7.3))
    {
        ++err;
    }
    
    free(meeting2);
    
    DestroyAD(ad);

    PrintResualt(testName, scenario, err);        
}

static void TestRemoveAppointmentEmptyCalender(void)
{
    int err = 0;
    char *testName = "TestRemoveAppointment";
    char *scenario = "EmptyCalender";
    float time = 2.3;
    calender_t *ad = NULL;
    meeting_t *meeting [3] = {0};
   
    ad = CreateAD(2,2);
    meeting[0] = CreateMeeting(time, time * 2, 1);

    if(UNDERFLOW != RemoveAppointment(ad, time))
    {
        ++err;
    }
    
    free(meeting[0]);
    
    DestroyAD(ad);

    PrintResualt(testName, scenario, err);       
}

static void TestFind(void)
{
    printf(BOLDGREY"TestFind\n"RESET);   

    TestFindAppointmenttAdNull();
    TestFindAppointmenttMeetingExists();
    TestFindAppointmenttMeetingNotExists();
    TestFindAppointmenttEmptyCalender();
    putchar('\n');
}

static void TestFindAppointmenttAdNull(void)
{
    int err = 0;
    char *testName = "TestFindAppointment";
    char *scenario = "AdNull";

    if(NOT_INITILIZE != FindAppointment(NULL, 1))
    {
        ++err;
    }
    
    PrintResualt(testName, scenario, err);       
}

static void TestFindAppointmenttMeetingExists(void)
{
    int err = 0;
    char *testName = "TestFindAppointment";
    char *scenario = "MeetingExists";
    calender_t *ad = NULL;
    meeting_t *meeting = NULL;
    
    ad = CreateAD(2,2);
    
    meeting = CreateMeeting(3.3, 4.0, 1);
    InsertAppointment(ad, meeting);

    if(APPOINTMENT_FOUND != FindAppointment(ad, 3.3))
    {
        ++err;
    }
    
    DestroyAD(ad);

    PrintResualt(testName, scenario, err);         
}
static void TestFindAppointmenttMeetingNotExists(void)
{
    int err = 0;
    char *testName = "TestFindAppointment";
    char *scenario = "MeetingNotExists";
    float time = 2.3;
    calender_t *ad = NULL;
    meeting_t *meeting [3] = {0};
   
    ad = CreateAD(2,2);
    
    meeting[0] = CreateMeeting(time, time * 2, 1);
    InsertAppointment(ad, meeting[0]);

    if(APPOINTMENT_NOT_FOUND != FindAppointment(ad, 16.2))
    {
        ++err;
    }
    
    DestroyAD(ad);

    PrintResualt(testName, scenario, err);
}

static void TestFindAppointmenttEmptyCalender(void)
{
    int err = 0;
    char *testName = "TestFindAppointment";
    char *scenario = "MeetingNotExists";
    calender_t *ad = NULL;

    ad = CreateAD(2,2);

    if(APPOINTMENT_NOT_FOUND != FindAppointment(ad, 16.2))
    {
        ++err;
    }
    
    DestroyAD(ad);

    PrintResualt(testName, scenario, err);
}


static void TestSaveDiary(void)
{
    int err = 0;
    char *testName = "TestSaveDiary";
    char *scenario = "";
    calender_t *ad = NULL;
    
    meeting_t *meet1 = CreateMeeting(2.3,2.6,2);
    meeting_t *meet2 = CreateMeeting(4.5,6.6,1);
    meeting_t *meet3 = CreateMeeting(6.8,8.9,3);

    ad = CreateAD(5,2);
    
    InsertAppointment(ad, meet1);
    InsertAppointment(ad, meet2);
    InsertAppointment(ad, meet3);

     if(ERR_OK != SaveDiary(ad, "meetings"))
    {
        ++err;
    }

    DestroyAD(ad);

    PrintResualt(testName, scenario, err);
}

static void TestLoadDiary(void)
{
    int err = 0;
    char *testName = "TestLoadDiary";
    char *scenario = "";
    calender_t *ad = NULL;
    
    ad = CreateAD(5,2);

    if(ERR_OK != LoadDiary(ad, "meetings"))
    {
        ++err;
    }

    PrintAd(ad);

    DestroyAD(ad);

    PrintResualt(testName, scenario, err);
}

/*------------- helpful functions -------------------------*/
static void PrintResualt(char *_testName, char *_scenario , int err)
{
    if(err)
    {
        printf(BOLDCYAN"%s"BOLDYELLOW":%s: "BOLDRED"FAIL!\n"RESET,
        _testName, _scenario); 
    }
    else
    {
        printf(BOLDCYAN"%s"BOLDYELLOW":%s: "BOLDGREEN"SUCSSES \n"RESET,_testName, _scenario);
    }
}

