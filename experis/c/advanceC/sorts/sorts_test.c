#include <stdio.h> /* printf */
#include "sorts.h"

#define TEST_SIZE (100)
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

static void PrintArray(float *_array, size_t _size);
static void PrintArrayVoid(void *_array[], size_t _size);
static void TestSortsBubbleSort();
int IsLessFloat(void *_x , void *_y);

int main(void)
{
    TestSortsBubbleSort();
    return 0;
}

static void TestSortsBubbleSort()
{
    int i;
    float arr[] = {2.4 ,5.66, 7.88, 1.23, 1.22, 1.67};
    size_t size = ARRAY_SIZE(arr);
    void* arrVoid[10];

    for (i = 0; i < size; i++)
    {
        arrVoid[i] = &arr[i];
    }

   /*  BubbleSort(arrVoid, size, IsLessFloat); */
    ShakeSort(arrVoid, size, IsLessFloat);
    PrintArrayVoid(arrVoid, size);


}


int IsLessFloat(void *_x , void *_y)
{
    return (*(float *)_x > *(float *)_y );
} 


static void PrintArray(float *_array, size_t _size)
{
    size_t i = 0;

    for (i = 0; i < _size; ++i)
    {
        printf("[%.2f] ", _array[i]);
    }

    printf("\n\n");
}

static void PrintArrayVoid(void *_array[], size_t _size)
{
    size_t i = 0;

    for (i = 0; i < _size; ++i)
    {
        printf("[%.2f] ", *(float*)_array[i]);
    }

    printf("\n\n");
}
