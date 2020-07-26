#include <stdio.h>  /* NULL        */
#include <stdlib.h> /* malloc, free */
#include "ad.h"

#define MAGIC_NUM 0xBFFBFFBF

/* checking functions */  
static ADerr CheckValidMeeting(int _beginTime, int _endTime);
static ADerr CheckAdParam(calender_t *_ad);
static ADerr CheckParams(calender_t *_ad, meeting_t *_meeting);
static ADerr CheckSizes(int _size, int _incSize);

/* sort function */
static void RotateRight(calender_t *_ad, size_t index);
static void RotateLeft(calender_t *_ad, size_t index);

static ADerr AllocNewMemory(calender_t *_ad);
static ADerr InsertMeetingToAd(calender_t *_ad, meeting_t *_meeting , size_t _index);
static meeting_t *FindMeeting(calender_t *_ad, float _beginTime, size_t *_index);

/* boolean functions */
static int IsFullCalender(calender_t *_ad);
static int IsEndOfMeetArray(calender_t *_ad, int _index);
static int IsInsertBefore(calender_t *_ad, meeting_t *_meeting, int _index);
static int IsOverlap(calender_t *_ad, meeting_t *_meeting, int _index);
static int IsEmptyCalander(calender_t *_ad);

struct calender_t
{
    meeting_t **metArray;
    int calSize;
    int calIncSize;
    int numOfMeeting;
    unsigned int magicNumber;
};

struct meeting_t
{
    float beginTime;
    float endTime;
    int room;
};

calender_t *CreateAD(int _size, int _inc_size)
{
    meeting_t **metArray = NULL;
    calender_t *ad = NULL;
    
    if (ERR_OK != CheckSizes(_size, _inc_size))
    {
        return NULL;
    }

    ad = (calender_t *)malloc(sizeof(calender_t));
    if (NULL == ad)
    {
        return NULL;
    }

    metArray = (meeting_t **)malloc(sizeof(meeting_t *) * _size);

    if (NULL == metArray)
    {
        free(ad);
        ad = NULL;
        return NULL;
    }

    ad->metArray = metArray;
    ad->calIncSize = _inc_size;
    ad->numOfMeeting = 0;
    ad->calSize = _size;
    ad->magicNumber = MAGIC_NUM;

    return ad;
}

void DestroyAD(calender_t *_ad)
{
    int i = 0;

    if(NULL != _ad)
    {
        if(_ad->magicNumber == MAGIC_NUM && NULL != _ad->metArray)
        {
            _ad->magicNumber = 0;
            /* check if calender isn't empty */
            if (_ad->numOfMeeting != 0)
            {
                for(i = 0;  i < _ad->numOfMeeting; ++i)
                {
                    if (NULL != _ad->metArray[i])
                    {
                        free(_ad->metArray[i]);
                    }
                }
            }

            free(_ad->metArray);
            _ad->metArray = NULL;

            free(_ad);
        }
    }
}

meeting_t *CreateMeeting(float _beginTime, float _endTime, int _room)
{
    meeting_t *meeting = NULL;

    int status = CheckValidMeeting(_beginTime, _endTime);

    if(status == ERR_OK)
    {
        meeting = (meeting_t *)malloc(sizeof(meeting_t));
        
        if(NULL == meeting)
        {
            return NULL;
        }

        meeting->beginTime = _beginTime;
        meeting->endTime = _endTime;
        meeting->room = _room;
    }
    
    return meeting;
}

ADerr FindAppointment(calender_t *_ad, float _meetingTime)
{
    ADerr status = CheckAdParam(_ad);
    size_t i = 0;

    if(ERR_OK == status)
    {
        status = (NULL == FindMeeting(_ad, _meetingTime, &i)) ? 
        APPOINTMENT_NOT_FOUND : APPOINTMENT_FOUND;
    }

    return status;
}

