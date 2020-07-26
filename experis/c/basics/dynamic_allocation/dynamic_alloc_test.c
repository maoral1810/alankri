#include <stdio.h> 
#include "dynamic_alloc.h"

#define ARR_LENGTH(x)(sizeof(x) / sizeof(x[0]))

#define RESET       "\033[0m"
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green    */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red      */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue     */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow   */

static int TestCreatAndDestroy(void);
static int TestInsert(void);
static int TestDelte(void);

/* static void PrintArray(int *arr, int len); */

int main(void)
{
    int err = 0;
    
    err += TestCreatAndDestroy();
    err += TestInsert(); 
    err += TestDelte();

    if (err)
    {
        printf(BOLDRED"Test Faild with %d errors\n"RESET,err); 
    }
    else
    {
        printf(BOLDGREEN"Test Sucsses :)\n"RESET,err); 
    }
    
    return 0;   
}

static int TestCreatAndDestroy(void)
{
    int *arr = NULL;
    int size = 5;
    int fail_size = -7;
    int err = 0;

    arr = DynamicArrayCreate(size);

    if(arr == NULL)
    {
        ++err;
    }

    DynamicArrayDestroy(arr);
    arr = NULL;

    arr = DynamicArrayCreate(fail_size);
    if(arr != NULL)
    {
        ++err;
    }

    if(err)
    {
        printf(BOLDRED"TestCreatAndDestroy Faild with %d errors\n"RESET,err); 
    }
    
    return err;
}

static int TestInsert(void)
{
    int *arr = NULL;
    int size = 5;
    int i = 0;
    int inc = 2;
    int err = 0;
    int to_insert[] ={0,1,2,3,4,5,6,7,8,9};
    int num_of_elements = 0;
    int status = OK;
    int invalid_size = 0;

    arr = DynamicArrayCreate(size);

    if(arr == NULL)
    {
        ++err;
    }

    for (i = 0; i < size && status == OK; ++i) /* fill full array */
    {
        status = DynamicArrayInsert(&arr, to_insert[i], &size, &num_of_elements, 0);
    }
    
    /* overflow */
    if(OVERFLOW != DynamicArrayInsert(&arr, to_insert[i], &size, &num_of_elements, 0)) 
    {
        ++err;
         printf(BOLDRED"TestInsert Faild with overflow"RESET);    
    }
    
    /* need to realloc by 2 elements */
    DynamicArrayInsert(&arr, to_insert[i], &size, &num_of_elements, 2); 

    if (size != 7 && num_of_elements != 6) 
    {
        ++err;
        printf(BOLDRED"TestInsert Faild with realloc"RESET);    
    }

    if(NOT_INITILIZE != DynamicArrayInsert(&arr, to_insert[i+1], &invalid_size, &num_of_elements, 0))
    {
        ++err;
        printf(BOLDRED"TestInsert Faild with invalid_size"RESET);  
    }

    if(NOT_INITILIZE != DynamicArrayInsert(NULL, to_insert[i+1], NULL, NULL, 0))
    {
        ++err;
        printf(BOLDRED"TestInsert Faild with NOT_INITILIZE"RESET);  
    }
    /* PrintArray(arr,size); */

    if(err)
    {
        printf(BOLDRED"TestInsert Faild with %d errors\n"RESET,err); 
    }
    
    DynamicArrayDestroy(arr);
    arr = NULL;

    return err;
   /*  if (DynamicArrayInsert) */
}

static int TestDelte(void)
{
    int *arr = NULL;
    int size = 5;
   
    int i = 0;
    int data = 0;
    int err = 0;
    int to_insert[] ={0,1,2,3,4,5,6};
    int num_of_elements = 0;
    int status = OK;

    arr = DynamicArrayCreate(size);

    if(arr == NULL)
    {
        ++err;
    }

    if(UNDERFLOW != DynamicArrayDelete(arr, &data, &num_of_elements))
    {
        ++err;
        printf(BOLDRED"TestDelte Faild with UNDERFLOW"RESET);  
    }

    for (i = 0; i < size && status == OK; ++i)
    {
        status = DynamicArrayInsert(&arr, to_insert[i], &size, &num_of_elements, 0);
    }

    DynamicArrayDelete(arr, &data, &num_of_elements);

    if(data != arr[i])
    {
        ++err;
        printf(BOLDRED"TestDelte Faild with Delete after insert"RESET);  
    }

    if(err)
    {
        printf(BOLDRED"TestDelte Faild with %d errors\n"RESET,err); 
    }
    
    DynamicArrayDestroy(arr);
    arr = NULL;
    
    return err;
}

/*=================================== helpful functions =============================== */
/* static void PrintArray(int *arr, int len)
{
    int i = 0;

    for (i = 0; i < len; ++i)
    {
        printf("%d," ,arr[i]);
    }

    putchar('\n');
}
 */

