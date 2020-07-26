#ifndef _STRUCTS_H
#define _STRUCTS_H

typedef enum {OK, NOT_INITILIZE, REALLOC_FAILED,
              OVERFLOW, UNDERFLOW} errors;
/* typedef struct da_s da_s; */
typedef struct Person Person;
typedef struct da_s 
{
    int *darray;
    int darray_size;
    int darray_block_size;
    int num_of_elements;
    unsigned int magic_number;
}da_s;


da_s *DynamicArrayCreate(int size, int block);
/*  
the function alloc struct and return a pointer for the struct

input:
size - numbers of elements 
block - block realloc factor

output:
pointer to the struct

error:
return NULL if alocation failed 

*/
void DynamicArrayDestroy(da_s *to_destroy);
/*  
the function free DynamicArrayStruct

input:
DynamicArraystruct - da_s struct  

output:
 

error:

*/
errors DynamicArrayInsert(da_s *da, int data);
/* 
the function insert data to darray in the struct
alloc new array if needed

input:
    da - pointer to struct  
    data - data to insert

output:

error: return status

OK - on sucsses
NOT_INITILIZE  - if one of the input pointers = NULL
REALLOC_FAILED -  if realloc return NULL
OVERFLOW - if size <= 0 and the array is full 
  
*/

errors DynamicArrayDelete(da_s *da, int *data);

/* 
the function delete data from darray in the struct

input:
    da - pointer to struct  
    data - pointer to return data

output:

error: return status

OK - on sucsses
NOT_INITILIZE - if the sruct == NULL 
UNDERFLOW - if the array is empty 
  
*/
void SortByName(per_s* persons, int size);
/* 

*/
void SortById(per_s* person_arr, int size);

#endif /*_STRUCTS_H*/