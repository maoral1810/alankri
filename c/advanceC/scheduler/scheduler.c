#include <stdlib.h> /*malloc , free */
#include "scheduler.h"
#include "priorityQ.h" /* Heap API */
#include "task.h"
#include "timer.h"
#include "ZLog.h"

#define FALSE 0
#define TRUE !FALSE
#define TASK_NOT_FINISH 0
#define MAGIC_NUMBER 0XACACACAC
#define MAGIC_DESTROY 0xBEDC0FFE
#define CHECK_SCH(sch)(sch != NULL && sch->magicNumber == MAGIC_NUMBER)

static SchErr SchAddCheckParam(Scheduler *_sch, size_t _interval, 
                               OperationFunc _operation);

struct Scheduler
{
    size_t magicNumber;
    PQ *m_PQ;
};

Scheduler *SchCreate(PriorFunction _IsPrior)
{
    Scheduler *newScheduler = (Scheduler *)malloc(sizeof(Scheduler));
    ZLogInit("Scheduler.log");
    if (NULL == newScheduler)
    {
        ZLOG(fatalError,"allocation failed");
        return NULL;
    }

    newScheduler->m_PQ = PQCreate(_IsPrior);

    if (NULL == newScheduler->m_PQ)
    {
        free (newScheduler);
        ZLOG(fatalError,"allocation failed");
        return NULL;
    }

    newScheduler->magicNumber = MAGIC_NUMBER;
    return newScheduler;
}

void SchDestroy(Scheduler *_sch)
{
    if(CHECK_SCH(_sch))
    {
		_sch->magicNumber = MAGIC_DESTROY;
		ZLOG(trace,"scheduler destroyed");
        PQDestroy(_sch->m_PQ);
		free(_sch);
    }
}

SchErr SchAdd(Scheduler *_sch, Time _interval, OperationFunc _operation, void *_arg)
{
    SchErr status = SchAddCheckParam(_sch, _interval, _operation);
    
    if(status == SCH_SUCSSES)
    {
		Task *newTask = TaskCreate(_interval, _operation, _arg);

		if (NULL == newTask)
		{
			return SCH_ALLOCATION_FAILED;
		}
        
		if(PQ_SUCSSES != PQEnquqe(_sch->m_PQ, newTask))
		{
			TaskDestroy(newTask);
			return SCH_TASK_INSERT_FAILED;
		}
        
        ZLOG(trace,"add task succsess");
    }

	return status;
}

size_t SchSize(const Scheduler *_sch)
{
    size_t counter = 0;

    if(CHECK_SCH(_sch))
    {
        counter = PQSize(_sch->m_PQ);
    }

    return counter;
}

SchErr SchRun(Scheduler *_sch)
{
    if(!CHECK_SCH(_sch))
    {
        return SCH_NOT_INITIALIZE;
    }

    while(1)
    {
        void *task;
        if(PQ_SUCSSES != PQDequeue(_sch->m_PQ, &task))
        {
            break;
        }
        
        if(TASK_NOT_FINISH == TaskRun((Task *)task))
        {
            TaskUpdateTime(task);
            PQEnquqe(_sch->m_PQ, task);
        }
        else
        {
            TaskDestroy(task);
        }
    }
    
    return SCH_SUCSSES;
}
/* --------------------static functions-----------------------*/
static SchErr SchAddCheckParam(Scheduler *_sch, size_t _interval, 
                               OperationFunc _operation)
{
    if(NULL != _sch && MAGIC_NUMBER == _sch->magicNumber && _interval != 0 && _operation != NULL)
    {
        return SCH_SUCSSES;
    }

    return SCH_NOT_INITIALIZE;  
}
