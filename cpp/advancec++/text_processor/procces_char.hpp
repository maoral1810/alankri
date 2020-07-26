#ifndef __PROCESS_CHAR_HPP__
#define __PROCESS_CHAR_HPP__

#include <vector>
#include "input.hpp"
#include "output.hpp"
#include "filter.hpp"
#include "processor.hpp"

namespace experis{

class ProcessChar{

    ProcessChar(){}
    //~ProcessChar() = default;
    //ProcessChar(const ProcessChar& a_input) = default;
    //ProcessChar operator=(const ProcessChar& a_input) = default;

    //API Functions
    std::string Resualt();//const???
    size_t NumOfChar()const{ return m_numOfChars; }

private:
    size_t m_numOfChars;
};
}// namespace experis

#endif //__PROCESS_CHAR_HPP__
