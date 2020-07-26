#ifndef DISTRIBUTION_LIST_DETAILTS_HPP
#define DISTRIBUTION_LIST_DETAILTS_HPP

#include <cstddef> // size_t

#include "event.hpp"
#include "location.hpp"
#include "ihandle_event.hpp"
#include "subscribers_list.hpp"

#include <functional> 

namespace smart_home
{

class ControllerHashFunction
{
public:
    //ControllerHashFunction();
    //~ControllerHashFunction() = default;

    size_t operator()(const Shared_Ptr<IHandleEvent>& a_controller) const NOEXCEPTIONS;
};

//--------------------EventTopic HashFunction + CmpFuction-----------------------
class EventTopicHashFunc {
public:
    //EventTopicHashFunc() = default;
    //~EventTopicHashFunc() = default;

    size_t operator()(const Event::EventTopic& a_eventTopic) const NOEXCEPTIONS;
};

// -------------- TopicMap Predicate --------------------
class IsEqualController 
{
public:
    IsEqualController(Shared_Ptr<IHandleEvent>& a_controller);
    //~IsEqualController() = default;

    bool operator() (DistributionInfo& a_controllerInfo) const NOEXCEPTIONS;
private:
    Shared_Ptr<IHandleEvent>& m_controller;
};

// -------------- AddSubscribers --------------------
class AddSubscribers
{
public:
    AddSubscribers(SubscribersList& a_list);
    //~AddSubscribers = default;
    
    void operator()(DistributionInfo& a_subscriber);

private:
    SubscribersList& m_list;
};

// -------------- TopicsHashFunction --------------------
class TopicsHashFunction
{
public:
    // TopicsHashFunction() = default;
    //~TopicsHashFunction() = default;

    size_t operator()(const std::tr1::unordered_set< Event::EventTopic, EventTopicHashFunc>& a_topics) const NOEXCEPTIONS;
};

class TopicsPermutitionCmpFunc
{
public:
    //EventTopicCmpFunc() = default;
    //~EventTopicCmpFunc() = default;

    bool operator()(const std::tr1::unordered_set< Event::EventTopic, EventTopicHashFunc>& a_topicPermutiotion,
                    const std::tr1::unordered_set< Event::EventTopic, EventTopicHashFunc>& a_other) const NOEXCEPTIONS;
};


} // namespace smart_home


#endif //DISTRIBUTION_LIST_DETAILTS_HPP