#include <stdio.h> 	    /* printf */ 
#include <string.h>     /* strlen */
#include <assert.h>     /* assert */
#include <math.h>       /* pow    */
#include "c_exe 1.h"    /* h file */

/* static functions */
static int CountDigits(int num);
static int CalcAmstrongNum(int num);
static unsigned long Pow(int base ,unsigned int exp);   /*pow by base*/

void CalAndPrint(int a, int b)
{
    printf("\nthe sum of a + b = %d \n", a+b);
    printf("the difference between a & b = %d \n", a-b);
    printf("the multiply of a * b = %d \n", a*b); 
}

int Factorial(int num)
{
	int sum = 1;
	int i = 0;
    
    if (num < -20 || num > 20)
    {
        return NOT_IN_RANGE;
    }
	
    if (0 == num)/* private for zero */
    {
        return 1;
    }

    for (i = num; i > 0; --i)
	{
		sum *= i;		
	}
	
	return sum;
}

int IsPalindrome(int num)
{
    int i = 0;
    int digits = CountDigits(num);
    int head = Pow(10, digits - 1);
    int tail = 10;
    
    digits = digits / 2 ; /* we need to do a digits / 2 checks */ 
    
    for(;i > digits / 2; ++i)
    {
        if ( num % head != num % tail)
        {
            return FAIL;
        }
        
        num = (num % head * head) / 10;
    }
    
    return SUCSSES;
}

int IsPrimeNumber(int num)
{
    if ( (0 == num % 2) || (0 == num % 3) || (0 == num % 5) || (0 == num % 7) )
    {
        return 1;
    }
    
    return 0; 
}

int IsAccendingOrder(int num)
{
    int first_num = num % 10;
    
    num /= 10;
    
    for ( ; num > 0; num /= 10)
    {
        if ( first_num < num % 10)
        {
            return 1;
        }
        
        first_num = num % 10;
    }
    
    return 0;
}

int ReverseNum(int num)
{
    int resualt = 0;
    int digits = CountDigits(num);
    int exp = Pow(10, digits - 1);
    
    for ( ;num > 0; num /= 10, exp /= 10)
    {
        resualt +=  (num % 10) * exp;
    }
    
    return resualt;
}

void PrintAmstrongNum(void)
{
    int i = 0;
    
    for ( ; i < 1000; ++i)
    {
        
        if (CalcAmstrongNum(i) == i)
        {
            printf("%d ", i);
        }
    }
    putchar('\n');
}

/* static functions */
static int CalcAmstrongNum(int num)
{
    int res = 0;
   
    for (;num > 0; num /= 10)
    {
        res += Pow(num % 10, 3);
    }
    
    return res;
}

static int CountDigits(int num)
{
    int i = 0;
    
    for(; num > 0 ; num /= 10 , ++i) {} /* count digits */
    
    return i;
}

static unsigned long Pow(int base ,unsigned int exp)   /*pow by base*/
{
    double res = 1;

    while (exp > 0)
    {
        res *= base;
        --exp;
    }

    return res;
}






