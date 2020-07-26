#include "event_bus.hpp"
#include "waitable_bounded_queue.hpp"

namespace smart_home
{
EventBus::EventBus(size_t a_size)
    : m_events(a_size)
{}

void EventBus::PushEvent(Shared_Ptr<Event> a_event)
{
    try{
        m_events.Enqueue(a_event);
    }
    catch(const WaitableBoundedQueueShutdownException& exp) // catch shutdown exception of queue
    {
        throw EventBusShutdownExp();
    }
}

void EventBus::PullEvent(Shared_Ptr<Event>& a_retval)
{
    try{
        m_events.Dequeue(a_retval);
    }
    catch(const WaitableBoundedQueueShutdownException& exp) // catch shutdown exception of queue
    {
        throw EventBusShutdownExp();
    }
}

void EventBus::Shutdown()
{
    m_events.ShutDownQueue(0);
}
} // namespace smart_home