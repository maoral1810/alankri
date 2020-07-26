#ifndef SHUTDOWN_HANDLE_HPP
#define SHUTDOWN_HANDLE_HPP

#include "ihandle_event.hpp"

namespace smart_home
{
class ShutdownHandler : public IHandleEvent
{
public:
    //ShutdownHandler() = default;
    virtual ~ShutdownHandler();

    virtual void HandleEvent(Shared_Ptr<Event>& a_event);
};
} // namespace smart_home

#endif //SHUTDOWN_HANDLE_HPP