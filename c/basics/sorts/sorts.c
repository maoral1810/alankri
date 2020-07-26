#include <stddef.h> /* size_t       */
#include <stdlib.h> /* malloc, free */
#include "sorts.h"  /* sorts API    */
#include "stack.h"

/* static functions */
static void SwapData(Vector *_vector, size_t _x, size_t _y, int _xdata, int _ydata);
static void RecQuickSort(Vector *_vector, size_t _begin, size_t _end);
static size_t Partition(Vector *_vector, size_t _begin, size_t _end);
static size_t FindMin(Vector *_vector, size_t _from, size_t _to);
static void Merge(Vector *_vec, int *_arr, size_t _begin, size_t middle, size_t _end);
static void RecMargeSort(Vector *_vector, int *_arr, size_t _begin, size_t _end);
static int BubbleForward(Vector *_vector, int _begin, int _end);
static int Bubblebackward(Vector *_vector, int _begin, int _end);

/*----------------------------------------------------------------------------*/

ADTErr BubbleSort(Vector *_vector) 
{  
    register i, j;
    size_t size;

    if(NULL == _vector)
    {
        return ERR_NOT_INITIALZED;
    }

    VectorItemsNum(_vector, &size);

    if(size < 2)
    {
        return ERR_OK;
    }

    size -= 1;

    for (i = 0; i < size; ++i)      
    {
        if(1 != BubbleForward(_vector, i, size))
        {
            return ERR_OK;
        }
    }  
}  

ADTErr ShakeSort(Vector *_vector)
{
    register i, j;
    size_t size;
    size_t begin = 0;
    size_t end;

    if(NULL == _vector)
    {
        return ERR_NOT_INITIALZED;
    }

    VectorItemsNum(_vector, &size);

    if(size < 2)
    {
        return ERR_OK;
    }
    
    end = size -1;

    while(begin < end)      
    {
        if(1 != BubbleForward(_vector, begin, end))
        {
            return ERR_OK;
        }

        ++begin;

        if(1 != Bubblebackward(_vector, begin, end))
        {
            return ERR_OK;
        }

        --end;
    }

    return ERR_OK;
}

ADTErr QuickSort(Vector *_vector)
{
    ADTErr status = ERR_OK;
    size_t vectorSize;

    if (_vector == NULL)
    {
        return ERR_NOT_INITIALZED;
    }

    VectorItemsNum(_vector, &vectorSize);
    RecQuickSort(_vector, 0, vectorSize - 1);

    return ERR_OK;
}


ADTErr InsertionSort(Vector *_vector, size_t _gup)
{
    int firstData, secondData;
    size_t size, i, j;

    VectorItemsNum(_vector, &size);
    for(; _gup > 0; _gup /= 2)
    {
        for (i = _gup; i < size; i++)
        {
            for(j = i; j >= _gup; j -= _gup)
            {
                VectorGet(_vector, j - _gup, &firstData);
                VectorGet(_vector, j, &secondData);
                if(firstData < secondData)
                {
                    break;
                }
                SwapData(_vector, j - _gup, j, firstData, secondData);
            }
        }
    }
}

ADTErr ShellSort(Vector *_vector)
{
    size_t vectorSize;

    if (_vector == NULL)
    {
        return ERR_NOT_INITIALZED;
    }

    VectorItemsNum(_vector, &vectorSize);


    InsertionSort(_vector, vectorSize / 2);


    return ERR_OK;
}

ADTErr SelectionSort(Vector *_vector)
{
    size_t size,i,minIndex;
    int currentData;
    int minData ;

    if(_vector == NULL)
    {
        return ERR_NOT_INITIALZED;
    }

    VectorItemsNum(_vector, &size);

    if(size > 1)
    {
        for(i = 0; i < size; ++i)
        {
            minIndex = FindMin(_vector, i, size);
            
            VectorGet(_vector, minIndex, &minData);
            VectorGet(_vector, i, &currentData);
            SwapData(_vector, i, minIndex, currentData, minData);
        }
    }

    return ERR_OK;
}

ADTErr MargeSort(Vector *_vector)
{
    size_t size;
    int *arr;

    if(NULL == _vector)
    {
        return ERR_NOT_INITIALZED;
    }

    VectorItemsNum(_vector,&size);
    if(!size)
    {
        return ERR_OK;
    }

    arr = (int *)malloc(size * sizeof(int));
    if(arr == NULL)
    {
        return ERR_ALLOCTAION_FAILED;
    }

    RecMargeSort(_vector, arr, 0, size - 1);

    free(arr);

    return ERR_OK;
}

ADTErr CountingSort(Vector *_vector, int _max, int _min)
{
    size_t i, j, vectorSize;
    size_t range = _max - _min;
    int *arrShows = (int *)calloc(sizeof(int), sizeof(int) * (range + 1));
    int *arrCopy;
    int data;

    if(arrShows == NULL)
    {
        return ERR_ALLOCTAION_FAILED;
    }

    if(_max < _min)
    {
        return ERR_INVALID_INPUT;
    }
    
    VectorItemsNum(_vector, &vectorSize);
    
    arrCopy = (int *)malloc(sizeof(int) * (vectorSize));

    if(arrCopy == NULL)
    {
        return ERR_ALLOCTAION_FAILED;
    }
    
    /* make a histogram of show in show array */
    for(i = 0; i < vectorSize; ++i)
    {
        VectorGet(_vector, i, &data);
        ++arrShows[data - _min];
    }
    /* make array of shows */
    for(i = 1; i <= range; ++i)
    {
        arrShows[i] += arrShows[i - 1];  
    }
    /* make array resualt*/
    for(i = vectorSize - 1; i > 0; --i)
    {
        VectorGet(_vector, i, &data);
        arrCopy[arrShows[data - _min]] = data;
        --arrShows[data - _min];
    }

    for (i = 0; i < vectorSize; ++i)
    {
        VectorSet(_vector, i, arrCopy[i]);
    }

    return ERR_OK;
}

