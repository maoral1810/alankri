#include <stddef.h>  /* size_t */
#include <stdio.h>   /* printf */
#include <time.h>    /* clock */
#include <pthread.h> /* pthread_create */
#include <math.h>   /* sqrt */

static int IsPrime(int n);
static void FindPrime(int *a_resArray, size_t a_numToFind);
static void* FindPrime2(void* argument);
static void PrintLess10PrimeNumbers(int *a_resArray, size_t a_numToFind);

static void TestWithoutThreads();
static void TestWithThread();

#define ARR_LEN 1000
#define NUM_OF_THREADS 2
#define FALSE 0
#define TRUE !FALSE

typedef struct Arr_s{
    int *arr;
    size_t arrLen;
}Arr_s;


int main(void)
{
    TestWithoutThreads();
    TestWithThread();

    return 0;
}

static void TestWithoutThreads()
{
    int arr[ARR_LEN];
    int arr2[ARR_LEN];
    clock_t before = 0;
    clock_t after = 0;
    double time;

    printf("\n---------------- without Threads ------------------\n");
    
    before = clock();
    FindPrime(arr, ARR_LEN);
    FindPrime(arr2, ARR_LEN);
    after = clock();
    
    time = ((double)after - before) / CLOCKS_PER_SEC;
    printf("first time: FindPrime finish after %.2f sec\n", time);
    PrintLess10PrimeNumbers(arr, ARR_LEN);
    PrintLess10PrimeNumbers(arr2, ARR_LEN);
}

static void TestWithThread()
{
    int arr[ARR_LEN];
    int arr2[ARR_LEN];
    clock_t before = 0;
    clock_t after = 0;
    double time;
    pthread_t thread_id[NUM_OF_THREADS];
    Arr_s arg;
    Arr_s arg2;

    arg.arr = arr;
    arg.arrLen = ARR_LEN;

    arg2.arr = arr2;
    arg2.arrLen = ARR_LEN;

    printf("\n---------------- with Threads ------------------\n");

    before = clock();
    if (0 != pthread_create(&thread_id[0], NULL ,&FindPrime2, &arg)) 
    {
        perror("failde to create a thread\n");
    }
    
    if (0 != pthread_create(&thread_id[1], NULL ,&FindPrime2, &arg2)) 
    {
        perror("failde to create a thread\n");
    }
    
    pthread_join(thread_id[0], NULL);
    pthread_join(thread_id[1], NULL);

    printf("FindPrime finish after %.2f sec\n", time);

    PrintLess10PrimeNumbers(arr, ARR_LEN);
    PrintLess10PrimeNumbers(arr2, ARR_LEN);
}

static void* FindPrime2(void* argument)
{
    size_t j = 0;
    size_t i = 0;
    Arr_s arg = *(Arr_s *)argument;

    while(j < arg.arrLen)
    {
        if(IsPrime(i))
        {
            arg.arr[j] = i;
            ++j;
        }

        ++i;
    }

    return argument;
}

static void FindPrime(int *a_resArray, size_t a_numToFind)
{
    size_t j = 0;
    size_t i = 0;

    while(j < a_numToFind)
    {
        if(IsPrime(i))
        {
            a_resArray[j] = i;
            ++j;
        }

        ++i;
    }
}

static void PrintLess10PrimeNumbers(int *a_resArray, size_t a_numToFind)
{
    size_t i =  a_numToFind - 10;

    for(; i < a_numToFind ;++i)
    {
        printf("%d, ",a_resArray[i]); 
    }

    putchar('\n');
}

static int IsPrime(int a_number) {
    size_t i;
    if(a_number == 2) {
        return TRUE;
    }
    if(a_number % 2 == 0) {
        return FALSE;
    }
    for(i = 3; i <= sqrt(a_number); i += 2) {
        if(a_number % i == 0) {
            return FALSE;
        }
    }
    return TRUE;
}
