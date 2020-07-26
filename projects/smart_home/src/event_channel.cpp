#include "event_channel.hpp"
#include "waitable_bounded_queue.hpp"

namespace smart_home
{
static const size_t eventQueueSize = 10; // what is the optimal size ??? need to get it in the constractor?

EventChannel::EventChannel()
    : m_eventQueue(eventQueueSize)
{}

EventChannel::~EventChannel()
{}

void EventChannel::Push(EventAddress a_val)
{
    try {
        m_eventQueue.Enqueue(a_val);
    }
    catch(const WaitableBoundedQueueShutdownException& exp)
    {
        throw EventChannelShutdownExp();
    }
}

void EventChannel::Pull(EventAddress& a_retval)
{
    try{
        m_eventQueue.Dequeue(a_retval);
    }
    catch(const WaitableBoundedQueueShutdownException& exp)
    {
        throw EventChannelShutdownExp();
    }
}

void EventChannel::Shutdown()
{
    m_eventQueue.ShutDownQueue(0);
}

} // namespace smart_home







