#ifndef WAITABLE_BOUNDED_QUEUE_EXCEPTIONS
#define WAITABLE_BOUNDED_QUEUE_EXCEPTIONS

#include <exception>
#include "common_utils.hpp"

class WaitableBoundedQueueShutdownException : public std::exception {
    virtual const char* what() const NOEXCEPTIONS
    {
      return ("ShutDown:");
    }
};




#endif // WAITABLE_BOUNDED_QUEUE_EXCEPTIONS