ADerr InsertAppointment(calender_t *_ad, meeting_t *_meeting)
{
    ADerr status = CheckParams(_ad, _meeting);
    size_t i = 0;

    if(ERR_OK == status)
    {
        /* alloc new memory for insert meeting */
        if(IsFullCalender(_ad))
        {
            status = AllocNewMemory(_ad);
            if(status != ERR_OK)
            {
                return status;
            }
        }
        
        /* run until the place to insert */
        for(;i < _ad->numOfMeeting  && _ad->metArray[i]->endTime < _meeting->beginTime; ++i){}

        if(IsEndOfMeetArray(_ad, i))/* todo check ovelap */
        {
            status = InsertMeetingToAd(_ad, _meeting, i);
        }
        
    /* 1) if start of the meeting is bigger then the end of new metting  
       2) the end of previos meeting is small then the begin of new meeting */
        else if(IsInsertBefore(_ad, _meeting, i))
        {
            status = InsertMeetingToAd(_ad, _meeting, i); 
        }
                
        else if(IsOverlap(_ad, _meeting, i))
        {
            status = OVELAPPING;
        }
    }

    return status;
}

ADerr RemoveAppointment(calender_t *_ad, float _beginTime)
{
    ADerr status = CheckAdParam(_ad);
    meeting_t *meetToRemove = NULL;
    size_t index = -1;

    if(_beginTime < 0 || _beginTime > 24)
    {
        status = INVALIV_INPUT;
    }

    if(ERR_OK == status)
    {
        if(IsEmptyCalander(_ad)) /* if calender is empty */
        {
            return UNDERFLOW;
        }

        meetToRemove = FindMeeting(_ad, _beginTime, &index);
        
        if(NULL == meetToRemove) 
        {
            status = APPOINTMENT_NOT_FOUND;
        }
        else
        {
            free(meetToRemove);
            meetToRemove = NULL;

            RotateLeft(_ad, index);
            --_ad->numOfMeeting; 
        }
    }
    
    return status;
}

void PrintAd(calender_t *_ad)
{
    int i = 0;
    if(_ad != NULL)
    {
        printf("-<>-<> dairy data -<>-<>\n");
        printf("calender size: %d \n", _ad->calSize);
        printf("increment block size: %d \n", _ad->calIncSize);
        printf("number of meetings: %d \n", _ad->numOfMeeting);
        printf("-<>-<>-<>-<>-<>-<>-<>-<>\n\n");
    
        for(i = 0; i < _ad->numOfMeeting; ++i)
        {
            printf("[%d]\tbegin time: %.2f\t end time: %.2f \t room:%d\n",
                    i, _ad->metArray[i]->beginTime, _ad->metArray[i]->endTime,
                    _ad->metArray[i]->room);
        }
        return;
    }

    printf(BOLDRED"there is no dairy");
}

ADerr SaveDiary(calender_t *_ad, char *_fileName)
{
    FILE *meetFile = NULL;
    int meetingSize = 0;
    int i = 0;

    if(_ad == NULL || _fileName == NULL)
    {
        return NOT_INITILIZE;
    }

    meetFile = fopen(_fileName, "w");
    
    if(meetFile == NULL)
    {
        return OPEN_FILE_FAILED;
    }

    meetingSize = _ad->numOfMeeting;
    
    fprintf(meetFile, "%d\n",_ad->numOfMeeting);
    
    for(; i < meetingSize; ++i)
    {
        fprintf(meetFile,"%.2f\t%.2f\t%d\n"
                    ,   _ad->metArray[i]->beginTime, 
                        _ad->metArray[i]->endTime,
                        _ad->metArray[i]->room);
    }

    fclose(meetFile);

    return ERR_OK;
}

ADerr LoadDiary(calender_t *_ad, char *_fileName)
{
    FILE *meetFile = NULL;
    ADerr status = ERR_OK;
    int meetingSize = 0;
    int i = 0;
    
    if(_ad == NULL || _fileName == NULL)
    {
        return NOT_INITILIZE;
    }

    meetFile = fopen(_fileName, "r");

    if(meetFile == NULL)
    {
        return OPEN_FILE_FAILED;
    }
    
    fscanf(meetFile,"%d\n",&meetingSize);

    for(; i < meetingSize; ++i)
    {
        float beginTime = 0;
        float EndTime = 0;
        int room = 0;
        meeting_t *meeting = NULL;

        fscanf(meetFile,"%f\t%f\t%d\n"
                       ,&beginTime, 
                        &EndTime,
                        &room);
        meeting = CreateMeeting(beginTime, EndTime, room);
        if(meeting == NULL)
        {
            return MEETING_CREATE_FAILED;
        }

        status = InsertAppointment(_ad, meeting);
        if(status != ERR_OK)
        {
            return status;
        }
    }

    fclose(meetFile);

    return ERR_OK;
}

