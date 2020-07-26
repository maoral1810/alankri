#include "timer.h"

typedef enum
{
	trace,
	error,
	fatalError,
	
}logType;

#define ZLOG(type,str)(ZLogWrite(__FILE__, __LINE__, __func__, type, GetTime(), str))

void ZLogWrite(const char *_fileName,  const int _lineNumber , const char *_funcName,  logType _type, Time _time, char *_msg);
void ZLogInit(char *_fileName);
void ZLogClose();



