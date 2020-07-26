#include <vector>
#include <list>
#include <algorithm>
#include <string>
#include <iostream> // cout for debug

#include "parcer.hpp"
#include "controller_agent.hpp"
#include "common_utils.hpp"
#include "distribution_list.hpp"
#include "thread.hpp"
#include "logger.hpp"
#include "location.hpp"
#include "time_stamp.hpp"

namespace smart_home
{

ControllerAgent::ControllerAgent(Shared_Ptr<AgentInfo> a_info)
    : m_info(a_info)
    , m_eventHandlerCounter(0)
{}

ControllerAgent::~ControllerAgent()
{}

bool ControllerAgent::operator==(const ControllerAgent& a_other)
{
    return (m_info == a_other.m_info);
}

void ControllerAgent::Connect(const Shared_Ptr<IRegistrar>& a_registrar, const Shared_Ptr<IEventPusher>& a_pusher)
{
    UNUSED(a_pusher);
    m_registrar = a_registrar;

    Tokens tokens;
    Parcer tokenizer;
    
    tokenizer.Parse(m_info->GetConfiguration(), Topic_Delimiter, tokens); // get only topics in configurtion

    for(size_t i = 0; i < tokens.size(); i += 3)
    {
        // Room:Floor:eventType
        Event::EventTopic curTopic(Location(tokens[i],tokens[i+1]), tokens[i+2]);
        m_topics.push_back(curTopic);
        Subscribe(curTopic);
    }
}

void ControllerAgent::Disconnect()
{
    Shared_Ptr<ControllerAgent> self = shared_from_this();
    m_registrar->UnRegistrate(self);
}

// ------------------- private functions ------------------------------
void ControllerAgent::Subscribe(const Event::EventTopic& a_topic)
{   
    Shared_Ptr<ControllerAgent> self = shared_from_this();
    m_registrar->Registrate(self, a_topic);
}

void ControllerAgent::HandleEvent(Shared_Ptr<Event>& a_event)
{
    // handle the event
    //IsEqualLocation compereFunc(a_event->GetLocation());

    //UNUSED(a_event); // for test
    //Logger log;
    
/*     Location eventLoc = a_event->GetLocation();
    TimeStamp eventTime = a_event->GetTime();

    std::string msg = "event_id:" + a_event->GetID();
    msg += " event type:" + a_event->GetType();
    msg += " event locaton" + eventLoc.GetRoom() + eventLoc.GetFloor(); 
    msg += " event time" + eventTime.GetTimeAsString();

    log.Log("trace", msg, __func__); */

/*     for(size_t i = 0; i < m_topics.size(); ++i)
    {
        if( ( compereFunc(m_topics[i].first) ) && ( m_topics[i].second == a_event->GetType() ) )
        {
            ++m_eventHandlerCounter;
        }
    } */
}

// -------------------- for tests ----------------------
size_t ControllerAgent::GetEventHandlerCounter() const NOEXCEPTIONS
{
    return m_eventHandlerCounter;
}

//--------------------------------------------------
IsEqualLocation::IsEqualLocation(const Location& a_location)
    : m_location(a_location)
{}

bool IsEqualLocation::operator()(const Location& a_other)
{
    if(m_location == a_other)
    {
        return true;
    }

    std::string otherRoom = a_other.GetRoom();
    std::string otherFloor = a_other.GetFloor();

    if((otherRoom == ANY && m_location.GetFloor() == otherFloor) || otherFloor == ANY) // TODO FOR ALL POSSIBLE KEYS
    {
        return true;
    }

    return false;
}
// -------------------------- so functions ---------------------------
extern "C"
{

Shared_Ptr<IAgent> CreateController(Shared_Ptr<AgentInfo>& a_info)
{
    return Shared_Ptr<IAgent>(new ControllerAgent(a_info));
}

} // extern "C"

} // namespace smart_home
