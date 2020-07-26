#include "stack.h" 
#include "colors.h"
#include <stdio.h>


#define TRUE 1
#define FALSE 0

static int IsCloser(char ch);
int IsValidPrantasis(char *_expresion);
static int IsMatch(char open, char close);
static void PrintResualt(char *_testName, char *_scenario , int err);

int main(void)
{
    char *goodExpresion = "({[]})";
    char *wrongExpresion ="{{(})(}{}";
    char *classExpresion = "(([{(({}[])[{()}])}]))";
    int err = 0;

    if(!IsValidPrantasis(goodExpresion))
    {
        ++err;
    }
    
    PrintResualt("IsValidPrantasis", "goodExpresion", err);
    err = 0;

    if(!IsValidPrantasis(wrongExpresion))
    {
       ++err; 
    }
    
    PrintResualt("IsValidPrantasis", "wrongExpresion", err);
    err = 0;
    
    if(!IsValidPrantasis(classExpresion))
    {
       ++err; 
    }

    PrintResualt("IsValidPrantasis", "classExpresion", err);
    return 0;
}


int IsValidPrantasis(char *_expresion)
{
    Stack *stack = StackCreate(10, 10);
    int open = 0;
    size_t i = 0;

    if(NULL == stack)
    {
        return TRUE;
    }
    
    for(;_expresion[i] != '\0'; ++i)
    {
        if(IsCloser(_expresion[i]))
        {
            if(!StackIsEmpty(stack))
            {
                StackPop(stack, &open);
                
/*                 printf("open = %c \t", open);
                printf("close = %c \n", _expresion[i]); */

                if(!IsMatch((char)open, _expresion[i]))
                {
                    return FALSE;
                }  
            }
        }
        
        else
        {
            StackPush(stack, (int)_expresion[i]);
        }
    }

   return StackIsEmpty(stack);
}

static int IsCloser(char ch)
{
    return (ch == '}' || ch == ']' || ch == ')' ) ? TRUE : FALSE;
}

static int IsMatch(char open, char close)
{
    if( (open == '(' && close == ')') ||
        (open == '[' && close == ']') ||
        (open == '{' && close == '}'))
    {
        return TRUE;
    }

    return FALSE;
}

static void PrintResualt(char *_testName, char *_scenario , int err)
{
    if(err)
    {
        printf(BOLDCYAN"%s"BOLDMAGENTA":%s: "BOLDRED"FAIL!\n"RESET,
        _testName, _scenario); 
    }
    else
    {
        printf(BOLDCYAN"%s"BOLDMAGENTA":%s: "BOLDGREEN"SUCSSES \n"RESET,_testName, _scenario);
    }
}



