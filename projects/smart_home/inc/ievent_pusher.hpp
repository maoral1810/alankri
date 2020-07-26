#ifndef IEventPusher_HPP
#define IEventPusher_HPP

#include "common_utils.hpp"
#include "event.hpp"

namespace smart_home
{
class IEventPusher {
public:
    //IEventPusher() = default;
    virtual ~IEventPusher();

    virtual void PushEvent(Shared_Ptr<Event> a_event) = 0;
};

inline IEventPusher::~IEventPusher()
{}

} // namespace smart_home



#endif //IEventPusher_HPP