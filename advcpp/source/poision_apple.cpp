#include "poision_apple.hpp"

namespace advcpp{

void PoisionApple::Run()
{
    throw PoisionAppleException();
}

const char* PoisionAppleException::what() const NOEXCEPTIONS
{
    return "poision apple";
}

}// advcpp
