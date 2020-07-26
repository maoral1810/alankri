#ifndef POSION_APPLE_HPP
#define POSION_APPLE_HPP

#include <exception>

#include "runnable.hpp"

namespace smart_home {

class PoisionApple : public Runnable {
public:
    // PoisionApple() = default;
    // ~PoisionApple() = default;
    // PoisionApple(const PoisionApple& a_other) = default;
    // PoisionApple& operator=(const PoisionApple& a_other) = default;

    virtual void Run();
};

class PoisionAppleException : public std::exception
{
	const char* what() const NOEXCEPTIONS;
};


}// namespace smart_home

#endif //POSION_APPLE_HPP