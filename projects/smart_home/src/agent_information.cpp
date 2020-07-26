#include "agent_information.hpp"

namespace smart_home {

size_t AgentInfo::m_id = 0;

AgentInfo:: AgentInfo(std::string a_payload, std::string a_log, Location a_location, AGENT_TYPE a_type, std::string a_configuration)
    : m_agentId(++m_id)
    , m_payload(a_payload)
    , m_log(a_log)
    , m_location(a_location)
    , m_type(a_type)
    , m_configuration(a_configuration)
{}

size_t AgentInfo::GetID() const NOEXCEPTIONS
{
    return m_id;
}

AgentInfo::AGENT_TYPE AgentInfo::GetType() const NOEXCEPTIONS
{
    return m_type;
}

std::string AgentInfo::GetConfiguration() const NOEXCEPTIONS
{
    return m_configuration;
}

Location AgentInfo::GetLocation() const NOEXCEPTIONS
{
    return m_location;
}

std::string AgentInfo::GetLog() const NOEXCEPTIONS
{
    return m_log;
}


} // namespace smart_home