/* ----------------- helpful functions --------------------- */
static ADerr CheckValidMeeting(int _beginTime, int _endTime)
{
    if((_beginTime < 24 && _beginTime > 0) && 
       (_endTime < 24 && _endTime > 0) &&
       _beginTime < _endTime)
      
    {
        return ERR_OK;
    }

    return INVALIV_INPUT;
}

static ADerr CheckAdParam(calender_t *_ad)
{
    if(NULL == _ad || NULL == _ad->metArray)
    {
        return NOT_INITILIZE;
    }

    return ERR_OK;
}

static ADerr CheckParams(calender_t *_ad, meeting_t *_meeting)
{
    ADerr status = NOT_INITILIZE;

    if(NULL != _ad && MAGIC_NUM == _ad->magicNumber && NULL != _meeting)
    {
        status = CheckValidMeeting(_meeting->beginTime, _meeting->endTime);
    }

    return status;
}

static ADerr CheckSizes(int _size, int _incSize)
{
    if( _size >= 0 && _incSize >= 0)
    {
        return ERR_OK;
    }

    return INVALIV_INPUT;
}

static ADerr AllocNewMemory(calender_t *_ad)
{
    meeting_t **saveAd = NULL;

    if(0 == _ad->calIncSize)
    {
        return OVERFLOW;
    }
    
    saveAd = (meeting_t **)realloc(_ad->metArray, 
                        (_ad->calSize + _ad->calIncSize) * (sizeof(meeting_t *)));
        
    if(NULL != saveAd)
    {
        _ad->metArray = saveAd;
        _ad->calSize += _ad->calIncSize;
        return ERR_OK; 
    }
    
    return REALLOC_FAILED;
}

static ADerr InsertMeetingToAd(calender_t *_ad, meeting_t *_meeting , size_t _index)
{
    ADerr status = CheckParams(_ad, _meeting);
    
    if( ERR_OK == status)
    {
        RotateRight(_ad, _index); /* rotate all the meeting 1 place right until index*/
        _ad->metArray[_index] = _meeting;
        ++_ad->numOfMeeting;
    }

    return status;
}

static meeting_t *FindMeeting(calender_t *_ad, float _beginTime, size_t *_index)
{
    ADerr status = CheckAdParam(_ad);
    int i = 0;

    if(ERR_OK == status)
    {
        for(;i < _ad->numOfMeeting; ++i)
        {
            if(_ad->metArray[i]->beginTime == _beginTime)
            {
                *_index = i;
                return _ad->metArray[i];
            }
        }
    }

    return NULL;
}

static void RotateLeft(calender_t *_ad, size_t index)
{
    size_t size = _ad->calSize;
    
    for(; index < size ;++index)
    {
        _ad->metArray[index] = _ad->metArray[index + 1]; 
    }
}

static void RotateRight(calender_t *_ad, size_t index)
{
    size_t i = 0;

    for(i = _ad->numOfMeeting; i < index ; --i)
    {
        _ad->metArray[i] = _ad->metArray[i - 1]; 
    }
    
}

static int IsFullCalender(calender_t *_ad)
{
    if(NULL != _ad)
    {
        return (_ad->calSize == _ad->numOfMeeting);
    }

    return 0;
}

static int IsEndOfMeetArray(calender_t *_ad, int _index)
{
    if(NULL != _ad)
    {
        return(_index == _ad->numOfMeeting);
    }
    
    return 0;
}

static int IsInsertBefore(calender_t *_ad, meeting_t *_meeting, int _index)
{
    if(_ad != NULL)
    {
        return (_ad->metArray[_index]->beginTime > _meeting->endTime && 
             _ad->metArray[_index - 1]->endTime < _meeting->beginTime);
    }

    return 0;
}

static int IsOverlap(calender_t *_ad, meeting_t *_meeting, int _index)
{
    if(_ad != NULL)
    {
        return (_ad->metArray[_index]->beginTime <=_meeting->endTime || 
                _ad->metArray[_index - 1]->endTime >= _meeting->beginTime);
    }

    return 0;
}

static int IsEmptyCalander(calender_t *_ad)
{
    if(_ad != NULL)
    {
        return (_ad->numOfMeeting == 0);
    }

    return 0;
}




 