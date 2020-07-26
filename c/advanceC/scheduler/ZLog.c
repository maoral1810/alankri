#include <stdio.h> /* fprintf, fopen, fclose */
#include "ZLog.h"

static char *g_fileName = "defualt.log"; 
static FILE *fd = NULL;

void ZLogWrite(const char *_fileName,  const int _lineNumber , 
			   const char *_funcName,  logType _type, Time _time, char *_msg)
{
	if(fd == NULL)
	{
		fd = fopen(g_fileName,"a+" );
	}
	
	switch(_type)
	{
		case(trace):
			fputs("trace", fd);
			break;
			
		case(error):
			fputs("error", fd);
			break;
		
		case(fatalError):
			fputs("fatalError", fd);
			break;
	}	
		
		fprintf(fd,"%s %s %s%s %s %d %s %ld %s\n" , " in file: ", _fileName, " in function: " , _funcName, " in line: ", _lineNumber,"time:",_time ,_msg);
}

void ZLogInit(char *_fileName)
{
	g_fileName = _fileName;
}

void ZLogClose()
{
	fclose(fd);
}



