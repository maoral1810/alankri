#include <iostream> // cout
#include "single_ptr.hpp" 


int main(void) {
    int i = 5;
    int *p = new int(i);
    experis::SinglePtr<int> relesePtr(p);

    std::cout<< *relesePtr << std::endl;

    return 0;
}
