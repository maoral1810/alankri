#include "poision_apple.hpp"

namespace smart_home {

void PoisionApple::Run()
{
    throw PoisionAppleException();
}

const char* PoisionAppleException::what() const NOEXCEPTIONS
{
    return "poision apple";
}

}// namespace smart_home
