#ifndef __TO_UPPER_HPP__
#define __TO_UPPER_HPP__

#include <cctype>
#include "filter.hpp"

namespace experis{

class ToUpper: public experis::Filter{
public:
    ToUpper(){}
    virtual ~ToUpper(){}
    ToUpper(const ToUpper& a_input);
    ToUpper operator=(const ToUpper& a_input);

    //API Functions
    virtual experis::ProcessChar FilterStream(char* a_inputBuffer, size_t a_sizeOfBuffer);
private:


};
}// namespace experis
#endif //__TO_UPPER_HPP__