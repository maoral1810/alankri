#include <algorithm>

#include "event_middlewere.hpp"
#include "event.hpp"
#include "common_utils.hpp"
#include "logger.hpp"

static const size_t NumOfChannles = 10; // FOR TEST NEED TO CHANGE

namespace smart_home
{

EventMiddlewere::EventMiddlewere(Shared_Ptr<IEventPuller> a_puller, 
                                Shared_Ptr<IDistribute> a_distributer, 
                                Shared_Ptr<ISearcher> a_subscribersSearcher
                                )
    : m_distributer(a_distributer)
    , m_puller(a_puller)
    , m_subscribersSearcher(a_subscribersSearcher)
{}

void EventMiddlewere::Run()
{
    Shared_Ptr<Event> event;
    SubscribersList list;
    Logger logger;
    
    while(true)
    {
        try {
            m_puller->PullEvent(event);
            logger.Log("Trace", "event was pull from bus", __func__);
            Event::EventTopic eventTopic(event->GetLocation(), event->GetType());
            list = m_subscribersSearcher->SerachSubscribers(eventTopic);
            m_distributer->DeliverEvent(list, event);
        }
        catch(const EventBusShutdownExp& ex)
        {
            break;
        }
    }
}

} // namespace smart_home
