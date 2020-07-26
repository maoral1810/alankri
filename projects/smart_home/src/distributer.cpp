#include "distributer.hpp"
#include "ievent_address_pusher.hpp"
#include "distribution_info.hpp"
#include "event_channel.hpp"
#include "shutdown_handle.hpp"
#include "logger.hpp"

namespace smart_home
{

Distributer::Distributer(ChannelPushers& a_channelsQueue)
    : m_channelsQueue(a_channelsQueue)
{}

Distributer::~Distributer()
{}

void Distributer::DeliverEvent(SubscribersList a_releventSubscribers, Shared_Ptr<Event> a_event)
{
    SubscribersListItr begin = a_releventSubscribers.Begin();
    Logger logger;
    while(begin != a_releventSubscribers.End())
    {
        // channel number, ieventHandler
        EventAddress toDeliver(a_event, begin->GetEventHandler());
        try{
            m_channelsQueue[begin->GetChannelNumber()]->Push(toDeliver);
        }
        catch(const EventChannelShutdownExp& ex)
        {
            break;
        }
        catch(...)
        {
            ++begin;
            continue;
        }
        
        ++begin;
    }
    
    std::string msg = "Event #";
    msg += IntToAssci(a_event->GetID()) + "Deliverd";
    logger.Log("Trace", msg, __func__);
}

void Distributer::Shutdown()
{
    EventAddress poisionApple(Shared_Ptr<Event>() , Shared_Ptr<ShutdownHandler>(new ShutdownHandler()));

    for(size_t i = 0 ; i < m_channelsQueue.size(); ++i)
    {
        m_channelsQueue[i]->Push(poisionApple);
    }
}

}// namespace smart_home