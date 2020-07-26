#include <iostream>
#include <dlfcn.h>

int main(void)
{
    class Cat;
    
    Cat* (*create)();
    void (*destroy)(Cat*);
    void (*yowl)(Cat*);

    void* handle = dlopen("./libcat.so", RTLD_NOW);

    if(!handle)
    {
        std::cout<< dlerror() << std::endl;
    }

    create = (Cat* (*)())dlsym(handle, "create_object");
    if(!create)
    {
        std::cout<< dlerror() << std::endl;
    }

    destroy = (void (*)(Cat*))dlsym(handle, "destroy_object");
    if(!destroy)
    {
        std::cout<< dlerror() << std::endl;
    }
    
    yowl = (void (*)(Cat*))dlsym(handle, "yowl");

    Cat* garfield = create();
    yowl(garfield);
    destroy(garfield);
   
    return 0;
}