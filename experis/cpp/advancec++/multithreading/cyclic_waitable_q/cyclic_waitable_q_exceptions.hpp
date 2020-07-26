#ifndef __CYCLIC_Q_EXCEPTIONS_HPP__
#define __CYCLIC_Q_EXCEPTIONS_HPP__

#include <exception>

namespace experis {

class ShutdownException : public std::exception {

  virtual const char* what() const throw()
  {
    return ("Shutdown: the queue is aboute to erase,please shutdown yourself");
  }
};

}// namespace experis
#endif //__CYCLIC_Q_EXCEPTIONS_HPP__