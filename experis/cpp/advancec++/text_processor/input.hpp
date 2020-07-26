#ifndef __INPUT_HPP__
#define __INPUT_HPP__

namespace experis{

class Input{
public:
    //Input() = default
    virtual ~Input(){}
    //Input(const Input& a_input) = default;
    //Input operator=(const Input& a_input) = default;

    //API functions
    virtual size_t Read(char* a_buffer ,size_t a_bufferSize) = 0;
private:

};

}// experis

#endif // __INPUT_HPP__