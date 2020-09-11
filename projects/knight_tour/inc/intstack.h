#ifndef INTSTACK_H_XXX
#define INTSTACK_H_XXX

#include <stddef.h> /* size_t */

typedef struct intstack_t intstack_t;
/* Create a new intstack.

parameters:

returns pointer to newly created intstack.

 */
intstack_t *IntStackCreate(size_t num_of_elements);

/* Destroy stack.

parameters:
      st_int- pointer to intstack.

return value is void
if st is NULL no operation is performed */
void IntStackDestroy(intstack_t *st_int);

/* Push new element to intstack.

parameters:
      element - int data .
      st_int- pointer to stack.

return value is void.
if stack is full or st is NULL behaviour is undefined! */
void IntStackPush(intstack_t *st_int, int element);

/*  removes top element from stack.

parameters:
      st_int- pointer to stack.

return value is void.
if stack is empty or st is NULL behaviour is undefined */
void IntStackPop(intstack_t *st_int);

/*  returns top element from stack.intstack_t

parameters:
      st_int- pointer to stack.

return element in top of stack.
if stack is empty or st is NULL behaviour is undefined */

int IntStackPeek(intstack_t *st_int);

/*  returns number of elements in stack
parameters:
      st- pointer to stack.

return value is the number of elements in stack.
if st is NULL behaviour is undefined */
size_t IntStackSize(const intstack_t *st_int);


#endif /* INTSTACK_H_XXX*/
