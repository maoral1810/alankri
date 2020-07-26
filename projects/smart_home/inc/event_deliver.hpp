#ifndef EVENT_DELIVER_HPP
#define EVENT_DELIVER_HPP

#include "runnable.hpp"
#include "ievent_address_puller.hpp"
#include "common_utils.hpp"

namespace smart_home
{

class EventDeliver : public Runnable
{
public:
    EventDeliver(Shared_Ptr<EventChannel> a_eventQueue);
    //~EventDeliver() = default;

    virtual void Run();
    void ShutDown() NOEXCEPTIONS;
private:
    Shared_Ptr<EventChannel> m_eventQueue;
    AtomicValue<bool> m_isShutDown;
};
} // namespace smart_home


#endif //EVENT_DELIVER_HPP