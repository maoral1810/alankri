#include <stdio.h>
#include <assert.h>

#include "arrays.h"

static void Swap(int *a, int *b);
static void BubleOddNum(int *arr, int index, int insert_index);
static int ChackParmeters(int *arr ,unsigned int size, void *res);
static int CountElement(unsigned int index, int *arr, unsigned int size);

#define SWAP(x,y,type)\
    {\
    type temp = x;\
    x = y;\
    y = temp;\
}

int CalcAvg(int *arr, unsigned int size, double *avg)
{
    unsigned int i = 0;
    int status = ChackParmeters(arr, size, avg);
    
    for (; i < size; ++i)
    {
        *avg += (double)arr[i] / size;
    }
    
    return status;
}

int FindMostReturnNumber(int *arr, unsigned int size, int *res)
{
    unsigned int i = 0;
    int max_count = 0;
    int status = ChackParmeters(arr, size, res);
   
    if(!status)
    {
        for (i = 0; i < size; ++i)
        {
            int counter = CountElement(i, arr, size);
           
            if (counter > max_count)
            {
                *res = arr[i];
                max_count = counter;
            }
        }
    }

    return status;
}

int OrderArray(int *arr, unsigned int size, int *res)
{
    unsigned int odd_index = 0;
    unsigned int even_index = 0;
    int even_counter = 0;
    int status = ChackParmeters(arr,size,res);

    if (!status)
    {
        while (odd_index < size && even_index < size)
        {
            /* find odd */
            for(; (!(arr[odd_index] % 2)) && odd_index < size ; ++odd_index){} 
            
            /* find even */
            for(; (arr[even_index] % 2) && even_index < size; ++even_index){} 
            
            if(odd_index < size && even_index < size)
            {
                ++even_counter;
                SWAP(arr[odd_index], arr[even_index],int);
                BubleOddNum(arr, even_index, odd_index + 1);
            }
        }
    }

    return status;
}

void BubbleSort(int *arr, size_t size)
{
	register size_t each_element = 0;
	register size_t not_sorted = 0;

	assert(arr);

	for (each_element = 0; each_element < size; ++each_element)
	{
		int needs_sorting = 0;
		size_t not_sorted_size = size - each_element - 1;

		for (not_sorted = 0; not_sorted < not_sorted_size; ++not_sorted)
		{
			if (arr[not_sorted] > arr[not_sorted + 1])
			{
				Swap(&(arr[not_sorted]), &arr[not_sorted + 1]);
				needs_sorting = 1;
			}
		}
		if (!needs_sorting)	
		{
			return;	
		}
	}
}

void BubbleSortWithMacro(int *arr, size_t size)
{
	register size_t each_element = 0;
	register size_t not_sorted = 0;

	assert(arr);

	for (each_element = 0; each_element < size; ++each_element)
	{
		int needs_sorting = 0;
		size_t not_sorted_size = size - each_element - 1;

		for (not_sorted = 0; not_sorted < not_sorted_size; ++not_sorted)
		{
			if (arr[not_sorted] > arr[not_sorted + 1])
			{
				SWAP((arr[not_sorted]), arr[not_sorted + 1],int);
				needs_sorting = 1;
			}
		}
		if (!needs_sorting)	
		{
			return;	
		}
	}
}

/* ================= Helpful Functions ================== */

static void Swap(int *a, int *b)
{
    int save_data = *a;
    *a = *b;
    *b = save_data;
}

static void BubleOddNum(int *arr, int index, int insert_index)
{
    for( ; index > insert_index; --index)
    {
        Swap(&arr[index],&arr[index -1]);
    }
}

static int ChackParmeters(int *arr ,unsigned int size, void *res)
{
    if (NULL == arr && NULL == res)
    {
        return INPUT_ERROR;
    }

    if(!size)
    {
        return SIZE_ERROR;
    }

    return OK;
}

static int CountElement(unsigned int index, int *arr, unsigned int size)
{
    int counter = 1;
    unsigned int i = index + 1;

    for(; i < size; ++i)
    {
        if (arr[index] == arr[i])
        {
            ++counter;
        }
    }

    return counter;
}


