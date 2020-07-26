#include "ZLog.h"
#include "timer.h"

int main(void)
{
	ZLogInit("STS.log");
	
	ZLOG(error, "i am in test");

	ZLOG(error, "diffrent time");
	return 0;
}

