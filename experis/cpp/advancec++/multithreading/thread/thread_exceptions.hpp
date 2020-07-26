#ifndef __THERAD_EXCEPTIONS_HPP__
#define __THERAD_EXCEPTIONS_HPP__

#include <exception>

namespace experis {

class ThreadCreateEAGAIN : public std::exception {

  virtual const char* what() const throw()
  {
    return ("EAGIN:Insufficient resources to create another thread");
  }
}EAGAINExeption;

class ThreadCreateEPERM : public std::exception {

  virtual const char* what() const throw()
  {
    return ("EPERM: No permission to set the scheduling policy and parameters specified in attr");
  }
}EPERMExeption;

}// namespce experis


#endif //__THERAD_EXCEPTIONS_HPP__