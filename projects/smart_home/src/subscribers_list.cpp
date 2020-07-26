#include <algorithm> // swap
#include <utility>   // swap

#include <iostream> // to delete

#include "subscribers_list.hpp"
#include "common_utils.hpp"
#include "distribution_info.hpp"

namespace smart_home
{
SubscribersList::SubscribersList()
    : m_list()
{}

void SubscribersList::Push(const DistributionInfo& a_data)
{
    m_list.push_back(a_data);
}

void SubscribersList::Pop(DistributionInfo& a_retval)
{
    std::swap(*(m_list.rbegin()), *(m_list.begin()));

    a_retval = *(m_list.rbegin());
    m_list.pop_back();
}

size_t SubscribersList::Size() const NOEXCEPTIONS
{
    return m_list.size();
}

void SubscribersList::Remove(SubscribersListItr a_toRemove) NOEXCEPTIONS
{
    m_list.erase(a_toRemove);
}

SubscribersListItr SubscribersList::Begin() NOEXCEPTIONS
{
    return m_list.begin();
}

SubscribersListItr SubscribersList::End() NOEXCEPTIONS
{
    return m_list.end();
}

SubscribersListItr SubscribersList::FindSubscriber(const Shared_Ptr<IHandleEvent>& a_subscriber) NOEXCEPTIONS
{
    SubscribersListItr begin = Begin();

    while (begin != End())
    {
        if(begin->GetEventHandler() == a_subscriber)
        {
            break;
        }
        
        ++begin;
    }

    return begin;
}

void SubscribersList::Print() const NOEXCEPTIONS
{
    List::const_iterator begin = m_list.begin();

    while(begin != m_list.end())
    {
        std::cout << "channel: "<< begin->GetChannelNumber() << " handler:" << begin->GetEventHandler() << std::endl;
        
        ++begin;
    }
}

} // namespace smart_home
