#include <stdio.h>  /* printf     */
#include <stdlib.h> /* atoi, itoa */
#include "mystring.h"

#define RESET       "\033[0m"
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green    */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red      */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue     */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow   */

int main(void)
{
    char str1[4] = "Maor";
    char *str2 = "ar";
    char *str3[] = {"  -1234556","2223abc","5B005`"};
    char itoa_res[32] = "";
    
    int num = 9898988;
    int err = 0;
    int res[3] = {0};
    size_t i = 0;

    printf("\n=========================== ReverseString ====================\n");
    printf ("string before reverse = %s\n",str1);

    if (ReverseString(str1))
    {
        ++err;
        printf(BOLDRED"failed with ReverseString!!!\n"RESET); 
    } 
    
    printf ("string after reverse = %s\n",str1);

    printf("\n=========================== DecToBin ====================\n");
    if(DecToBin(num))
    {
        ++err;
        printf(BOLDRED"failed with DecToBin!!!\n"RESET); 
    }

    ReverseString(str1);

    printf("\n=========================== Squeeze ====================\n");
    printf("string = %s  char to delete = %s\n", str1, str2);
    if(Squeeze(str1,str2))
    {
        ++err;
        printf(BOLDRED"failed with Squeeze!!!\n"RESET); 
    }
    printf("\nstring after Squeeze = %s\n", str1);

     printf("\n=========================== MyAtoi ====================\n");
    for (i = 0; i < ARR_LENGTH(str3); ++i)
    {
        if(MyAtoi(str3[i], &res[i]))
        {
            ++err;
            printf(BOLDRED"failed with MyAtoi!!! input error\n"RESET); 
        }

        printf("MyAtoi = %d   atoi = %d \n", res[i], atoi(str3[i]));
    }

   
    printf("\n=========================== MyItoa ====================\n");
    if(MyItoa(num, itoa_res))
    {
        ++err;
        printf(BOLDRED"failed with MyItoa!!!\n"RESET); 
    }

    printf("MyItoa = %s num = %d \n", itoa_res, num);

    return 0;
    
}

