#include <stdio.h> /* printf*/
#include <time.h>   /* clock */
#include <stdlib.h> /* malloc , free */
#include <string.h> /* memcpy, memcmp */
#include "arrays.h"

#define RESET       "\033[0m"
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green    */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red      */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue     */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow   */

#define ARR_LENGTH(x)(sizeof(x) / sizeof(x[0]))
#define TEST_SIZE (50000)

static void PrintArray(int *arr, int len);
static int CompareArrays(int* arr1, int *arr2, int len1);
static void PrintStatus(int status);
static int *GetRandomArray(void);
static int CmpFunc(const void *a, const void *b);

static void TestArrays(void);
static int TestBubbleSort();

int main(void)
{
/*     TestArrays(); */
    TestBubbleSort();

    return 0;
}
static void TestArrays(void)
{
     int arr[] = {95,96,100,92.5,84,85,76};
    int arr1[] = {1,2,3,4};
    int arr2[] = {1,2,3,1,5,6,1,7,8,9,0,-4,-89};
    int unsorted_arr[] = {3,56,-7,0,12};

    int exp_arr1[] = {2,4,1,3};
    int exp_arr2[] = {2,6,8,0,-4,1,3,1,5,1,7,9,-89};
    int exp_sorted[] = {-7,0,3,12,56}; 
    
    int exp_res_2 = 1;
    int res = 0;
    double avg = 0;    
    int err = 0;
    int status = 0;
    
    status = CalcAvg(arr, ARR_LENGTH(arr), &avg);
    
    if(!status)
    {
        printf(BOLDGREEN"the average of the arr is %.5f \n"RESET,avg);
    }
    else
    {
        PrintStatus(status);
    }

    status = FindMostReturnNumber(arr1, ARR_LENGTH(arr1), &res);
    
    if(!status)
    {
        if (exp_res_2 != res)
        {
            printf(BOLDRED"FindMostReturnNumber failed \n"RESET);
            printf("function resualt is %d expected resualt is %d",
                res,exp_res_2);
            ++err;
        }
    }
    else
    {
        PrintStatus(status);
    }

    status = OrderArray(arr1,ARR_LENGTH(arr1), &res);

    if(!status)
    {
        if(CompareArrays(arr1,exp_arr1, ARR_LENGTH(arr1)))
        {
            printf(BOLDRED"OrderArray failed with array:\n"RESET);
            PrintArray(arr1,ARR_LENGTH(arr1));
            ++err;
        }
    }
    else
    {
        PrintStatus(status);
    }

    status = OrderArray(arr2,ARR_LENGTH(arr2), &res);
    
    if(!status)
    {
        if(CompareArrays(arr2,exp_arr2, ARR_LENGTH(arr2)))
        {
            printf(BOLDRED"OrderArray failed with array:\n"RESET);
            PrintArray(arr2,ARR_LENGTH(arr2));
            ++err;
        }
    }
    else
    {
        PrintStatus(status);
    }
    
    BubbleSort(unsorted_arr, ARR_LENGTH(unsorted_arr));
    
    if(CompareArrays(unsorted_arr, exp_sorted, ARR_LENGTH(exp_sorted)))
    {
        printf(BOLDRED"BubbleSort failed with array:\n"RESET);
        PrintArray(unsorted_arr, ARR_LENGTH(unsorted_arr));
        ++err;
    }

    if(!err)
    {
        printf(BOLDYELLOW"Test sucsses!!! :)\n"RESET); 
    }
}

static int TestBubbleSort()
{
    int *array1 = GetRandomArray();
    int array2[TEST_SIZE] = {0};
    clock_t before = 0;
    clock_t after = 0;
    char *name = "BubbleSort";

    printf("test %s:\n", name);

    memcpy(array2, array1, TEST_SIZE * sizeof(int));

    before = clock();
    BubbleSortWithMacro(array1, TEST_SIZE);
    after = clock();
    printf("%s BublesortWithMacro finished in %ld secondes\n", name, (after - before) / CLOCKS_PER_SEC);

    before = clock();
    BubbleSort(array2, TEST_SIZE);
    after = clock();
    printf("%s Bublesort finished in %ld secondes\n", name, (after - before) / CLOCKS_PER_SEC);
    printf("\n************************************************************\n\n");

/*     if (0 != memcmp(array1, array2, TEST_SIZE * sizeof(int)))
    {
        printf("%s test failed!\n", name);
        free(array1);
        return 1;
    } */

    free(array1);
    return 0;
}

/* ================= Helpful Functions ================== */

static int CompareArrays(int* arr1, int *arr2, int len)
{
    int i = 0;

    for(i = 0; i < len; ++i)
    {
        if (arr1[i] != arr2[i])
        {
            return 1;
        }
    }

    return 0;
}


static void PrintArray(int *arr, int len)
{
    int i = 0;

    for (i = 0; i < len; ++i)
    {
        printf("%d," ,arr[i]);
    }

    putchar('\n');
}

static void PrintStatus(int status)
{
    
    if(INPUT_ERROR == status)
    {
        printf("failed with memory error");
    }

    if(SIZE_ERROR == status)
    {
        printf("failed with size error");
    }
}

static int *GetRandomArray(void)
{
    size_t i = 0;
    int *array = (int *)malloc(TEST_SIZE * sizeof(int));
    if (NULL == array)
    {
        printf("failed because malloc failed!\n");
        return NULL;
    }

    srand(time(NULL));

    for (i = 0; i < TEST_SIZE; ++i)
    {
        array[i] = rand()% 1000;
    }

    return array;
}

static int CmpFunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}