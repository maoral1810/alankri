#ifndef ISEARCHER_HPP
#define ISEARCHER_HPP

#include <list>

#include "ihandle_event.hpp"
#include "event.hpp"
#include "subscribers_list.hpp"
#include "location.hpp"

namespace smart_home
{

class ISearcher
{
public:
    //ISearcher() = default;
    virtual ~ISearcher();

    virtual SubscribersList SerachSubscribers(const Event::EventTopic& a_eventTopic) = 0;
};

inline ISearcher::~ISearcher()
{}

}// smart_home

#endif //ISEARCHER_HPP