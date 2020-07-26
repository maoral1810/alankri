#include "sensor_agent.hpp"
#include "ievent_pusher.hpp"
#include "common_utils.hpp"
#include "thread.hpp"
#include "parcer.hpp"
#include "logger.hpp"

#include <iostream> // TODO COUT

namespace smart_home
{

SensorAgent::SensorAgent(const Shared_Ptr<AgentInfo>& a_agentInfo)
    : m_agentInfo(a_agentInfo)
    , m_isShutdown(false)
{}

SensorAgent::~SensorAgent()
{}

void SensorAgent::Run()
{
    Tokens tokens;
    Parcer Tokenizer;
    Tokenizer.Parse(m_agentInfo->GetConfiguration(), Event_Type_Delimiter, tokens);
    Event::EVENT_TYPE eventType(tokens[0]);
    Logger logger;

    while(!m_isShutdown.Get())
    {
        Shared_Ptr<Event> event( new Event( m_agentInfo->GetLocation(), eventType, TimeStamp() ) );
        try{
            m_eventPusher->PushEvent(event);
        }
        catch(const EventBusShutdownExp& exp)
        {
            m_isShutdown.Aquire();
        }
        catch(const std::exception& exp)
        {
            continue;
        }
        
        std::string msg = "event ";
        msg += IntToAssci(event->GetID()) + "was pushed to bus"; 
        logger.Log("Trace",msg, __func__);
    }
}

void SensorAgent::Connect(const Shared_Ptr<IRegistrar>& a_registrar, const Shared_Ptr<IEventPusher>& a_pusher)
{
    UNUSED(a_registrar);
    
    std::string msg = "sensor ";
    msg += IntToAssci(m_agentInfo->GetID()) + " connect";
    Logger logger;
    logger.Log("Trace", msg , __func__);
    
    m_eventPusher = a_pusher;
    m_thread = Shared_Ptr<Thread>(new Thread(this));
}

void SensorAgent::Disconnect()
{
    std::string msg = "sensor ";
    msg += IntToAssci(m_agentInfo->GetID()) + " Disconnect";
    Logger logger;
    logger.Log("Trace", msg , __func__);
    
    m_isShutdown.Aquire();
    m_thread->Join();
}

extern "C"
{

Shared_Ptr<IAgent> CreateSensor(Shared_Ptr<AgentInfo>& a_info)
{
    return Shared_Ptr<IAgent>(new SensorAgent(a_info));
}

} // extern "C"
 
} // namespace smart_home
