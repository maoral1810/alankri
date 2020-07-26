#ifndef __THERAD_EXCEPTIONS_HPP__
#define __THERAD_EXCEPTIONS_HPP__

#include <exception>

namespace advcpp {

class ThreadCreateEAGAIN : public std::exception {

  virtual const char* what() const throw()
  {
    return ("EAGIN:Insufficient resources to create another thread");
  }
};

class ThreadCreateEPERM : public std::exception {

  virtual const char* what() const throw()
  {
    return ("EPERM: No permission to set the scheduling policy and parameters specified in attr");
  }
};

class ThreadTimeJoinEDEADLK : public std::exception {
  virtual const char* what() const throw()
  {
    return ("EDEADLK: A deadlock was detected");
  }
};
}// namespce advcpp


#endif //__THERAD_EXCEPTIONS_HPP__