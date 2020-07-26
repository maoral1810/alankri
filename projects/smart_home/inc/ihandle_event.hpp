#ifndef IHANDLE_EVENT_HPP
#define IHANDLE_EVENT_HPP

#include "event.hpp"
#include "common_utils.hpp"

namespace smart_home
{

class IHandleEvent
{
public:
    //IHandleEvent() = default;
    virtual ~IHandleEvent();

    virtual void HandleEvent(Shared_Ptr<Event>& a_event) = 0;
};

inline IHandleEvent::~IHandleEvent()
{}

}// smart_home

#endif //IHANDLE_EVENT_HPP