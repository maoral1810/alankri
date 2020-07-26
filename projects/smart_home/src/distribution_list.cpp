#include <algorithm>    // for_each
#include <tr1/memory> 
#include <string>
#include <cassert> 

#include <iostream>

#include "distribution_list.hpp"
#include "distribution_list_details.hpp"
#include "common_utils.hpp"
#include "controller_agent.hpp"

namespace smart_home
{

void SafeDistributionList::Registrate(Shared_Ptr<IHandleEvent> a_subscriber, Event::EventTopic a_eventTopic)
{
    MutexGuard lock(m_mutex);
    ControllersMap::iterator controllerItr = m_controllerMap.find(a_subscriber);
    bool isConrollerExsist = m_controllerMap.end() != controllerItr;

    if(isConrollerExsist)
    {
        TopicsMap::iterator topicItr = m_topicsMap.find(controllerItr->second);
        SubscribersListItr subscribersItr = topicItr->second.FindSubscriber(a_subscriber);
        DistributionInfo subscriberCopy(*subscribersItr);
        topicItr->second.Remove(subscribersItr);
        m_controllerMap[a_subscriber].insert(a_eventTopic); 
        m_topicsMap[controllerItr->second].Push(subscriberCopy);
    }
    else
    {
        m_controllerMap[a_subscriber].insert(a_eventTopic);
        controllerItr = m_controllerMap.find(a_subscriber);
        m_topicsMap[controllerItr->second].Push(a_subscriber);
    }
}
SubscribersList SafeDistributionList::SerachSubscribers(const Event::EventTopic& a_eventTopic)
{
    MutexGuard lock(m_mutex);
    SubscribersList retval;

    for (size_t i = 0; i < POSSIBLE_KEYS; ++i)
    {
        Event::EventTopic currentTopic = GetSpacificKey(a_eventTopic, i);
        TopicsMap::iterator TopicMapItr = m_topicsMap.begin();
        while (TopicMapItr != m_topicsMap.end())
        {
            TopicsPermutition::const_iterator findRes = TopicMapItr->first.find(currentTopic);
            if(findRes != TopicMapItr->first.end())
            {
                std::for_each(TopicMapItr->second.Begin(), TopicMapItr->second.End(), AddSubscribers(retval));
            }
            ++TopicMapItr;
        }
    }

    return retval; 
}

void SafeDistributionList::UnRegistrate(Shared_Ptr<IHandleEvent> a_subscriber)
{
    TopicsPermutition& releventTopics =  m_controllerMap[a_subscriber];
    TopicsMap::iterator topicItr = m_topicsMap.find(releventTopics);
    SubscribersListItr subscribersItr = topicItr->second.FindSubscriber(a_subscriber);
    topicItr->second.Remove(subscribersItr);

    //std::string msg = "controller" 
}
//------------------------- private functions --------------------------
Event::EventTopic SafeDistributionList::GetSpacificKey(Event::EventTopic a_eventTopic, unsigned int a_spacificCase)
{
    Location newLocation();
    switch (a_spacificCase)
    {
        case 0:// (ROOM : FLOOR : TYPE)
            break;
        
        case 1: // (* : FLOOR : TYPE)  
            a_eventTopic.first = Location(ANY, a_eventTopic.first.GetFloor());
            break;
        
        case 2: //(* : * : TYPE)
            a_eventTopic.first = Location(ANY, ANY);   
            break;

        case 3: // (* : * : *)
            a_eventTopic.first = Location(ANY, ANY);
            a_eventTopic.second = ANY;  
            break;
        
        // we need this others keys ???
        
        case 4: //(ROOM: * : TYPE)
            a_eventTopic.first = Location(a_eventTopic.first.GetRoom(), ANY);
            break;
        
        case 5: // (ROOM: FLOOR : *)
            a_eventTopic.second = ANY;
            break;
        
        case 6: //(ROOM: * : *)
            a_eventTopic.first = Location(a_eventTopic.first.GetRoom(), ANY);
            a_eventTopic.second = ANY;
            break;
        
        case 7: //(* : FLOOR : *)
            a_eventTopic.first = Location(ANY, a_eventTopic.first.GetFloor());
            a_eventTopic.second = ANY;
            break;

        default:
            assert(!"cannot support spacific Case");
            break;
    }

    return a_eventTopic;
} 


} // namespace smart_home
