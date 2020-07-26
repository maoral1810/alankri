#include <stdio.h>
#include <stdlib.h>
#include "scheduler.h"
#include "colors.h"

static int IsPrior(const void *_data1, const void *_data2);
static int OperationForTask(void *arg);
static void PrintResualt(char *_testName, char *_scenario, int err);

static void TestSchedulerNull(void);
static void TestSchedulerIntervalsZero(void);
static void TestSchedulerIntervalsNotZero(void);
static void TestSchedulerSmallIntervals(void);

int main(void)
{
    TestSchedulerNull();
    TestSchedulerIntervalsZero();
    TestSchedulerSmallIntervals();
    TestSchedulerIntervalsNotZero();
}

static void TestSchedulerNull(void)
{
    char *testNmae = "TestScheduler";
    char *scenario = "Null";
    int err = 0;

    if(SCH_NOT_INITIALIZE != SchAdd(NULL, 0 , OperationForTask, &err))
    {
        ++err;
    }
    
    if(SCH_NOT_INITIALIZE != SchRun(NULL))
    {
        ++err;
    }

    PrintResualt(testNmae, scenario, err);
}

static void TestSchedulerIntervalsNotZero(void)
{
    char *testNmae = "TestScheduler";
    char *scenario = "IntervalsNotZero";
    int err = 0;
    Scheduler *sch = SchCreate(IsPrior);
    size_t i = 0;
    double interval[] = {10, 5500, 100, 1000, 2000};
    size_t size = 5;
    char *args[] = {"1", "2", "3", "4", "5"};

    while(i < size)
    {
        if(SCH_SUCSSES != SchAdd(sch, interval[i] , OperationForTask, args[i]))
        {
            ++err;
        }

        ++i;
    }

    SchRun(sch);
    SchDestroy(sch);

    PrintResualt(testNmae, scenario, err);
}


static void TestSchedulerIntervalsZero(void)
{
    char *testNmae = "TestScheduler";
    char *scenario = "IntervalsZero";
    int err = 0;
    Scheduler *sch = SchCreate(IsPrior);
    size_t i = 0;
    size_t size = 5;
    char *args[] = {"1", "2", "3", "4", "5"};

    while(i < size)
    {
        if(SCH_NOT_INITIALIZE != SchAdd(sch, 0, OperationForTask, args[i++]))
        {
            ++err;
        }
    }

    SchRun(sch);
    SchDestroy(sch);

    PrintResualt(testNmae, scenario, err);
}

static void TestSchedulerSmallIntervals(void)
{
    char *testNmae = "TestScheduler";
    char *scenario = "SmallIntervals";
    int err = 0;
    Scheduler *sch = SchCreate(IsPrior);
    size_t i = 0;
    size_t size = 5;
    char *args[] = {"1", "2", "3", "4", "5"};

    while(i < size)
    {
        if(SCH_SUCSSES != SchAdd(sch, 1, OperationForTask, args[i++]))
        {
            ++err;
        }
    }

    SchRun(sch);
    SchDestroy(sch);

    PrintResualt(testNmae, scenario, err);
}

/* --------------------helpful functions ----------------------------*/
static void PrintResualt(char *_testName, char *_scenario, int err)
{
    if (err)
    {
        printf(BOLDCYAN "%s" BOLDYELLOW ":%s: " BOLDRED "FAIL!\n" RESET,
               _testName, _scenario);
    }
    else
    {
        printf(BOLDCYAN "%s" BOLDYELLOW ":%s: " BOLDGREEN "SUCSSES \n" RESET, _testName, _scenario);
    }
}

static int IsPrior(const void *_data1, const void *_data2)
{
    return *(size_t *)_data1 > *(size_t *)_data2;
}

static int OperationForTask(void *arg)
{
    printf("i operasion with %s\n",(char *)arg);
    return 1;
}