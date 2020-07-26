#include "to_upper.hpp"

virtual experis::ProcessChar FilterStream(char* a_inputBuffer, size_t a_sizeOfBuffer) {
    for(int i = 0; i < a_sizeOfBuffer; ++i)
    {
        a_inputBuffer[i] = toupper(a_inputBuffer[i]);
    }
    //return process_char
}