#include <string>
#include <functional> // needed???
#include <tr1/unordered_set>

#include <iostream>

#include "distribution_info.hpp"
#include "distribution_list_details.hpp"

namespace smart_home
{
    typedef std::tr1::unordered_set< Event::EventTopic, EventTopicHashFunc>::const_iterator constTopicPerItr;
// ------------------------ TopicsHashFunction ---------------------------------
size_t TopicsHashFunction::operator()(const std::tr1::unordered_set< Event::EventTopic, EventTopicHashFunc>& a_topics) const NOEXCEPTIONS
{
    std::tr1::unordered_set<Event::EventTopic, EventTopicHashFunc>::const_iterator begin = a_topics.begin();
    size_t topicKey = 0;
    std::tr1::hash<std::string> hashFunc;
    
    // first- location , second - type
    while(begin != a_topics.end())
    {
        size_t roomKey = hashFunc(begin->first.GetRoom());
        size_t floorKey = hashFunc(begin->first.GetFloor());
        size_t typeKey = hashFunc(begin->second);

        topicKey ^= (roomKey + floorKey + typeKey);
        ++begin;
    }

    return topicKey;
}
// ------------------------ ControllerHashFunction ---------------------------------
size_t ControllerHashFunction::operator()(const Shared_Ptr<IHandleEvent>& a_controller) const NOEXCEPTIONS
{
    std::tr1::hash<IHandleEvent*> hashFunc;
    size_t controllerKey = hashFunc(a_controller.get());
    //std::cout<< "key = " << controllerKey << std::endl; //TODO
    return controllerKey;
}

//------------------IsEqualController--------------------

IsEqualController::IsEqualController(Shared_Ptr<IHandleEvent>& a_controller)
    : m_controller(a_controller)
{}

bool IsEqualController::operator() (DistributionInfo& a_controllerInfo) const NOEXCEPTIONS
{
    return ( a_controllerInfo.GetEventHandler() == m_controller);
}

// ------------------EventTopicHashFunc---------------------------------
size_t EventTopicHashFunc::operator()(const Event::EventTopic& a_eventTopic) const NOEXCEPTIONS
{
    size_t eventTopicKey = 0;
    std::tr1::hash<std::string> hashFunc;
    const Location& eventLocation = a_eventTopic.first;
    const Event::EVENT_TYPE& eventType = a_eventTopic.second;

    size_t roomKey = hashFunc(eventLocation.GetRoom()) >> 3;
    size_t floorKey = hashFunc(eventLocation.GetFloor()) << 3;
    size_t typeKey = hashFunc(eventType) >> 7;

    eventTopicKey = (roomKey + floorKey + typeKey);
    
    return eventTopicKey;
}

// ------------------AddSubscribers---------------------------------

AddSubscribers::AddSubscribers(SubscribersList& a_list)
        : m_list(a_list)
{}

void AddSubscribers::operator()(DistributionInfo& a_subscriber)
{
    m_list.Push(a_subscriber);
}

// ------------------ TopicsPermutitionCmpFunc ---------------------------------
bool TopicsPermutitionCmpFunc::operator()
    (const std::tr1::unordered_set< Event::EventTopic, EventTopicHashFunc>& a_topicPermutiotion,
     const std::tr1::unordered_set< Event::EventTopic, EventTopicHashFunc>& a_other) const NOEXCEPTIONS
{
    if(a_topicPermutiotion.size() != a_other.size())
    {
        return false;
    }

    constTopicPerItr otherBegin = a_other.begin();

    for(; otherBegin != a_other.end() ; ++otherBegin)
    {
        bool topicExsist = a_topicPermutiotion.find(*otherBegin) != a_topicPermutiotion.end();
        if(!topicExsist)
        {
            return false;
        }
    }
    
    // not need to check but iterators becuse the privious size check
    return (true); 
}

} // namespace smart_home
