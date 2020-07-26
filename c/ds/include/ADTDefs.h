#ifndef __ADT_DEFS_H__
#define __ADT_DEFS_H__

typedef enum 
{
    ERR_OK,
    ERR_GENERAL,
    ERR_NOT_INITIALZED,
    ERR_ALLOCTAION_FAILED,
    ERR_UNDERFLOW,
    ERR_OVERFLOW,
    ERR_WRONG_INDEX,
    ERR_STACK_IS_EMPTY,
    ERR_DATA_EXSIST,
    ERR_EMPTY_HEAP,
        
}ADTErr;

void HandleErr(ADTErr errNum, char *msg);

#endif /*ADT_DEFS_H */
