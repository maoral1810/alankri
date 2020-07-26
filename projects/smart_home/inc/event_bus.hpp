#ifndef EVENT_BUS_HPP
#define EVENT_BUS_HPP

#include <tr1/memory>

#include "event.hpp"
#include "waitable_bounded_queue.hpp"
#include "common_utils.hpp"
#include "ievent_puller.hpp"
#include "ievent_pusher.hpp"

namespace smart_home
{
class EventBus : private Uncopyable , public IEventPusher , public IEventPuller  { 
public:
    EventBus(size_t a_size);
    //~EventBus() = default;

    virtual void PushEvent(Shared_Ptr<Event> a_event);
    virtual void PullEvent(Shared_Ptr<Event>& a_retval);
    void Shutdown();

private:
    WaitableBoundedQueue<std::tr1::shared_ptr<Event> > m_events;   
};
    
} // namespace smart_home


#endif //EVENT_BUS_HPP