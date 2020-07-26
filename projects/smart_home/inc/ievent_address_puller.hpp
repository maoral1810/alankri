#ifndef I_EVENT_ADDRESS_PULLER
#define I_EVENT_ADDRESS_PULLER

#include "common_utils.hpp"

namespace smart_home
{
class IEventAddressPuller : private Uncopyable
{
public:
    //IEventAddressPuller() = default; 
    virtual ~IEventAddressPuller();

    virtual void Pull(EventAddress& a_retval) = 0;
};

inline IEventAddressPuller::~IEventAddressPuller()
{}

} // namespace smart_home


#endif //I_EVENT_ADDRESS_PULLER