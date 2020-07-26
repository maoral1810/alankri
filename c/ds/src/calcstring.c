#include "stack.h" 
#include "colors.h"     /* colors  */
#include "ADTDefs.h"    /* errors  */
#include <stdio.h>      /* printf  */
#include <ctype.h>      /* isdigit */
#include <string.h>     /* strlen  */  
#include <stdlib.h>     /* malloc, free */

#define TRUE 1
#define FALSE 0

static ADTErr ChackParam(Stack *_stack, char *_expresion, char *_postfix);
/* infix postfix convert function */
static ADTErr InfixToPostfix(Stack *_stack, char *_expresion, char *_postfix);
static int IsOperator(char ch);
static ADTErr OperatorHandler(Stack *_stack, char _operator, char **_postfix);
static int IsHighPriority(Stack *_stack, char _operator);
static void InsertFromStack(Stack *_stack, char *_postfix);
static void PopUntilOpener(Stack *_stack, char **_postfix);
/* calculte postfix expresion function */
static ADTErr CalcPostfix(char *_postfix, int *_res);
static int CalcOperands(char _operator, int _left, int _right);

static void PrintResualt(char *_testName, char *_postfix , int err);

ADTErr CalcString(char *_expresion, int *_res);

int main(void)
{
    char *expresion[] = {"(2*5)+(4*9+5)", "2 + 3+(5*1+2)*3" ,"", 
                        "(2*0)+6/2*(9+8*1)", "1-2+5-1-1+(2*0)"};
    int excepted[] = {51, 26, 0, 51, 2};
/*     char *expresion1 = "2 + 3+(5*1+2)*3";
    char *expresion2 = "";
    char *expresion3 ="(2*0)+6/2*(9+8*1)";
    char *expresion4 ="1-2+5-1-1+(2*0)";
     */
    size_t i = 0;
    size_t size = sizeof(expresion) / sizeof(expresion[0]);
    

    for( i = 0; i < size; ++i)
    {
        int res = 0;
        CalcString(expresion[i], &res);
        printf(YELLOW"Expresion = %s\n\nRes = %d\tExepted resualt = %d\n\n",
               expresion[i],res,excepted[i]);
    }

  
    if(ERR_NOT_INITIALZED != CalcString(NULL, NULL))
    {
        printf(BOLDBLUE"CalcString with NULLS "BOLDRED"FAILED\n"RESET);
    }
    else
    {
        printf(BOLDBLUE"CalcString with NULLS "BOLDGREEN"SUCSSES\n"RESET);
    }
        
    return 0;
}

ADTErr CalcString(char *_expresion, int *_res)
{
    Stack *stack = NULL;
    char *postfix = NULL;
    int err = 0;
    
    if(NULL == _expresion || NULL == _res)
    {
        return ERR_NOT_INITIALZED;
    } 

    stack = StackCreate(10, 10);
    if(stack == NULL)
    {
        return ERR_ALLOCTAION_FAILED;
    }

    postfix =(char *)malloc(sizeof(char) * strlen(_expresion) + 1);
    
    if(ERR_OK != InfixToPostfix(stack, _expresion, postfix))
    {
        ++err;
    }

    if(ERR_OK !=  CalcPostfix(postfix, _res))
    {
        ++err;
    }

    PrintResualt("CalcString", postfix, err);

    StackDestroy(stack);
    free(postfix);

    return ERR_OK;
}

static ADTErr  CalcPostfix(char *_postfix, int *_res)
{
    Stack *stack = StackCreate(10,10);
    ADTErr status = ChackParam(stack, _postfix, _postfix);

    if(ERR_OK == status && NULL != _res) 
    {
        while('\0' !=  *_postfix)
        {
            if(isdigit(*_postfix))
            {
                StackPush(stack, *_postfix - '0');
                
            }

            else /* operator */
            {
                int right = 0;
                int left = 0;
                int operandsRes = 0;

                StackPop(stack, &right);
                StackPop(stack, &left);

                operandsRes = CalcOperands(*_postfix, left, right);

                StackPush(stack, operandsRes); 
                
            }
            
            ++_postfix;

        }
            StackPop(stack, _res);
    }
    
    return status;
}

