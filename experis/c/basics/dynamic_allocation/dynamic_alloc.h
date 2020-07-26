#define OK 0
#define NOT_INITILIZE -1
#define REALLOC_FAILED -2
#define OVERFLOW -3
#define INVALIV_INPUT -4
#define UNDERFLOW -5
#define N 10

void TryMalloc(void);

/*
the function alloc array , insert all index in array , free the array 

input:

output:

error:

*/  

int *DynamicArrayCreate(int size);
/* 
the function alloc dynamic memory and return a pointer for the first address

input:
size - numbers of elements 

output:
pointer to the allocation 

error:
return INPUT_ERROR if alocation failed or OK on sucsses

*/

void DynamicArrayDestroy(int *DynamicArrayPtr);
/*
 
the function free DynamicArrayPtr

input:
DynamicArrayPtr - int pointer 

output:
 

error:

*/

int DynamicArrayInsert(int **DynamicArrayPtr, int data, int *DaSize, 
                       int * DaNumOfElements, int IncBlockSize);
/*

the function insert data to *DynamicArrayPtr
alloc new *DynamicArrayPtr if needed

input:
    DynamicArrayPtr - pointer to array 
    data - data to insert
    DaSize - pointer to size of array
    DaNumOfElements - pointer to number of elements
    IncBlockSize - realloc increment factor 

output:

error: return status

OK - on sucsses
INVALIV_INPUT - if one of the input pointers = NULL
NOT_INITILIZE 
REALLOC_FAILED -  if realloc return NULL
OVERFLOW - if size <= 0
  
*/
int DynamicArrayDelete(int *DynamicArrayPtr, int *data, int *DaNumOfElements);
/* 

 */