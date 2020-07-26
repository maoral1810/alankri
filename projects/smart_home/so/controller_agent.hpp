#ifndef CONTROLLER_AGENT_HPP
#define CONTROLLER_AGENT_HPP

#include <vector>

#include "common_utils.hpp"
#include "agent_information.hpp"
#include "event.hpp"
#include "iregistrar.hpp"
#include "common.hpp"
#include "distribution_list.hpp"
#include "iagent.hpp"

namespace smart_home
{

typedef std::vector<Event::EventTopic> Topics;

class ControllerAgent : public IHandleEvent, 
                        public std::tr1::enable_shared_from_this<ControllerAgent>,
                        public IAgent
{
public:
    ControllerAgent(Shared_Ptr<AgentInfo> a_info); // can get the IRegister to be a data memeber?
    virtual ~ControllerAgent();

    virtual void Connect(const Shared_Ptr<IRegistrar>& a_registrar, const Shared_Ptr<IEventPusher>& a_pusher);
    virtual void Disconnect();

    size_t GetEventHandlerCounter() const NOEXCEPTIONS; // for tests

    bool operator==(const ControllerAgent& a_other); 

private:
    virtual void Subscribe(const Event::EventTopic& a_topic);
    virtual void HandleEvent(Shared_Ptr<Event>& a_event);

private:
    Shared_Ptr<AgentInfo> m_info;
    size_t m_eventHandlerCounter; // for tests
    Topics m_topics;
    Shared_Ptr<IRegistrar> m_registrar;
}; 

class IsEqualLocation
{
public:
    IsEqualLocation(const Location& a_location);
    //~IsEqualLocation = default;

    bool operator()(const Location& a_other);

private:
    Location m_location;
};

} // namespace smart_home


#endif // CONTROLLER_AGENT_HPP