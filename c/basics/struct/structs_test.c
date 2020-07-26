#include <stdio.h> 
#include "structs.h"

#define ARR_LENGTH(x)(sizeof(x) / sizeof(x[0]))

#define RESET       "\033[0m"
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red      */
#define BOLDGREEN   "\033[5m\033[32m"      /* Bold Green    */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow   */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue     */

static int TestCreatAndDestroy(void);
static int TestInsert(void);
static int TestDelte(void);
static int TestSortByName(void);

static void PrintArrayPerson(Person *s1, int size);
/* static void PrintArray(int *arr, int len); */

int main(void)
{
    int err = 0;
    
    err += TestCreatAndDestroy();
    err += TestInsert(); 
    err += TestDelte();
    err += TestSortByName();

    if (err)
    {
        printf(BOLDRED"Test Faild with %d errors\n"RESET,err); 
    }
    else
    {
        printf(BOLDGREEN "Test Sucsses\n "RESET"("BOLDBLUE"*"BOLDRED"_"BOLDBLUE"*"RESET")\n",err); 
    }
    
    return 0;   
}

static int TestCreatAndDestroy(void)
{
    da_s *da = NULL;
    int size = 5;
    int fail_size = -7;
    int err = 0;
    int block_size = 2;

    da = DynamicArrayCreate(size, block_size);
    
    if(da == NULL)
    {
        ++err;
    }

    DynamicArrayDestroy(da);
    da = NULL;

    da = DynamicArrayCreate(fail_size, block_size);
    if(da != NULL)
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
    da_s *da = NULL;
    int size = 5;
    int i = 0;
    
    int err = 0;
    int to_insert[] ={0,1,2,3,4,5,6,7,8,9};
    int status = OK;
    int block_size = 0;

    da = DynamicArrayCreate(size, block_size);

    if(da == NULL)
    {
        ++err;
    }

    for (i = 0; i < size && status == OK; ++i) /* fill full array */
    {
        status = DynamicArrayInsert(da, to_insert[i]);
    }

    if(OVERFLOW != DynamicArrayInsert(da, to_insert[i])) /* overflow */
    {
        ++err;
         printf(BOLDRED"TestInsert Faild with overflow\n"RESET);    
    }

    da->darray_block_size = 2;

    DynamicArrayInsert(da, to_insert[i]); /* need to realloc by 2 elements */

    if (da->darray_size != 7 && da->num_of_elements != 6) 
    {
        ++err;
        printf(BOLDRED"TestInsert Faild with realloc\n"RESET);    
    }

    da->darray_size = 0;
    da->darray_block_size = 0;

    if(NOT_INITILIZE != DynamicArrayInsert(NULL, to_insert[i+1]))
    {
        ++err;
        printf(BOLDRED"TestInsert Faild with NOT_INITILIZE\n"RESET);  
    }

    if(err)
    {
        printf(BOLDRED"TestInsert Faild with %d errors\n"RESET,err); 
    }
    
    DynamicArrayDestroy(da);
    da = NULL;

    return err;
}

static int TestDelte(void)
{
    da_s *da = NULL;
    int size = 5;
    int i = 0;
    int err = 0;
    int to_insert[] ={0,1,2,3,4,5,6,7,8,9};
    int status = OK;
    int block_size = 0;
    int data = 0;

    da = DynamicArrayCreate(size, block_size);

    if(da == NULL)
    {
        ++err;
    }

    if(UNDERFLOW != DynamicArrayDelete(da, &data))
    {
        ++err;
        printf(BOLDRED"TestDelte Faild with UNDERFLOW\n"RESET);  
    }

    for (i = 0; i < size && status == OK; ++i)
    {
        status = DynamicArrayInsert(da, to_insert[i]);
    }

    status = DynamicArrayDelete(da, &data);

    if(data != to_insert[i - 1])
    {
        ++err;
        printf(BOLDRED"TestDelte Faild with Delete after insert\n"RESET);  
    }
    
    /* insert new num to same place in array*/
    DynamicArrayInsert(da, to_insert[i]); 

    status = DynamicArrayDelete(da, &data);

    if(data != to_insert[i] && status == OK)
    {
        ++err;
        printf(BOLDRED"TestDelte Faild with Delete after insert2\n"RESET);  
    }

    if(err)
    {
        printf(BOLDRED"TestDelte Faild with %d errors\n"RESET,err); 
    }
    
    DynamicArrayDestroy(da);
    da = NULL;
    
    return err;
}

int TestSortByName(void)
{
    Person arr[4] = {{"maor",222111333, 30, 5}, {"soso",333111220, 35, 3},
                    {"dudu",666666666, 12, 1}, {"ori",999111333, 59, 2}};
    int size = 4;
    
    printf("--------- struct before changes--------------\n");
    PrintArrayPerson(arr, size);
    
    printf("--------- struct after SortByName--------------\n");
    SortByName(arr, size);
    PrintArrayPerson(arr, size);

    printf("--------- struct after SortById--------------\n");
    SortById(arr, size);
    PrintArrayPerson(arr, size);

    return 0;
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
} */


static void PrintArrayPerson(Person *s1, int size)
{   
    int i = 0;

    for( i = 0; i < size; ++i)
    {
        printf("struct[%d]:\nname: %s\t id: %d\t age: %d\t education: %d\t\n\n" ,
        i,s1[i].name , s1[i].id, s1[i].age, s1[i].education);
    }
}





