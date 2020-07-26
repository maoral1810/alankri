
#include <stdio.h> /* printf */
#include "trig.h"

#define RESET       "\033[0m"
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red  */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */

int main (void)
{
    int err = 0;
        
    if (TRIG_OK != trig1(6, '$'))
    {
        ++err;
    }
    
    putchar('\n');
    
    if (TRIG_OK != trig2(6, '$'))
    {
        ++err;
    }
    
     putchar('\n');
    
    if (TRIG_OK != trig3(6, '$'))
    {
        ++err;
    }
    
    putchar('\n');
    
    if (TRIG_OK != trig4(6, '$'))
    {
        ++err;
    }
    
    putchar('\n');
    
    if (TRIG_OK != trig5(6, '$'))
    {
        ++err;
    }
    
    putchar('\n');
    
    if (TRIG_OK != trig6(6,'$'))
    {
        ++err;
    }
    
    putchar('\n');
    
    if (err)
    {
        printf(BOLDRED"program failed with %d errors \n"RESET, err);
    }
    else
    {
        printf(BOLDGREEN"sucsses"RESET);
    }
        
    return 0;
}
