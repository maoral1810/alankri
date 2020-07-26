#ifndef I_AGENT_HPP
#define I_AGENT_HPP

#include "iregistrar.hpp"
#include "ievent_pusher.hpp"

namespace smart_home
{    
class IAgent
{
public:
    //IAgent() = default
    virtual ~IAgent() = 0;

    virtual void Connect(const Shared_Ptr<IRegistrar>& a_registrar, const Shared_Ptr<IEventPusher>& a_pusher) = 0; // TODO not const
    virtual void Disconnect() = 0;
};

inline IAgent::~IAgent()
{}
} // namespace smart_home


#endif //I_AGENT_HPP

