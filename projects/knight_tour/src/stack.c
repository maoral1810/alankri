#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */
#include <stddef.h> /* size_t */
#include <string.h> /* memcpy */
#include <assert.h> /* assert */
#include "stack.h"

struct stack_t /* Create a new stack */
{
  void *head;
  size_t element_size;
  char data [1];
};

stack_t *StackCreate(size_t element_size, size_t num_of_elements)
{

    stack_t *new_stack = (stack_t *)malloc(sizeof(stack_t) +
    (element_size * num_of_elements));

    if (!new_stack)
    {
        printf("allocated failed\n");
    }

    new_stack->head = new_stack->data;
    new_stack->element_size = element_size;

    return new_stack;
}

void StackDestroy(stack_t *st)
{
    assert(st);

    free(st);
    st = NULL;
}

void StackPush(stack_t *st, const void *element)
{
    char *new_location = (char *)(st->head) ;

    assert(st);
    assert(element);

    memcpy(st->head,element,st->element_size) ;
    new_location += st->element_size;
    st->head = (void *)new_location;
}

void StackPop(stack_t *st)
{
    char *new_location = (char *)(st->head);

    assert(st);

    new_location -= st->element_size;
    st->head = (void *)new_location;
}

void *StackPeek(stack_t *st)
{
    assert(st);

    return ((char *)st->head - st->element_size);
}

size_t StackSize(const stack_t *st)
{
    assert(st);

    return ((size_t)((char *)st->head - (char *)st->data) / st->element_size);
}
