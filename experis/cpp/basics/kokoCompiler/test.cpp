#include <iostream> //cout
#include <string> 
#include "parsar.h"


int main(int argc, char *argv[])
{
    Parcer_t par; //= new Parcer_t(argv[1]);

    par.Parse(argv[1]);
    
    return 0;
}