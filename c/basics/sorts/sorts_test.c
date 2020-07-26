#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, rand, qsort */
#include <time.h>   /* clock */
#include "colors.h"
#include "vector.h"
#include "sorts.h"

#define TEST_SIZE (100)
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

typedef ADTErr(*sort_func_t)(Vector *);

/* test functions */
static double TestSortsBubbleSort(Vector *_vec);
static double TestSortsShakeSort(Vector *_vec);
static double TestSortsQuickSort(Vector *_vec);
static double TestSortsInsertionSort(Vector *_vec);
static double TestSortsShellSort(Vector *_vec);
static double TestSortsSelectionSort(Vector *_vec);
static double TestSortsMargeSort(Vector *_vec);
static double TestSortsCountingSort(Vector *_vec);
static double TestSortsItarativeQuickSort(Vector *_vec);
/* helpful functions */
static void PrintResualt(char *_testName, char *_scenario, double time);
static void PrintArray(int *array, size_t size);
static Vector *GetRandomVector(void);
static void CopyVector(Vector *_vec1, Vector *_vec2);
static int FindMin(Vector *_vector);
static int FindMax(Vector *_vector);
/* static void PrintDifference(double time1, double time2, char *str1, char *str2); */

int main(void)
{
    FILE *fd = NULL;
    char *fileName = "sortsRes";
    double BubbleTime;
    double ShakeTime;
    double quickTime;
    double InsertionTime;
    double ShellTime;
    double selctionTime;
    double MargeTime;
    double CountingTime;
    double ItarativeQuickSort;

    Vector *master = GetRandomVector();
    Vector *copyMaster = VectorCreate(TEST_SIZE,TEST_SIZE);
    
    CopyVector(master,copyMaster);
    BubbleTime = TestSortsBubbleSort(copyMaster);

    CopyVector(master,copyMaster);
    ShakeTime = TestSortsShakeSort(copyMaster); 
    
    CopyVector(master,copyMaster);
    quickTime = TestSortsQuickSort(copyMaster);
    
    CopyVector(master,copyMaster);
    InsertionTime = TestSortsInsertionSort(copyMaster);

    CopyVector(master,copyMaster);
    ShellTime = TestSortsShellSort(copyMaster);

    CopyVector(master,copyMaster);
    selctionTime = TestSortsSelectionSort(copyMaster); 

    CopyVector(master,copyMaster);
    MargeTime = TestSortsMargeSort(copyMaster);

    CopyVector(master,copyMaster);
    CountingTime = TestSortsCountingSort(copyMaster);

    CopyVector(master,copyMaster);
    ItarativeQuickSort = TestSortsItarativeQuickSort(copyMaster); 

    fd = fopen(fileName,"a");

    if(fd == NULL)
    {
        printf("failed in open a file\n");
        return 0;
    }

    fprintf(fd,"%s%d%s\n", "for ",TEST_SIZE," elements:");
    fprintf(fd,"%-25s\t%.3f\n","ShakeTime", ShakeTime);
    fprintf(fd,"%-25s\t%.3f\n","quickTime", quickTime);
    fprintf(fd,"%-25s\t%.3f\n","InsertionTime", InsertionTime);
    fprintf(fd,"%-25s\t%.3f\n","ShellTime", ShellTime);
    fprintf(fd,"%-25s\t%.3f\n","selctionTime", selctionTime);
    fprintf(fd,"%-25s\t%.3f\n","MargeTime", MargeTime);
    fprintf(fd,"%-25s\t%.3f\n","CountingTime", CountingTime);
    fprintf(fd,"%-25s\t%.3f\n","ItarativeQuickSort", ItarativeQuickSort);
    fputc('\n',fd);

    fclose(fd);

    return 0;
}

static double TestSortsBubbleSort(Vector *_vec)
{
    char *testName = "TestSorts";
    char *scenario = "BubbleSort";

    clock_t before = 0;
    clock_t after = 0;
    double time;


    before = clock();
    BubbleSort(_vec);
    after = clock();
    time = ((double)after - before) / CLOCKS_PER_SEC;

    PrintResualt(testName, scenario, time);

    return time;
}

static double TestSortsShakeSort(Vector *_vec)
{
    char *testName = "TestSorts";
    char *scenario = "ShakeSort";
    clock_t before = 0;
    clock_t after = 0;
    double time;

    before = clock();
    ShakeSort(_vec);
    after = clock();

    time = ((double)after - before) / CLOCKS_PER_SEC;
    PrintResualt(testName, scenario, time);

    return time;
}

static double TestSortsQuickSort(Vector *_vec)
{
    char *testName = "TestSorts";
    char *scenario = "QuickSort";

    size_t pivot = 0;
    clock_t before = 0;
    clock_t after = 0;
    double time;

    before = clock();
    QuickSort(_vec);
    after = clock();

    time = ((double)after - before) / CLOCKS_PER_SEC;

    PrintResualt(testName, scenario, time);

    return time;
}

