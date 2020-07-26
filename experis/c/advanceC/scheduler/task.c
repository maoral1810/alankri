#include <stddef.h> 		/* size_t			*/
#include <assert.h>		    /* assert			*/
#include <stdlib.h>			/* malloc , free 	*/
#include <stdio.h>          /* printf           */

#include "task.h"
#include "timer.h"
#include "scheduler.h"
#include "ZLog.h"

#define RUN_NOW 0

struct Task
{
    Time interval;
    OperationFunc operation;
    void *arg;
    Time nextRunTime;
};

Task *TaskCreate(Time interval ,OperationFunc operation ,void *arg)
{
    Task *newTask = (Task *)malloc(sizeof(Task));

    if (NULL == newTask)
    {
        ZLOG(fatalError,"allocation failed");
        return NULL;
    }

    newTask->interval = interval;
    newTask->operation = operation;
    newTask->arg = arg;
    newTask->nextRunTime = GetTime() + interval;
    ZLOG(trace, "task create");
    return newTask;
}

void TaskDestroy(Task *_task)
{
    assert(_task);
    ZLOG(trace,"task finish! task destroy");
    free(_task);
    _task = NULL;
}

int TaskRun(Task *_task)
{
    assert(_task);
    ZLOG(trace,"task run");
    if(TimeCompere(GetTime(), _task->nextRunTime) != RUN_NOW)
    {
        GoToSleep(_task->nextRunTime);
    }

    return (_task->operation(_task->arg));
}

void TaskUpdateTime(Task *_task)
{
    assert(_task);

    _task->nextRunTime = UpdateNextTimeToRun(_task->interval);
}

void PrintTask(Task *_task)
{
	printf("\ninterval: ");
	PrintTime(_task ->interval);
	printf("\nnext Run Time: ");
	PrintTime(_task ->nextRunTime);
}



