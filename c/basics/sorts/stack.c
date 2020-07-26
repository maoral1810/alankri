#include <stddef.h> /* size_t       */
#include <stdlib.h> /* malloc, free */

#include "vector.h"
#include "stack.h"
#include "vectorTestFunc.h" /* getVectorSize */

#define MAGIC_NUMBER 0xFAFA1989
#define TRUE 1
#define FALSE 0

static ADTErr CheckParam(Stack *_stack);

struct Stack
{
    Vector *m_vector;
    size_t m_MagicNumber;
};

Stack *StackCreate(size_t _size, size_t _blockSize)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));

    if(NULL == stack)
    {
        return NULL;
    }

    stack->m_vector = VectorCreate(_size, _blockSize);
    
    if(NULL == stack->m_vector)
    {
        free(stack);
        stack = NULL;
        return NULL;
    }

    stack->m_MagicNumber = MAGIC_NUMBER; 

    return stack;
}

void StackDestroy(Stack *_stack)
{
    if(NULL != _stack && _stack->m_MagicNumber == MAGIC_NUMBER)
    {
        _stack->m_MagicNumber = 0;

        VectorDestroy(_stack->m_vector);
        _stack->m_vector = NULL;

        free(_stack);
    }
}

ADTErr StackPush(Stack *_stack, int _item)
{
    if(ERR_OK != CheckParam(_stack))
    {
        return ERR_NOT_INITIALZED;
    }

    return VectorAdd(_stack->m_vector, _item);
}

ADTErr StackPop(Stack *_stack, int * _item)
{
    if(ERR_OK != CheckParam(_stack) || NULL == _item)
    {
        return ERR_NOT_INITIALZED;
    }

    return VectorDelete(_stack->m_vector, _item);
}

ADTErr StackTop(Stack *_stack, int * _item)
{
    size_t numOfItem = 0;

    if(ERR_OK != CheckParam(_stack) || NULL == _item)
    {
        return ERR_NOT_INITIALZED;
    }

    VectorItemsNum(_stack->m_vector, &numOfItem);

    if(0 == numOfItem)
    {
        return ERR_STACK_IS_EMPTY;
    }

    return VectorGet(_stack->m_vector,numOfItem - 1, _item); 
}

int StackIsEmpty(Stack *_stack)
{
    size_t numOfItem = -1;

    if(ERR_OK != CheckParam(_stack))
    {
        return FALSE;
    }
    
    if (ERR_OK == VectorItemsNum(_stack->m_vector, &numOfItem))
    {
        return (0 == numOfItem);
    }
    
    return FALSE;
}

void StackPrint(Stack *_stack)
{
    if(ERR_OK == CheckParam(_stack))
    {
        VectorPrint(_stack->m_vector);
    }
}

ADTErr GetStackSize(Stack *_stack, size_t *_size)
{
    if( ERR_OK == CheckParam(_stack) && NULL != _size)
    {
        return GetVectorSize(_stack->m_vector, _size);
    }

    return ERR_NOT_INITIALZED;
}


static ADTErr CheckParam(Stack *_stack)
{
    if(NULL != _stack && MAGIC_NUMBER == _stack->m_MagicNumber)
    {
        return ERR_OK;
    }

    return ERR_NOT_INITIALZED;
}