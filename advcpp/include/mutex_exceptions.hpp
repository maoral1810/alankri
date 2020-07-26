#ifndef MUTEX_EXCEPTIONS_HPP
#define MUTEX_EXCEPTIONS_HPP

#include <exception>
#include "common_utils.hpp"

namespace advcpp {

class MutexInitENOMEM : public std::exception {

    virtual const char* what() const NOEXCEPTIONS
    {
      return ("ENOMEM:not have the privilege to perform the operation");
    }
};

class MutexInitEAGAIN : public std::exception {

    virtual const char* what() const NOEXCEPTIONS
    {
      return ("EAGAIN:The system lacked the necessary resources (other than memory) to initialise another mutex");
    }
};
// ----------------------------------------------
class MutexUnlockEAGAIN : public std::exception {

    virtual const char* what() const NOEXCEPTIONS
    {
      return ("EAGAIN:The mutex could not be acquired because the maximum number of recursive locks for mutex has been exceeded");
    }
};

class MutexUnlockEPERM : public std::exception {

    virtual const char* what() const NOEXCEPTIONS
    {
      return ("EPERM: The current thread does not own the mutex");
    }
};

// ---------------------------------

class MutexlockEDEADLK : public std::exception {

    virtual const char* what() const NOEXCEPTIONS
    {
      return ("EDEADLK: The current thread already owns the mutex");
    }
};






}// namespac advcpp
#endif //MUTEX_EXCEPTIONS_HPP