/* 
arrays_h_ file 
programar: Maor Alankri
version: 1
last update: 1.11.19
*/
#define OK 0
#define INPUT_ERROR 1
#define SIZE_ERROR 2


int CalcAvg(int *arr, unsigned int size, double *avg);
/*
the function calculate the average of array 

input:
arr - array
arr_len - length of array

output:
the average of all the index in the array

error:
if the array is empty return 0

*/
int FindMostReturnNumber(int *arr, unsigned int size, int *res);

/*
the function get an array and return the number that return the most 

input:
arr - array
arr_len - length of array

output#define OK 0
the mo#define MEMORY_ERROR 1

error:#define SIZE_ERROR 2

*/

int OrderArray(int *arr, unsigned int size, int *res);

/* 
the function get an array and return array sorted from even to odd numbers 

input:
arr - array
arr_len - length of array

output:

error:
*/
void BubbleSort(int *arr, size_t size);
void BubbleSortWithMacro(int *arr, size_t size);

