#include <dlfcn.h> /* dlopen, dlsym */
#include <stdio.h> /* printf,  NULL */

int main(void)
{
    void *dllD;
    int a = 5;
    int b = 3;
    int (*functionp)(int, int);

    dllD = dlopen("libdl.so", RTLD_LAZY);
    
    if(NULL == dllD)
    {
        return 0;
    }

    functionp = dlsym(dllD,"add");
    
    printf("a = %d\n", a);
    a = functionp(a,b);

    printf("a = %d\n", a);

    return 0;
}