#ifndef __ADT_DEFS_H__
#define __ADT_DEFS_H__

typedef enum 
{
    ERR_OK,
    ERR_GENERAL,
    ERR_NOT_PALINDROME,
    ERR_ALLOCTAION_FAILED,


}ADTErr;

void HandleErr(ADTErr errNum, char *msg);

#endif /*ADT_DEFS_H */
