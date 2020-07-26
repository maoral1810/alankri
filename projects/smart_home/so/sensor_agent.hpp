#ifndef SENSOR_AGENT_HPP
#define SENSOR_AGENT_HPP

#include "agent_information.hpp"
#include "ievent_pusher.hpp"
#include "runnable.hpp"
#include "iagent.hpp"
#include "thread.hpp"

namespace smart_home
{
class SensorAgent : public Runnable, public IAgent {
public:
    SensorAgent(const Shared_Ptr<AgentInfo>& a_agentInfo);    
    virtual ~SensorAgent();
    
    virtual void Connect(const Shared_Ptr<IRegistrar>& a_registrar, const Shared_Ptr<IEventPusher>& a_pusher);
    void Disconnect();
    
private:
    virtual void Run();
    
private:
    Shared_Ptr<IEventPusher> m_eventPusher;
    Shared_Ptr<AgentInfo> m_agentInfo;
    AtomicValue<bool> m_isShutdown;   
    Shared_Ptr<Thread> m_thread;   
};
} // namespace smart_home

#endif // SENSOR_AGENT_HPP