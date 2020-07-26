#include <stddef.h> /* size_t */
#include <stdio.h>  /* printf */

#define TRUE 1
#define FALSE 0

typedef int (*SortingMethod)(int data1, int data2);

void BubbleSort(int *arr, size_t size, SortingMethod _sortCriteria);

static int SortByBigger(int _a, int _b);
static int SortBySmaller(int _a, int _b);
static int SortByEven(int _a, int _b);
static int SortByOdd(int _a, int _b);
static void PrintArray(int *arr, int len);

static void Swap(int *a, int *b);

int main(void)
{
    int arr[] = {1, 8, 2, 66, 5, 4, 9, 11};

    size_t size = sizeof(arr) / sizeof(arr[0]);

    printf("array before sort:\n");
    PrintArray(arr, size);
    putchar('\n');

    BubbleSort(arr, size, SortByBigger);
    printf("sort by bigger:\n");
    PrintArray(arr, size);
    putchar('\n');

    BubbleSort(arr, size, SortBySmaller);
    printf("sort by smaller:\n");
    PrintArray(arr, size);
    putchar('\n');

    BubbleSort(arr, size, SortByEven);
    printf("sort by even:\n");
    PrintArray(arr, size);
    putchar('\n');

    BubbleSort(arr, size, SortByOdd);
    printf("sort by odd:\n");
    PrintArray(arr, size);
    putchar('\n');
}

void BubbleSort(int *_arr, size_t _size, SortingMethod _sortCriteria)
{
    register size_t each_element = 0;
    register size_t not_sorted = 0;
    
    if(_arr == NULL)
    {
        return;
    }

    for (each_element = 0; each_element < _size; ++each_element)
    {
        int needs_sorting = 0;
        size_t not_sorted_size = _size - each_element - 1;

        for (not_sorted = 0; not_sorted < not_sorted_size; ++not_sorted)
        {
            if (_sortCriteria(_arr[not_sorted], _arr[not_sorted + 1]) == TRUE)
            {
                Swap(&(_arr[not_sorted]), &_arr[not_sorted + 1]);
                needs_sorting = 1;
            }
        }
        if (!needs_sorting)
        {
            return;
        }
    }
}

/******************** static functions **************************/
static void Swap(int *a, int *b)
{
    int save_data = *a;
    *a = *b;
    *b = save_data;
}

static void PrintArray(int *arr, int len)
{
    int i = 0;

    for (i = 0; i < len; ++i)
    {
        printf("%d,", arr[i]);
    }

    putchar('\n');
}
/*----------------------- sort functions ----------------------------*/
static int SortByBigger(int _a, int _b)
{
    return (_a < _b);
}

static int SortBySmaller(int _a, int _b)
{
    return (_a > _b);
}

static int SortByEven(int _a, int _b)
{
    if (_a % 2 == 1 && _b % 2 == 0)
    {
        return TRUE;
    }

    return FALSE;
}

static int SortByOdd(int _a, int _b)
{
    if (_a % 2 == 0 && _b % 2 == 1)
    {
        return TRUE;
    }

    return FALSE;
}