ADTErr ItarativeQuickSort(Vector *_vector)
{
    size_t vectorSize;
    Stack *stack = NULL;
    int newPivot;
    int begin;
    int end;

    if (_vector == NULL)
    {
        return ERR_NOT_INITIALZED;
    }

    VectorItemsNum(_vector, &vectorSize);
    stack = StackCreate(vectorSize,vectorSize);

    if(stack == NULL)
    {
        return ERR_ALLOCTAION_FAILED;
    }

    if(vectorSize < 2)
    {
        return ERR_OK;
    }

    StackPush(stack, 0);
    StackPush(stack, vectorSize - 1);

    while(!StackIsEmpty(stack))
    {
        StackPop(stack, &end);
        StackPop(stack, &begin);

        newPivot = (int)Partition(_vector, (size_t)begin, (size_t)end);

        if((newPivot-1 > begin))
        {
            StackPush(stack, begin);
            StackPush(stack, newPivot - 1);
        }
        if(newPivot + 1 < end)
        {         
            StackPush(stack, newPivot + 1);
            StackPush(stack, end);
        }
    }

    return ERR_OK;
}

/* -------------------------- static functions -----------------------------*/
static void RecMargeSort(Vector *_vector, int *_arr, size_t _begin, size_t _end)
{
    size_t mid = (_end + _begin) / 2; 

    if(_begin == _end)
    {
        return;
    }

    RecMargeSort(_vector, _arr, _begin, mid);
    RecMargeSort(_vector, _arr, mid + 1, _end);

    Merge(_vector, _arr,_begin, mid, _end); 
}

static void Merge(Vector *_vec, int *_arr, size_t _begin, size_t _middle, size_t _end)
{
    size_t i = _begin;
    size_t j = _middle + 1;
    size_t current = 0;

    int iData;
    int jData;


    for(;i <= _middle && j <= _end; ++current)
    {
        VectorGet(_vec, i, &iData);
        VectorGet(_vec, j, &jData);
        
        if(iData < jData)
        {
            _arr[current] = iData;
            ++i; 
        }
        else
        {
            _arr[current] = jData;
            ++j; 
        }
    }
    /* copy tail to end of array */
    for(;i <= _middle; ++i, ++current)
    {
        VectorGet(_vec, i ,&iData);
        _arr[current] = iData;
    }


    for(;j <= _end; ++j, ++current)
    {
        VectorGet(_vec, j ,&jData);
        _arr[current] = jData;
    }

    /* copy arr to vector */

    for(current = _begin, i = 0; current <= _end; ++current, ++i)
    {
        VectorSet(_vec, current, _arr[i]);
    }
}
static size_t Partition(Vector *_vector, size_t _begin, size_t _end)
{
    size_t low = _begin;
    size_t high = _end;
    int pivot;
    int highData;
    int lowData;

    VectorGet(_vector, _begin, &pivot);

    while (low < high)
    {
        VectorGet(_vector, low, &lowData);

        while (lowData <= pivot && low < _end)
        {
            ++low;
            VectorGet(_vector, low, &lowData);
        }

        VectorGet(_vector, high, &highData);

        while (highData > pivot)
        {
            --high;
            VectorGet(_vector, high, &highData);
        }

        if (low < high)
        {
            SwapData(_vector, low, high, lowData, highData);
        }
    }

    SwapData(_vector, _begin, high, pivot, highData);

    return high;
}

static void RecQuickSort(Vector *_vector, size_t _begin, size_t _end)
{
    size_t pivot;

    if (_begin < _end)
    {
        pivot = Partition(_vector, _begin, _end);

        if (pivot >= 1)
        {
            RecQuickSort(_vector, _begin, pivot - 1);
        }

        RecQuickSort(_vector, pivot + 1, _end);
    }
}

static void SwapData(Vector *_vector, size_t _x, size_t _y, int _xdata, int _ydata)
{
    VectorSet(_vector, _y, _xdata);
    VectorSet(_vector, _x, _ydata);
}

static size_t FindMin(Vector *_vector, size_t _from, size_t _to)
{
    size_t i = _from;
    size_t minIndex = _from;
    int currentData;
    int minData;
    
    VectorGet(_vector, _from, &minData);

    for(; i < _to; ++i)
    {
        VectorGet(_vector, i, &currentData);
        if(currentData < minData)
        {
            minIndex = i;
            VectorGet(_vector, i, &minData);
        }
    }

    return minIndex;
}

static int BubbleForward(Vector *_vector, int _begin, int _end)
{
    int needsSorting = 0;
    int data1, data2;
    int j;

    for (j = 0; _begin < _end ; ++_begin)
    {
        VectorGet(_vector, _begin, &data1);
        VectorGet(_vector, _begin + 1, &data2);

        if (data1 > data2)
        {
            SwapData(_vector, _begin, _begin + 1, data1, data2);
            needsSorting = 1;
        }
    }

    return needsSorting;
}

static int Bubblebackward(Vector *_vector, int _begin, int _end)
{
    int needsSorting = 0;
    int data1, data2;
    int j;

    for (; _end < _begin; --_end)
    {
        VectorGet(_vector, _end, &data1);
        VectorGet(_vector, _end - 1, &data2);

        if (data1 < data2)
        {
            SwapData(_vector, _end, _end - 1, data1, data2);
            needsSorting = 1;
        }
    }

    return needsSorting;
}

