#ifndef DISTRIBUTER_HPP
#define DISTRIBUTER_HPP

#include <list>

#include "ihandle_event.hpp"
#include "event.hpp"
#include "idistribute.hpp"
#include "isearch.hpp"
#include "subscribers_list.hpp"

namespace smart_home
{

class Distributer : public IDistribute
{
public:
    Distributer(ChannelPushers& a_channelsQueue);
    virtual ~Distributer();

    virtual void DeliverEvent(SubscribersList a_releventSubscribers, Shared_Ptr<Event> a_event);
    void Shutdown();
private:
    ChannelPushers& m_channelsQueue;
};

}// smart_home

#endif //DISTRIBUTER_HPP