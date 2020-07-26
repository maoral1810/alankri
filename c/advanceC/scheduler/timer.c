#define _POSIX_C_SOURCE (0xFFFFFFFFFFF)
#include <stdio.h> /* printf */

#include <time.h>   /*timespec , clock_gettime  */
#include <unistd.h> /* usleep                   */
#include "timer.h"
#include "ZLog.h"
#define SEC_TO_MILISEC(x)( (x) * 1000)
#define MILI_TO_MICRO(x)( (x) * 1000)
static Time g_startTime = 0;

/* timer is in resoulosion of miliseconeds */

void GetStartTime()
{
    struct timespec SystemTime;
    clockid_t clockId = CLOCK_REALTIME;

    if(!clock_gettime(clockId, &SystemTime))
    {
        g_startTime = SEC_TO_MILISEC(SystemTime.tv_sec);
    }
}

Time GetTime()
{
    Time time = 0;
    struct timespec SystemTime;
    clockid_t clockId = CLOCK_REALTIME;

    if(!g_startTime)
    {
    	GetStartTime();
    }
    
    if(!clock_gettime(clockId, &SystemTime))
    {
        time = SEC_TO_MILISEC(SystemTime.tv_sec);
    }
    
    return (time - g_startTime);
}

void GoToSleep(Time _runTime)
{
    Time time = GetTime();
    
    if(time < _runTime)
    {
        ZLOG(trace, "go to sleep before running");
        usleep(MILI_TO_MICRO(_runTime - time));
    }
}

Time UpdateNextTimeToRun(Time _interval)
{
    ZLOG(trace,"update next time to run");
    return GetTime() + _interval;
}

int TimeCompere(Time _now , Time _runTime)
{
    return _now < _runTime;
}

void PrintTime(Time _time)
{
	printf("%ld",_time);
}
