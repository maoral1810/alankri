#include <stddef.h> /* size_t */
#include "sorts.h"

#define NOT_NEED_SORTING 0
#define FORWARD 1
#define BACKWARD -1

static int BubbleForward(void **_arr, LessFunc _lessFanc, size_t _size);
static int Bubble(void **_arr, LessFunc _lessFanc, size_t _begin, 
                  size_t _end, int _direction);
static void SwapPointers(void **_x, void **_y);

void BubbleSort(void **_arr, size_t _size, LessFunc _lessFanc)
{  
    if(_arr == NULL || _size < 2)
    {
        return;
    }

    while(_size > 0)
    {
        if(NOT_NEED_SORTING == BubbleForward(_arr, _lessFanc, --_size))
        {
            return;
        }
    }
}  

void ShakeSort(void **_arr, size_t _size, LessFunc _lessFanc)
{
    size_t begin = 0;
    size_t end = _size - 1;

    if(_arr == NULL || _size < 2)
    {
        return;
    }

    while(_size > 0)
    {
        if(NOT_NEED_SORTING == Bubble(_arr, _lessFanc, begin, --end, FORWARD))
        {
            return;
        }

        if(NOT_NEED_SORTING == Bubble(_arr, _lessFanc, ++begin, end, BACKWARD))
        {
            return;
        }
    }
}

static int Bubble(void **_arr, LessFunc _lessFanc, size_t _begin, 
                  size_t _end, int _direction)
{
    int needsSorting = 0;
    size_t j;

    if(_direction == FORWARD)
    {
        while (_begin < _end)
        {
            if(_lessFanc(_arr[_begin] , _arr[_begin + 1]))
            {
                SwapPointers(&_arr[_begin] , &_arr[_begin + 1]);
                needsSorting = 1;
            }

            ++_begin;
        }
    }

    else
    {
        while(_end > _begin)
        {
            if(_lessFanc(_arr[_end - 1] , _arr[_end]))
            {
                SwapPointers(&_arr[_end] , &_arr[_end - 1]);
                needsSorting = 1;
            }

            --_end;
        }
    }
    
    return needsSorting;
}


static int BubbleForward(void **_arr, LessFunc _lessFanc, size_t _size)
{
    int needsSorting = 0;
    size_t j;

    for (j = 0; j < _size; ++j)
    {
        if(_lessFanc(_arr[j] , _arr[j + 1]))
        {
            SwapPointers(&_arr[j] , &_arr[j + 1]);
            needsSorting = 1;
        }
    }

    return needsSorting;
}

static void SwapPointers(void **_x, void **_y)
{
    void *savePointer = *_x;
    *_x = *_y;
    *_y = savePointer;
}