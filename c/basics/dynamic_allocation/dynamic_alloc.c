#include <stdio.h>  /*printf         */
#include <stdlib.h> /* malloc , free */
#include "dynamic_alloc.h"


#define ARR_LENGTH(x)(sizeof(x) / sizeof(x[0]))
/* static functions */
static void PrintArray(int *arr, int len);
static int CheckInsertParameters(int **arr, int *size, int *num_of_elements);
static int CheckDeleteParameters(int *arr, int *data, int *num_of_elements);

void TryMalloc(void)
{
    int i = 0;
    int *arr = (int *)malloc(sizeof(int) * N);
    
    if(arr == NULL)
    {
        return ;
    }

    for(i = 0; i < N; ++i)
    {
        int num = 0;

        scanf("%d",&num);
        arr[i] = num;
    }

    PrintArray(arr,  N);

    free(arr);
    arr = NULL;
}

int *DynamicArrayCreate(int size)
{
    int *arr_ptr = NULL;
    
    if(size < 0)
    {
        return NULL;
    }

    arr_ptr = (int *)malloc(sizeof(int) * size);

    return arr_ptr;
}

void DynamicArrayDestroy(int *DynamicArrayPtr)
{
    if(DynamicArrayPtr != NULL)
    {
        free(DynamicArrayPtr);
    }
}

int DynamicArrayInsert(int **DynamicArrayPtr, int data, int *DaSize, 
                       int *DaNumOfElements, int IncBlockSize)
{
    int status = OK;
    
    status = CheckInsertParameters(DynamicArrayPtr, DaSize, DaNumOfElements);
    if (status == OK)
    {
        if(*DaSize == *DaNumOfElements)
        {
            int *save_arr = *DynamicArrayPtr;
            
            /* check if have place in block and if can realloc him */
            if(IncBlockSize <= 0)
            {
                return OVERFLOW;
            }

            *DynamicArrayPtr = (int *)realloc(*DynamicArrayPtr, 
                                    (IncBlockSize + *DaSize) * sizeof(int));
            
            if(*DynamicArrayPtr == NULL)
            {
                *DynamicArrayPtr = save_arr;
                return REALLOC_FAILED; 
            }
            
            *DaSize += IncBlockSize;
        }
 
        (*DynamicArrayPtr)[*DaNumOfElements] = data; /*TODO check places */
        ++(*DaNumOfElements); /* increment NumOfElements By 1 */
    }

    return status;
}

int DynamicArrayDelete(int *DynamicArrayPtr, int *data, int *DaNumOfElements)
{
    int status = CheckDeleteParameters(DynamicArrayPtr, data, DaNumOfElements);

    if (status == OK)
    {
        if(*DaNumOfElements == 0)
        {
            return UNDERFLOW;
        }

        *data = DynamicArrayPtr[*DaNumOfElements];
        --(*DaNumOfElements); 
    }

    return status;
}

/* =================== static functions ====================== */
static void PrintArray(int *arr, int len)
{
    int i = 0;

    for (i = 0; i < len; ++i)
    {
        printf("%d," ,arr[i]);
    }

    putchar('\n');
}

static int CheckInsertParameters(int **arr, int *size, int *num_of_elements)
{
    int status = OK;

    if (arr == NULL)
    {
        return NOT_INITILIZE;
    }
    
    if(*arr == NULL || size == NULL || num_of_elements == NULL)
    {
        status =  NOT_INITILIZE;
    }
    
    if(*size <= 0 || *num_of_elements < 0)
    {
        status = INVALIV_INPUT;
    }

    return status;
}

static int CheckDeleteParameters(int *arr, int *data, int *num_of_elements)
{
    int status = OK;

    if(arr == NULL || data == NULL || num_of_elements == NULL)
    {
        status =  NOT_INITILIZE;
    }

    return status;
}
