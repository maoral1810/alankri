#ifndef __PRIORITYQ_H
#define __PRIORITYQ_H

typedef struct PQ PQ;
typedef int(*CompereFunction)(const void *_data1, const void *_data2);

typedef enum
{
    PQ_SUCSSES,
    PQ_NOT_INITIALIZE,
    PQ_UNDERFLOW
}pqErr;

PQ *PQCreate(CompereFunction _isPrior);
void PQDestroy(PQ *_pQueue);
pqErr PQEnquqe(PQ *_pQueue, void *_value);
pqErr PQDequeue(PQ *_pQueue, void **_pValue);
size_t PQSize(PQ *_pQueue);

#endif  /*__PRIORITYQ_H */