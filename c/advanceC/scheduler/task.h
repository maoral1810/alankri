#ifndef __TASK_H
#define __TASK_H

#include "timer.h" /* Time */

typedef struct Task Task;
/*
    return signals to task - 0 to keep running, !0 to end
*/
typedef int (*OperationFunc)(void *_arg);

/*
    create a task 

    inputs:
        interval - run cycale(run every interval)
        operation - operation function
        arg - arguments of operation function

    output:
        retrun pointer to task
    
    errors:
        return NULL if allocation failed

*/
Task *TaskCreate(Time interval ,OperationFunc operation ,void *arg);
/*
    destroy a task 

    inputs:
        task - pointer to task
*/
void TaskDestroy(Task *_task);
/*
    the function run tasks by using operasion function 

    input:  
        task- the task to run by the schedular
    
    output:
        return 0 if task need to run again
    
    error:
        return !0 if task finish  
*/
int TaskRun(Task *_tasks);
/* 
    the function update the next time to run in task

    input:
        task - pointer to task
*/
void TaskUpdateTime(Task *_task);
/* 
    the function return the next time to run in a specific task

    input:
        task - pointer to task
    
    output:
        return the next time to run for specific task
*/
Time TaskNextRuntime(const Task *_task);

void PrintTask(Task *_task);

#endif /*__TASK_H */