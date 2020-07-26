#ifndef __OUTPUT_HPP__
#define __OUTPUT_HPP__

namespace experis{

class Output{
public:
    Output(){}
    virtual ~Output(){}
    //Output(const Output& a_Output) = defualt;
    //Output operator=(const Output& a_input) = defualt;

    //API functions
    virtual size_t Write(char* a_buffer ,size_t a_numOfChars) = 0;
private:

};
}// namespace experis
#endif //__OUTPUT_HPP__