static ADTErr InfixToPostfix(Stack *_stack, char *_expresion, char *_postfix)
{
    if(ERR_OK != ChackParam(_stack, _expresion, _postfix))
    {
        return ERR_NOT_INITIALZED;
    }

    while('\0' != *_expresion) /* run on all _expresion */
    {
        if(isdigit(*_expresion))
        {
            *_postfix = *_expresion;
            ++_postfix;
        }

        else if(IsOperator(*_expresion))
        {
            OperatorHandler(_stack, *_expresion, &_postfix);
        }
 
        else if (*_expresion == ')')
        {
            PopUntilOpener(_stack, &_postfix);
            
        }

        ++_expresion;
    }
    /* put all the rest of operators from stack in postfix*/ 
    while(!StackIsEmpty(_stack))
    {
        int operator = 0;
        StackPop(_stack, &operator);
        *_postfix = (char)operator;
        ++_postfix;
    }

    *_postfix = '\0';

    return ERR_OK;
}

static void PopUntilOpener(Stack *_stack, char **_postfix)
{
    /* StackPop(_stack, &operator); */
    int operator = 0;
    StackPop(_stack, &operator);

    while(operator != '(')
    {
        **_postfix = operator;
        ++*_postfix;
        StackPop(_stack, &operator);
    }

}

static ADTErr ChackParam(Stack *_stack, char *_expresion, char *_postfix)
{
    if(NULL == _stack || NULL == _expresion || NULL == _postfix)
    {
        return ERR_NOT_INITIALZED;
    }

    return ERR_OK;
}

static ADTErr OperatorHandler(Stack *_stack, char _operator, char **_postfix)
{
    ADTErr status = ChackParam(_stack, *_postfix, *_postfix);
    
    if(ERR_OK == status)
    {
        if(IsHighPriority(_stack, _operator))
        {
             InsertFromStack(_stack, *_postfix);
            ++*_postfix;
        }

        StackPush(_stack, _operator);
    }

    return status;
}

static int IsOperator(char ch)
{
    if(ch == '*' || ch == '/' || ch == '+' || ch == '-' || ch == '(')
    {
        return TRUE;
    }

    return FALSE;
}

static void InsertFromStack(Stack *_stack, char *_postfix)
{
    int toAdd = 0;
    
    StackPop(_stack, &toAdd);
    *_postfix = (char)toAdd;
}

static int IsHighPriority(Stack *_stack, char _operator)
{
    int stackOperator = 0;
    
    if ( NULL != _stack)
    {
        StackTop(_stack, &stackOperator);
    
        if((_operator == '+' || _operator == '-' ) &&
          (stackOperator == '*' || stackOperator == '/'))
        {
            return TRUE;
        }

        else if((_operator == '+' || _operator == '-' ) &&
          (stackOperator == '+' || stackOperator == '-'))
        {
            return TRUE;
        }

        else if((_operator == '*' || _operator == '/' ) &&
          (stackOperator == '*' || stackOperator == '/'))
        {
            return TRUE;
        }
    }

    return FALSE;
}

static int CalcOperands(char _operator, int _left, int _right)
{
    int res = 0;

    switch (_operator)
    {
        case '+':
            res = _left + _right;
            break;
        
        case '-':
            res = _left - _right;
            break;

        case '*':
            res = _left * _right;
            break;

        case '/':
            res = _left / _right;
            break;

        default:
            break;
    }
    
    return res;
}

static void PrintResualt(char *_testName, char *_postfix , int err)
{
    if(err)
    {
        printf(BOLDCYAN"%s"BOLDMAGENTA":%s: "BOLDRED"FAIL!\n"RESET,
        _testName, _postfix); 
    }
    else
    {
        printf(BOLDCYAN"%s"BOLDMAGENTA":%s: "BOLDGREEN"SUCSSES \n"RESET,_testName, _postfix);
    }
}