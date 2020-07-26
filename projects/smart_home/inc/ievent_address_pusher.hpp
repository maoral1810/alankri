#ifndef I_EVENT_ADDRESS_PUSHER
#define I_EVENT_ADDRESS_PUSHER

#include "common_utils.hpp"

namespace smart_home
{
class IEventAddressPusher : private Uncopyable
{
public:
    //IEventAddressPusher() = default;
    virtual ~IEventAddressPusher();

    virtual void Push(EventAddress a_val) = 0;
};

inline IEventAddressPusher::~IEventAddressPusher()
{}

} // namespace smart_home


#endif //I_EVENT_ADDRESS_PUSHER