#ifndef __STRING_OUTPUT_HPP__
#define __STRING_OUTPUT_HPP__

#include <sstream>      // std::stringstream
#include "output.hpp"

namespace experis{

class StringOutput:public Output{
public:
    StringOutput(std::string* a_str)
    :m_output(a_str)
    {

    }
    virtual ~StringOutput(){}
    //StringOutput(const StringOutput& a_input) = default;
    //StringOutput operator=(const StringOutput& a_input) = default;

    //API functions
    virtual size_t Write(char* a_buffer ,size_t a_numOfChars){ 
        m_output->assign(a_buffer, a_numOfChars);
        return m_output->size();
    }
    
private:
    std::string* m_output;
};
} // namespace experis
#endif // __STRING_OUTPUT_HPP__