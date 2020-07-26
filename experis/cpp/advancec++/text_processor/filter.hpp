#ifndef __FILTER_HPP__
#define __FILTER_HPP__

#include <vector>
#include "input.hpp"
#include "output.hpp"
#include "procces_char.hpp"

namespace experis{

class Filter{
public:
    Filter(){}
    virtual ~Filter(){}
    //Filter(const Filter& a_input) = default;
    //Filter operator=(const Filter& a_input) = default;

    //API Functions
    virtual experis::ProcessChar FilterStream(char* a_inputBuffer, size_t a_sizeOfBuffer) = 0;
private:

};

}// experis
#endif //__FILTER_HPP__