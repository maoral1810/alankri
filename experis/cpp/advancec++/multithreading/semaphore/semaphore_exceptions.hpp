#ifndef __SEMAPHORE_EXCEPTIONS_HPP__
#define __SEMAPHORE_EXCEPTIONS_HPP__

#include <exception>

namespace experis {
// ------------------- init exception --------------------

class SemaphoreInitEINVAL : public std::exception {

  virtual const char* what() const throw()
  {
    return ("EINVAL: value exceeds to SEM_VALUE_MAX.");
  }
}InitEINVALExeption;

class SemaphoreInitENOSYS : public std::exception {

  virtual const char* what() const throw()
  {
    return ("ENOSYS: pshared is nonzero, but the system does not support process-shared ");
  }
}InitENOSYSExeption;

// ------------------------- wait exceptions------------------------

class SemaphoreWaitEINTR : public std::exception {

  virtual const char* what() const throw()
  {
    return ("EINTR: The call was interrupted by a signal handler ");
  }
}WaitEINTRExeption;

class SemaphoreWaitEINVAL : public std::exception {

  virtual const char* what() const throw()
  {
    return ("EINVAL: The value of abs_timeout.tv_nsecs is less than 0, or greater than or equal to 1000 million ");
  }
}WaitEINVALExeption;

class SemaphoreWaitETIMEDOUT : public std::exception {
    virtual const char* what() const throw()
    {
        return ("ETIMEDOUT: The call timed out before the semaphore could be locked ");
    }
}WaitETIMEDOUTExeption;

//------------------- post exceptions ----------------------

class SemaphorePostEINVAL : public std::exception {
    virtual const char* what() const throw()
    {
        return ("EINVAL: not a valid semaphore ");
    }
}postEINVALExeption;

class SemaphorePostEOVERFLOW : public std::exception {
    virtual const char* what() const throw()
    {
        return ("EOVERFLOW: The maximum allowable value for a semaphore would be exceeded ");
    }
}postEOVERFLOWExeption;



}// namespace experis
#endif //__SEMAPHORE_EXCEPTIONS_HPP__