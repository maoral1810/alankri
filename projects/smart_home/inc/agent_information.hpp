#ifndef AGENT_INFORMATION_HPP
#define AGENT_INFORMATION_HPP

#include <string>

#include "location.hpp"
#include "common_utils.hpp"

namespace smart_home {

class AgentInfo : private Uncopyable { 
public:
    typedef std::string AGENT_TYPE;
    
    AgentInfo(std::string a_payload, std::string a_log, Location a_location, AGENT_TYPE a_type, std::string a_configuration);
    // ~AgentInfo() = default;

    size_t GetID() const NOEXCEPTIONS;
    AGENT_TYPE GetType() const NOEXCEPTIONS;
    std::string GetConfiguration() const NOEXCEPTIONS;
    Location GetLocation() const NOEXCEPTIONS;
    std::string GetLog() const NOEXCEPTIONS;

private:
    static size_t m_id;
    size_t m_agentId;
    std::string m_payload;
    std::string m_log;
    Location m_location;
    AGENT_TYPE m_type;
    std::string m_configuration;
};

}// namespace smart_home
#endif // AGENT_INFORMATION_HPP