static double TestSortsInsertionSort(Vector *_vec)
{
    char *testName = "TestSorts";
    char *scenario = "InsertionSort";

    size_t pivot = 0;
    clock_t before = 0;
    clock_t after = 0;
    double time;

    before = clock();
    InsertionSort(_vec, 1);
    after = clock();
    time = ((double)after - before) / CLOCKS_PER_SEC;
  
    PrintResualt(testName, scenario, time);

    return time;
}

static double TestSortsShellSort(Vector *_vec)
{
    char *testName = "TestSorts";
    char *scenario = "ShellSort";

    size_t pivot = 0;
    clock_t before = 0;
    clock_t after = 0;
    double time;

    before = clock();
    ShellSort(_vec);
    after = clock();
    time = ((double)after - before) / CLOCKS_PER_SEC;

    PrintResualt(testName, scenario, time);

    return time;
}

static double TestSortsSelectionSort(Vector *_vec)
{
    char *testName = "TestSorts";
    char *scenario = "SelectionSort";

    size_t pivot = 0;
    clock_t before = 0;
    clock_t after = 0;
    double time;

    before = clock();
    SelectionSort(_vec);
    after = clock();
    time = ((double)after - before) / CLOCKS_PER_SEC;
    PrintResualt(testName, scenario, time);

    return time;
}

static double TestSortsMargeSort(Vector *_vec)
{
    char *testName = "TestSorts";
    char *scenario = "MargeSort";

    size_t pivot = 0;
    clock_t before = 0;
    clock_t after = 0;
    double time;

    before = clock();
    MargeSort(_vec);
    after = clock();
    time = ((double)after - before) / CLOCKS_PER_SEC;
    PrintResualt(testName, scenario, time);

    return time;
}

static double TestSortsCountingSort(Vector *_vec)
{
    char *testName = "TestSorts";
    char *scenario = "CountingSort";
    int max,min;
    size_t pivot = 0;
    clock_t before = 0;
    clock_t after = 0;
    double time;

    max = FindMax(_vec);
    min = FindMin(_vec);
    before = clock();
    CountingSort(_vec, max, min);
    after = clock();
    time = ((double)after - before) / CLOCKS_PER_SEC;
    PrintResualt(testName, scenario, time);

    return time;
}

static double TestSortsItarativeQuickSort(Vector *_vec)
{
    char *testName = "TestSorts";
    char *scenario = "ItarativeQuickSort";
    int max,min;
    size_t pivot = 0;
    clock_t before = 0;
    clock_t after = 0;
    double time;

    before = clock();
    ItarativeQuickSort(_vec);
    after = clock();

    time = ((double)after - before) / CLOCKS_PER_SEC;
    PrintResualt(testName, scenario, time);

    return time;
}


/*---------------------------------------------------------------------------*/
/* Helpful functions: */

static Vector *GetRandomVector(void)
{
    size_t i = 0;
    int data;
    Vector *vector = VectorCreate(TEST_SIZE,TEST_SIZE);
    if (NULL == vector)
    {
        printf("failed because malloc failed!\n");
        return NULL;
    }

    srand(time(NULL));

    for (i = 0; i < TEST_SIZE; ++i)
    {
        data = rand()% 1000;
        VectorAdd(vector, data);
    }

    return vector;
}

static void CopyVector(Vector *_vec1, Vector *_vec2)
{
    size_t i = 0;
    int data;
    size_t vecSize;

    VectorItemsNum(_vec1, &vecSize);

    if(_vec1 != NULL && _vec2 != NULL)
    {
        for( ;i < vecSize ; ++i)
        {
            VectorGet(_vec1, i, &data);
            VectorAdd(_vec2, data);
        }
    }
}
/* may be useful: */

static void PrintArray(int *array, size_t size)
{
    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        printf("[%d] ", array[i]);
    }

    printf("\n\n");
}

static void PrintResualt(char *_testName, char *_scenario, double time)
{
    printf(BOLDCYAN "\n%s" BOLDYELLOW ":%s: " BOLDGREEN "Finish in"BOLDRED" %.3f \n" RESET, 
           _testName, _scenario, time);
}

/* static void PrintDifference(double time1, double time2, char *str1, char *str2)
{
    printf("\nDifference between %s to %s = %.3f % \n", 
    str1, str2, (time1 - time2) / time1 * 100);
} */

static int FindMin(Vector *_vector)
{
    size_t i, vectorSize;
    int currentData;
    int minData;

    VectorItemsNum(_vector, &vectorSize);
    VectorGet(_vector, 0, &minData);

    for(i = 1; i < vectorSize; ++i)
    {
        VectorGet(_vector, i, &currentData);
        if(currentData < minData)
        {
            minData = currentData;
        }
    }

    return minData;
}

static int FindMax(Vector *_vector)
{
    size_t i, vectorSize;
    int currentData;
    int maxData;

    VectorItemsNum(_vector, &vectorSize);
    VectorGet(_vector, 0, &maxData);

    for(i = 1; i < vectorSize; ++i)
    {
        VectorGet(_vector, i, &currentData);
        if(currentData > maxData)
        {
            maxData = currentData;
        }
    }

    return maxData;
}