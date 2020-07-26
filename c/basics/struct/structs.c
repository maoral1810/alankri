#include <stdio.h> /* printf, scanf */
#include <stdlib.h> /* malloc , free , realloc */
#include <string.h> /* strcmp */
#include "structs.h"

struct Person 
{
    char name[30];
    int id ;
    int age;
    int education;
};

void SwapStructs(Person *arr, int index);

da_s *DynamicArrayCreate(int size, int block)
{
    da_s *da = (da_s *)malloc(sizeof(da_s));
    
    if(da == NULL)
    {
        return NULL;
    }

    da-> darray = (int *)malloc(sizeof(int) * size);

    if(da->darray == NULL)
    {
        free(da);
        da = NULL;
        
        return NULL;
    }

    da->darray_size = size;
    da->darray_block_size = block;
    da->num_of_elements = 0;
    da->magic_number = 0xBEDC0FFE;

    return da;
}

void DynamicArrayDestroy(da_s *to_destroy)
{
    if(to_destroy->magic_number == 0xBEDC0FFE && to_destroy != NULL)
    {
        to_destroy->magic_number = 0;
        free(to_destroy->darray);
        to_destroy->darray = NULL;
        free(to_destroy);    
    }
}

errors DynamicArrayInsert(da_s *da, int data)
{
    if(da == NULL)
    {
        return NOT_INITILIZE;
    }

    if(da->darray_size == da->num_of_elements)
        {
            int *save_arr = da->darray;
            
            /* check if have place in block and if can realloc him */
            if(da->darray_block_size <= 0)
            {
                return OVERFLOW;
            }

            da->darray = (int *)realloc(da->darray, 
                         (da->darray_block_size + da->darray_size) * sizeof(int));
            
            if(da->darray == NULL)
            {
                da->darray = save_arr;
                return REALLOC_FAILED; 
            }
            
            da->darray_size += da->darray_block_size;
            
        }
 
        da->darray[da->num_of_elements] = data; /*TODO check places */
        ++da->num_of_elements; /* increment NumOfElements By 1 */

        return OK;
}

errors DynamicArrayDelete(da_s *da, int *data)
{
    if(da == NULL || data == NULL)
    {
        return NOT_INITILIZE;
    }

    if(da->num_of_elements == 0)
    {
        return UNDERFLOW;
    }

    *data = da->darray[da->num_of_elements - 1];
    --da->num_of_elements;

    return OK; 
}

void SortByName(Person* Person_arr, int size)
{
    int i = 0;
    int not_sorted_size = 0;
    int not_sorted = 0;
    int needs_sorting = 0;
    
    for(; i < size - 1; ++i)
    {
        not_sorted_size = size - i - 1;
        
        for(not_sorted = 0; not_sorted < not_sorted_size ; ++not_sorted)
        {
            if(strcmp((Person_arr[not_sorted]).name, Person_arr[not_sorted + 1].name) > 0)
            {
                SwapStructs(Person_arr, not_sorted);
                needs_sorting = 1;
			}
    	}
		
        if (!needs_sorting)	/* if the arr is sorted */
		{
			return ;	
		}
    }
}

void SortById(Person* Person_arr, int size)
{
    int i = 0;
    int not_sorted_size = 0;
    int not_sorted = 0;
    int needs_sorting = 0;
    
    for(; i < size - 1; ++i)
    {
        not_sorted_size = size - i - 1;
        
        for(not_sorted = 0; not_sorted < not_sorted_size ; ++not_sorted)
        {
            if((Person_arr[not_sorted]).id > Person_arr[not_sorted + 1].id)
            {
                SwapStructs(Person_arr, not_sorted);
                needs_sorting = 1;
			}
    	}
		
        if (!needs_sorting)	/* if the arr is sorted */
		{
			return ;	
		}
    }
}
void SwapStructs(Person *arr, int index)
{
    Person save_Person = arr[index];
    arr[index] = arr[index + 1];
    arr[index + 1] = save_Person;
}

