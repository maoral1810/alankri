#ifndef __AD_H__
#define __AD_H__

#include "ADerr.h" /* errors */
#include "colors.h"

typedef struct calender_t calender_t;
typedef struct meeting_t meeting_t;

calender_t *CreateAD(int _size, int _inc_size);
/*
    the function allocated calender and return a pointer to calender

    input:
        size     - the size of array of meetings
        inc_size - block realloc factor

    output:
        pointer to calender

    error:
        return NULL if alocation failed 
*/
void DestroyAD(calender_t *_ad);
/* 
    the function free calender 

    input:
        ad - pointer to calender
    
    output:
        
    error:
*/   

meeting_t *CreateMeeting(float _beginTime, float _endTime, int _room);
/*
    the function allocated meeting and return a pointer to meeting

    input:
        begin_time - begin time of meetings 
        end_time   - end time of meetings 
        room       - room number of meeting

    output:
        pointer to meetings

    error:
        return NULL if alocation failed 
*/

ADerr InsertAppointment(calender_t *_ad, meeting_t *_meeting);
/* 
    the function insert meeting to calender 

    input:
        ad - pointer to calender 
        meeting - meeting to insert

    output:
        ADTErr 

    error:
        OK - if the meeting insert to calender
        REALLOC_FAILED - if alloc new memory is failed 
        NOT_INITILIZE - if one of the pointers are NULL
        OVERFLOW - if there is no place for meeting and the increment size is 0
*/
ADerr RemoveAppointment(calender_t *_ad, float _beginTime);
/* 
    the function remove meeting from calender 

    input:
        ad - pointer to calender 
        meeting - meeting to removing

    output:
        ADTErr 

    error:
        OK - if the meeting remove from calender
        APPOINTMENT_NOT_FOUND - if there is no match for meeting in calender 
        NOT_INITILIZE - if one of the pointers are NULL
*/
ADerr FindAppointment(calender_t *_ad, float _meetingTime);
/*
    the function serach meeting in calender 

    input:
        ad - pointer to calender 
        meetingTime - begin time of meetings 
        meeting     - pointer to return meeting

    output:
        ADTErr 

    error:
        OK - if there is a meeting in calender
        APPOINTMENT_NOT_FOUND - if there is no match for meeting in calender 
        NOT_INITILIZE - if one of the pointers are NULL
*/
void PrintAd(calender_t *_ad);
/* 
    the function print all meeting in calender

    input:
        ad - pointer to calender 

    output:

    error:
  
*/

ADerr SaveDiary(calender_t *_ad, char *_fileName);
/* 
    the function write to file all meeting in calender

    input:
        ad - pointer to calender
        fileName - name of the file 

    output:
        ERR_OK on sucsses

    error:
        OPEN_FILE_FAILED - if failed in open the file
        INVALIV_INPUT - if ad & fileName is NULL

*/
ADerr LoadDiary(calender_t *_ad, char *_fileName);
/* 
    the function insert meetings to calander from file

    input:
        ad - pointer to calender
        fileName - name of the file 

    output:
        ERR_OK on sucsses

    error:
        OPEN_FILE_FAILED - if failed in open the file
        INVALIV_INPUT - if ad & fileName is NULL

*/
#endif /*__AD_H__*/