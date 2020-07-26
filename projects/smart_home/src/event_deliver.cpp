#include "event_deliver.hpp"
#include "ihandle_event.hpp"
#include "event_channel.hpp"
#include "common_utils.hpp"

namespace smart_home
{

EventDeliver::EventDeliver(Shared_Ptr<EventChannel> a_eventQueue) // TODO IPULLER
    : m_eventQueue(a_eventQueue)
    , m_isShutDown(false)
{}

void EventDeliver::Run()
{
    while (!m_isShutDown.Get())
    {
        EventAddress a_eventInfo;
        try{
            m_eventQueue->Pull(a_eventInfo);
            a_eventInfo.second->HandleEvent(a_eventInfo.first);
        }
        catch(const ShutdownExp& ex)
        {
            m_isShutDown.Aquire();
        }
        catch(const std::exception& ex)
        {
            continue;
        }
    }
}
    
void EventDeliver::ShutDown() NOEXCEPTIONS
{
    m_isShutDown.Aquire();
}

} // namespace smart_home
