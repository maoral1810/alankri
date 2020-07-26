#ifndef CONDITION_VARIABLE_EXCEPTIONS_HPP
#define CONDITION_VARIABLE_EXCEPTIONS_HPP

#include <exception>
#include "common_utils.hpp"

namespace smart_home {

class ConditionVarInitENOMEM : public std::exception {

    virtual const char* what() const NOEXCEPTIONS
    {
      return ("ENOMEM: Insufficient memory exists to initialize the condition variable");
    }
};

class ConditionVarInitEAGAIN : public std::exception {

    virtual const char* what() const NOEXCEPTIONS
    {
      return ("EAGAIN: The system lacked the necessary resources (other than memory) to initialize another condition variable");
    }
};

// ------------------------ 

class ConditionVarWaitEPERM : public std::exception {

    virtual const char* what() const NOEXCEPTIONS
    {
      return ("EPERM: The mutex was not owned by the current thread at the time of the call");
    }
};


} // namespace smart_home


#endif // CONDITION_VARIABLE_EXCEPTIONS_HPP