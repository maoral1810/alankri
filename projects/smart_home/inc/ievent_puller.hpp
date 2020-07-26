#ifndef IEventPuller_HPP
#define IEventPuller_HPP

#include "common_utils.hpp"
#include "event.hpp"

namespace smart_home
{
class IEventPuller {
public:
    //IEventPuller() = default;
    virtual ~IEventPuller();

    virtual void PullEvent(Shared_Ptr<Event>& a_retval) = 0;
};

inline IEventPuller::~IEventPuller()
{}

} // namespace smart_home

#endif // IEventPuller_HPP