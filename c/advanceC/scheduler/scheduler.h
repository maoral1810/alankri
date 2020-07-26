#ifndef __SCHEDULER_H
#define __SCHEDULER_H

#include <stddef.h>     /* size_t */
#include "task.h"
typedef struct Scheduler Scheduler;

typedef enum 
{
    SCH_SUCSSES,
    SCH_NOT_INITIALIZE,
    SCH_ALLOCATION_FAILED,
    SCH_TASK_INSERT_FAILED
}SchErr;
/*
    the function is for container use.
    
    input:
        data1 - pointer to data 
        data2 - pointer to data
        
    output:
        return TRUE if data 1 is prior or FALSE otherwise
*/
typedef int (*PriorFunction)(const void *_data1, const void *_data2);

/*
    Create a new Scheduler, returns a reference to it NULL on failure.
*/
Scheduler *SchCreate(PriorFunction _IsPrior);

/*
Destroy a given Scheduler.
    All tasks will me erased, all references will become invalid.

    Arguments:
            sch - pointer to Scheduler

    complexity O(n)
*/
void SchDestroy(Scheduler *_sch);

/*
Returns number of tasks in a given scheduler.

    Arguments:
        sch - the scheduler.
    
    output:
        return the number of tasks in scheduler.
    
    error:
        if scheduler NULL return 0.

    complexity O(n)
*/
size_t SchSize(const Scheduler *_sch);

/*
    Add a new task to a given scheduler.

    Arguments:
        sch         - the scheduler
        interval    - milliseconds between calls to opt
        operation   - task function
        arg         - any other things needed for user to perform operation

    output:
        SchErr - SCH_SUCSSES
    
    errors:
        SCH_NOT_INITIALIZE      - if sch or interval or operation are NULL
        SCH_ALLOCATION_FAILED   - if TaskCreate failed
        SCH_TASK_INSERT_FAILED  - if insert task to the container failed

    complexity O(log(n))
*/
SchErr SchAdd(Scheduler *_sch, Time _interval, OperationFunc _operation, void *_arg);

/*
    Start scheduler

    Blcoks thread indifferently

    Arguments:
        sch - scheduler

    output:
        SchErr - SCH_SUCSSES
    
    errors:
        SCH_NOT_INITIALIZE - if sch is NULL
    
*/
SchErr SchRun(Scheduler *_sch);

#endif /* __SCHEDULER_H */  
