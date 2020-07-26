#ifndef INITILIZER_HPP
#define INITILIZER_HPP

#include <string>
#include <vector>

#include "common_utils.hpp"
#include "event_middlewere.hpp"
#include "distributer.hpp"
#include "event_bus.hpp"
#include "distribution_list.hpp"
#include "sensor_agent.hpp"
#include "iagent.hpp"
#include "logger.hpp"

namespace smart_home
{

typedef std::vector<std::string> Tokens;
typedef std::vector<Shared_Ptr<IAgent> > AgentsCont;

class Initilizer :public Uncopyable
{
public:
    Initilizer(std::string a_fileName);
    ~Initilizer();

    AgentsCont& GetAgents() NOEXCEPTIONS;
    Shared_Ptr<SafeDistributionList>& GetDistributionList() NOEXCEPTIONS;
    Shared_Ptr<EventBus>& GetEventBus() NOEXCEPTIONS;
    Shared_Ptr<Distributer>& GetDistributer() NOEXCEPTIONS;
    Shared_Ptr<EventMiddlewere>& GetMiddlewere() NOEXCEPTIONS;
    ChannelsQueues& GetChannels() NOEXCEPTIONS;

private:
    void BuildChannels();
    void BuildSystem(const std::string& a_line);
    void BuildAgent(const std::string& a_line,  SoLibHandler& libHandler);
    void BuildAgentInfo(Shared_Ptr<AgentInfo>& info, Tokens a_tokens);

private:
    AgentsCont m_agents;
    smart_home::ChannelsQueues m_channels;
    Shared_Ptr<EventBus> m_eventBus;
    Shared_Ptr<SafeDistributionList> m_dl;
    Shared_Ptr<Distributer> m_distributer;
    Shared_Ptr<EventMiddlewere> m_middlewere;
};


} // namespace smart_home



#endif // INITILIZER_HPP