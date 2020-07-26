#ifndef EVENT_CHANNEL_HPP
#define EVENT_CHANNEL_HPP

#include <cstddef> // size_t

#include "event.hpp"
#include "common_utils.hpp"
#include "subscribers_list.hpp"
#include "ievent_address_puller.hpp"
#include "ievent_address_pusher.hpp"
#include "ievent_puller.hpp"
#include "event_bus.hpp"

namespace smart_home
{
class EventChannel : public IEventAddressPuller, public IEventAddressPusher 
{
public:
    EventChannel();
    ~EventChannel();

    virtual void Push(EventAddress a_val);
    virtual void Pull(EventAddress& a_retval);
    void Shutdown(); // 

private:
    WaitableBoundedQueue<EventAddress> m_eventQueue; 
};
    
} // namespace smart_home

#endif //EVENT_CHANNEL_HPP

