#include <iostream>
#include <dlfcn.h>
//#include "cat.hpp"
class Cat;
int main(void)
{
    void* handle = dlopen("./libcat.so", RTLD_NOW);

    if(!handle)
    {
        std::cout<< dlerror() << std::endl;
    }

    Cat* (*create)();
    void (*destroy)(Cat*);

    create = (Cat* (*)())dlsym(handle, "create_object");
    destroy = (void (*)(Cat*))dlsym(handle, "destroy_object");

    //void yowl_t = dlsym(handle, "yowl");

    //pf(42)
    //create cat object from the cat.so.1
    // call a function on the cat object

    return 1;
}