#ifndef EVENT_MIDDLEWERE_HPP
#define EVENT_MIDDLEWERE_HPP

#include <string>
#include <vector>
#include <list>

#include "controller_agent.hpp"
#include "event_bus.hpp"
#include "distributer.hpp"
#include "ievent_puller.hpp"
#include "runnable.hpp"
#include "event_channel.hpp"
#include "idistribute.hpp"
#include "mutex.hpp"

namespace smart_home
{
class EventMiddlewere : public Runnable
{
public:
    EventMiddlewere(Shared_Ptr<IEventPuller> a_puller, 
                    Shared_Ptr<IDistribute> a_distributer, 
                    Shared_Ptr<ISearcher> a_subscribersSearcher
                    );
    //~EventMiddlewere() = default;

    virtual void Run();
    //void Shutdown();

private:
    Shared_Ptr<IDistribute> m_distributer;
    Shared_Ptr<IEventPuller> m_puller;
    Shared_Ptr<ISearcher> m_subscribersSearcher;
};
    
} // namespace smart_home

#endif //EVENT_MIDDLEWERE_HPP

//-------------------------------------


