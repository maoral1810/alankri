#include <stdlib.h> /* malloc */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

#include "stack.h"
#include "intstack.h"


struct intstack_t /* Create a new stack */
{
    stack_t *st;
};

intstack_t *IntStackCreate(size_t num_of_elements)
{
    intstack_t *new_stack = (intstack_t *)malloc(sizeof(intstack_t));

    if (!new_stack)
    {
        return NULL;
    }

    new_stack->st = StackCreate(sizeof(int) ,num_of_elements);

    return new_stack;
}

void IntStackDestroy(intstack_t *st_int)
{
    assert(st_int);

    StackDestroy(st_int->st);
    free (st_int);
    st_int = NULL;
}

void IntStackPush(intstack_t *st_int, int element)
{
    StackPush(st_int->st ,&element);
}

void IntStackPop(intstack_t *st_int)
{
    StackPop(st_int->st);
}

int IntStackPeek(intstack_t *st_int)
{
    return *(int *)(StackPeek(st_int->st));
}

size_t IntStackSize(const intstack_t *st_int)
{
    return StackSize(st_int->st);
}

