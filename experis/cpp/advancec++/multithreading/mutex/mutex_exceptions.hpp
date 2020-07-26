#ifndef __MUTEX_EXCEPTIONS_HPP__
#define __MUTEX_EXCEPTIONS_HPP__

#include <exception>

namespace experis {

class MutexCreateEINVAL : public std::exception {

  virtual const char* what() const throw()
  {
    return ("EINVAL:the mutex has not been properly initialized");
  }
}EINVALExeption;

}// namespace experis
#endif //__MUTEX_EXCEPTIONS_HPP__