#include <string.h>     /* strlen    */
#include <stddef.h>     /* size_t    */
#include <stdio.h>      /* printf    */
#include <ctype.h>      /* is,digits */
#include <math.h>       /* pow       */
#include "mystring.h"

static int ChackParmeters(char *str);
static void Swap(char *a, char *b);
static void RotateLeft(char *str, size_t len);
static int CountDigits(int num);

int ReverseString(char *str)
{
    int status = 0;
    size_t len = 0; 

    char *head = str;
    char *tail = str;

    status = ChackParmeters(str);
     
    if(!status)
    {
        len = strlen(str);
        tail += len - 1;

        while (head < tail)
        {
            Swap(head, tail);
            ++head;
            --tail;
        }
    }

    return status;
}

int DecToBin(int num)
{
    int status = 0;
    int exponent = 1;
    int i = 1;

    if(num < 0)
    {
        status = INPUT_ERROR;
    }

    if(!status)
    {
        
        for(;num > exponent; ++i ,exponent *= 2){} /* calc the big exponent in num */

        exponent /= 2;

        for(;exponent > 0; exponent /= 2)
        {
            printf("%c",(num / exponent) + '0');
/*              printf("%d\n",num );  */           
            if (num >= exponent)
            {
                num -= exponent;
            }
        }

        putchar('\n');
    }

    return status;
}

int Squeeze(char *str1, const char *str2)
{
    size_t len1 = 0;
    size_t len2 = 0;
    size_t i = 0;
    size_t j = 0;

    if(str1 == NULL || str2 == NULL)
    {
        return INPUT_ERROR;
    } 

    len1 = strlen(str1);
    len2 = strlen(str2);
    
    for(;i < len2; ++i)
    {
        for(j = 0; j < len1; ++j)
        {
            if (str1[j] == str2[i])
            {
                RotateLeft(str1 + j, len1 - j);
            }
        }
    }
    
    return OK;
}

int MyAtoi(char *str, int *res)
{
    size_t len = 0;
    size_t i = 0;
    char sign = 0; 
    int sum = 0;

    if (str == NULL)
    {
        return INPUT_ERROR;
    }
    
    len = strlen(str);
    
    while(*str == ' ') /* forward space before num in str */
    {
        ++str;
        --len;
    }
    
    if (*str == '-' || *str == '+')  /* can only be 1 time in the beginnig*/
    {
        sign = *str;
        ++str;
        --len;
    }
    
    for(i = 0 ;i < len; ++i, ++str)
    {
        if (isdigit(*str))     /*chack if its a number*/
        {
            sum = (sum + (*str - '0')) * 10;
        }
        else
        {
            break;
        }
    }

    
    if (sign == '-')
    {
        sum *= -1;
    }
    
    sum /= 10;
    *res = sum;

    return OK;
}


int MyItoa(int num, char *res)
{
    int status = ChackParmeters(res);
    int digits = CountDigits(num);

    if(!status)
    {
        if (num < 0)
        {
            *res = '-';
            ++res;
        }

        for(; digits > 0; --digits, ++res)
        {
            int exp = pow(10, digits - 1);
            char dig = num / exp;
            
            *res = dig + '0';
            num -= exp *dig; 
        }

        *res = '\0';
    }

    return status;
}


/* %%%%%%%%%%%%%%%%%%%% static functions %%%%%%%%%%%%%%%%%%%%*/

static void RotateLeft(char *str, size_t len)
{
    size_t i = 0;

    for(; i < len ; ++i)
    {
        str[i] = str[i+1];
    }
}


static void Swap(char *a, char *b)
{
    char save_data = *a;
    *a = *b;
    *b = save_data;
}

static int ChackParmeters(char *str)
{
    if (NULL == str)
    {
        return INPUT_ERROR;
    }

    return OK;
}

static int CountDigits(int num)
{
    int i = 0;
    
    for(; num > 0 ; num /= 10 , ++i) {} /* count digits */
    
    return i;
}

