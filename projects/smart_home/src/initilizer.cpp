#include <iostream> // ifstream
#include <fstream>  // ifstream
#include <string>
#include <sstream>
#include <dlfcn.h>

#include <cstdlib>  // atoi
#include <cassert>

#include "initilizer.hpp"
#include "event_channel.hpp"
#include "distribution_list.hpp"
#include "event_middlewere.hpp"
#include "event_bus.hpp"
#include "parcer.hpp"
#include "logger.hpp"

namespace smart_home
{

typedef Shared_Ptr<IAgent> (*CreateAgent)(Shared_Ptr<AgentInfo>& a_info);

Initilizer::Initilizer(std::string a_fileName)
{
    std::string line;
    std::ifstream file(a_fileName.c_str());
    Logger logger;
    SoLibHandler libHandler("./libAgent.so");

    if(file.is_open())
    {
        // get the first line for configurate all system without the agents
        getline (file, line);
        BuildSystem(line);

        while (getline (file, line)) // initilize all agents
        {
            BuildAgent(line, libHandler);
        }

        file.close();   
    }
    else
    {
        logger.Log("Error", "unable to open file",__func__);
        assert(!"unable to open file");
    }
}

Initilizer::~Initilizer()
{}

AgentsCont& Initilizer::GetAgents() NOEXCEPTIONS
{
    return m_agents;
}

Shared_Ptr<SafeDistributionList>& Initilizer::GetDistributionList() NOEXCEPTIONS
{
    return m_dl;
}

Shared_Ptr<EventBus>& Initilizer::GetEventBus() NOEXCEPTIONS
{
    return m_eventBus;
}

Shared_Ptr<Distributer>& Initilizer::GetDistributer() NOEXCEPTIONS
{
    return m_distributer;
}

Shared_Ptr<EventMiddlewere>& Initilizer::GetMiddlewere() NOEXCEPTIONS
{
    return m_middlewere;
}

ChannelsQueues& Initilizer::GetChannels() NOEXCEPTIONS
{
    return m_channels;
}

void Initilizer::BuildSystem(const std::string& a_line)
{
    // line = "eventBusCapacity"
    BuildChannels();
    m_eventBus = Shared_Ptr<EventBus>(new EventBus(atoi(a_line.c_str())));
    m_dl = Shared_Ptr<SafeDistributionList>(new SafeDistributionList);
    m_distributer = Shared_Ptr<Distributer>(new Distributer(m_channels));
    m_middlewere = Shared_Ptr<EventMiddlewere>(new EventMiddlewere(m_eventBus, m_distributer, m_dl));
}

void Initilizer::BuildAgent(const std::string& a_line,  SoLibHandler& libHandler)
{
    Shared_Ptr<AgentInfo> info;
    Tokens tokens;
    Parcer tokenizer;

    tokenizer.Parse(a_line, Info_Delimiter, tokens);
    BuildAgentInfo(info, tokens);
    
    std::string funcName = (tokens[0] == "controller") ? "CreateController" : "CreateSensor";

    CreateAgent createFunc = libHandler.getFunction<CreateAgent>(funcName.c_str()); 
    Shared_Ptr<IAgent> agent = createFunc(info);
    m_agents.push_back(agent);
}

void Initilizer::BuildAgentInfo(Shared_Ptr<AgentInfo>& info, Tokens a_tokens)
{
    // line = agentType: location : payload : log : configurtion
    size_t i = 1;
    Location loc(a_tokens[i],a_tokens[i+1]);
    info = Shared_Ptr<AgentInfo>(new AgentInfo(a_tokens[i + 2],a_tokens[i+3], loc, a_tokens[i+4], a_tokens[i+5]));
}

void Initilizer::BuildChannels()
{
    m_channels.reserve(smart_home::NUM_OF_CHANNELS);

    for(size_t i = 0; i < smart_home::NUM_OF_CHANNELS; ++i)
    {
        m_channels.push_back(Shared_Ptr<EventChannel>(new EventChannel()));
    }
}


} // namespace smart_home
