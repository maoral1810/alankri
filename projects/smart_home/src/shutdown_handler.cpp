#include "shutdown_handle.hpp"
#include "common_utils.hpp" // UNUSED

namespace smart_home
{

ShutdownHandler::~ShutdownHandler()
{}

void ShutdownHandler::HandleEvent(Shared_Ptr<Event>& a_event)
{
    //UNUSED(a_event);
    throw ShutdownExp();
}

} // namespace smart_home
