#ifndef IDISTRIBUTE_HPP
#define IDISTRIBUTE_HPP

#include <list>

#include "ihandle_event.hpp"
#include "event.hpp"

namespace smart_home
{
class SubscribersList;
class IDistribute
{
public:
    //IDistribute() = default;
    virtual ~IDistribute();

    virtual void DeliverEvent(SubscribersList a_releventSubscribers, Shared_Ptr<Event> a_event) = 0; // will be run function
};

inline IDistribute::~IDistribute()
{}

}// smart_home

#endif //IDISTRIBUTE_HPP