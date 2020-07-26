#ifndef __STRING_INPUT_HPP__
#define __STRING_INPUT_HPP__

#include <string>
#include "input.hpp"

namespace experis{

class StringInput : public Input {
public:
    StringInput(std::string* a_input)
    : Input()
    , m_str(a_input)
    {

    }
    virtual ~StringInput(){}
    StringInput(const StringInput& a_input);
    StringInput operator=(const StringInput& a_input);

    //API functions
    virtual size_t Read(char* a_buffer ,size_t a_bufferSize){ return m_str->copy(a_buffer, a_bufferSize); }
    
private:
    std::string* m_str;
};
}// namespace experis
#endif // __STRING_INPUT_HPP__