#include <iostream>
#include <unistd.h> // sleep
#include "cat.hpp"

Cat::Cat()
{}

void Cat::yowl()
{
    std::cout << "meowww";
    sleep(1);
    std::cout << ".";
    sleep(1);
    std::cout << ".";
    sleep(1);
    std::cout << "." << std::endl;
    sleep(1);
    std::cout << "meowww";
    sleep(1);
    std::cout << ".";
    sleep(1);
    std::cout << ".";
    sleep(1);
    std::cout << "." << std::endl;
    sleep(3);
    std::cout << "Shut The Fuck Up!!!!!!!" << std::endl;
    sleep(1);
}

extern "C" 
{
Cat* create_object()
{
    return new Cat; 
}

void destroy_object(Cat* object)
{
    delete object; 
} 

void yowl(Cat* a_cat)
{
    a_cat->yowl();
}

}// extern "C"
