#ifndef __ADT_DEFS_H__
#define __ADT_DEFS_H__

typedef enum 
{
    ERR_OK,
    ERR_OPEN_FILE,
    ERR_ALLOCTAION_FAILED,
    ERR_OVERFLOW,
    ERR_NOT_INISILIZE,
    ERR_FILE_NULL,
    ERR_NOT_VALID_INPUT,
    REALLOC_FAILED,
    ERR_READ_AND_WRITE

}Err;

void HandleErr(Err errNum, char *msg);

#endif /*ADT_DEFS_H */
