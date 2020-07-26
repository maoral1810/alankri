#include <stddef.h> /* size_t   */ 
#include <stdio.h>  /* printf   */
#include <time.h>   /* clock_t  */
#include <stdlib.h> /* malloc */

#define TEST_SIZE (100000000)
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

static int *GetRandomArray(void);
int LinearSearch(int *_arr, int _size, int _data);
int TopLinearSearch(int *_arr, int _size, int _data);

int main(void)
{
    int *arr = GetRandomArray();
    int *toSearch = GetRandomArray();
    clock_t before;
    clock_t after;
    clock_t before2;
    clock_t after2;
    size_t i = 0;
    int res;
    double time1;
    double time2;

    before = clock();
    for(i = 0; i < TEST_SIZE; ++i)
    {
        res = LinearSearch(arr, ARRAY_SIZE(arr), toSearch[i]);
    }
    after = clock();
    printf("before1 = %.2ld\n",before);
    printf("after1 = %.2ld\n",after);
    time1 = ((double)after - before) / CLOCKS_PER_SEC;

    before2 = clock();
    for(i = 0; i < TEST_SIZE; ++i)
    {
        res = TopLinearSearch(arr, ARRAY_SIZE(arr), toSearch[i]);
    }
    after2 = clock();
    printf("before2 = %.2ld\n",before2);
    printf("after2 = %.2ld\n",after2);
    time2 = ((double)after2 - before2) / CLOCKS_PER_SEC;

    printf("time1 = %.3f\t time2 = %.3f\n", time1, time2);
    printf( "the diffrance in time is %.3f % \n" ,((time1 - time2) / time1 )* 100);

    free(arr);
    free(toSearch);

    return 0;
}


int LinearSearch(int *_arr, int _size, int _data)
{
    size_t i = 0;

    for(i = 0; i < _size; ++i)
    {
        if(_arr[i] == _data)
        {
            return 1;
        }
    }

    return 0;
}

int TopLinearSearch(int *_arr, int _size, int _data)
{
    size_t i = 0;

    int savedata = _arr[_size -1];
    _arr[_size -1] = _data;

    while(_arr[i] != _data)
    {
        ++i;
    }

    _arr[_size - 1] = savedata;

    if(i == (_size - 1))
    {
        return 0;
    }

    return 1;
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
        array[i] = rand()% 1000000;
    }

    return array;
}