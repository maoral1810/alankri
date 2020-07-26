#ifndef __TIMER_H
#define __TIMER_H

#include <stddef.h> /*size_t */

typedef long int Time;
/* 
    the function get the current time

    output:
       	TIME - the current time 
*/
Time GetTime();
/*
	the function suspend task if needed
	
	return current Time of system  
*/
void GoToSleep(Time _runTime);
/*
	the function update the next time to run for task
	
	input:
		interval - the offset for next time to run from current time
		
	output:
		the next time to run for task
*/

Time UpdateNextTimeToRun(Time _interval);
/*
	the function get the start time and save it  
*/
void GetStartTime();
/*
	print time
*/

int TimeCompere(Time _now , Time _runTime);

void PrintTime(Time _time);

#endif /*__TIMER_H*/
