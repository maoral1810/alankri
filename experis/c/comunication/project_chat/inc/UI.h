#ifndef __UI_H__
#define __UI_H__

#include "errors.h"

typedef enum
{
    CLIENT_REGITRATE = 1,
    CLIENT_LOGIN,
    EXIT,
    CLIENT_JOIN_GROUP,
    CLIENT_LEAVE_GROUP,
    CLIENT_GET_GROUPS,
    CLIENT_LOGUOT

}ManuSelection;

void PrintStatus(ERR _status);

void GetInput(char* _requestedField, char* _buffer, size_t _maxFieldSize, char _returnChar);

ManuSelection WelcomeMenuGetSelection();
ManuSelection HomeMenuGetSelection();


#endif /*__UI_H__*/