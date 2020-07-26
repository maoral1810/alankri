#ifndef DISTRIBUTION_LIST_HPP
#define DISTRIBUTION_LIST_HPP

#include <list>
#include <vector>
#include <tr1/memory>
#include <tr1/unordered_set>

#include "common_utils.hpp"
#include "mutex.hpp"
#include "event.hpp"
#include "isearch.hpp"
#include "iregistrar.hpp"
#include "subscribers_list.hpp"
#include "distribution_info.hpp"
#include "distribution_list_details.hpp"

namespace smart_home
{
class SafeDistributionList : public ISearcher, public IRegistrar
{
private:
    typedef std::string SubscribeKey;
    typedef Shared_Ptr<IHandleEvent> ControllerHandler;
    typedef std::tr1::unordered_set< Event::EventTopic, EventTopicHashFunc> TopicsPermutition;
    
    typedef std::tr1::unordered_map< ControllerHandler, TopicsPermutition, ControllerHashFunction> ControllersMap;
    typedef std::tr1::unordered_map< TopicsPermutition, SubscribersList , TopicsHashFunction, TopicsPermutitionCmpFunc> TopicsMap;

public:
    //SafeDistributionList() = default;
    //~SafeDistributionList() = default;

    virtual void Registrate(Shared_Ptr<IHandleEvent> a_subscriber, Event::EventTopic a_eventTopic);
    virtual SubscribersList SerachSubscribers(const Event::EventTopic& a_eventTopic);
    virtual void UnRegistrate(Shared_Ptr<IHandleEvent> a_subscriber);
    
private:
    Event::EventTopic GetSpacificKey(Event::EventTopic a_eventTopic, unsigned int a_spacificCase); 

private:
    ControllersMap m_controllerMap;
    TopicsMap m_topicsMap;

    Mutex m_mutex;
};

}// namespace smart_home

#endif // DISTRIBUTION_LIST_HPP