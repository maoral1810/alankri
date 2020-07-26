#ifndef SUBSCRIBERS_LIST_HPP
#define SUBSCRIBERS_LIST_HPP

#include <vector>

#include "ihandle_event.hpp"
#include "common_utils.hpp"
#include "distribution_info.hpp"

namespace smart_home
{
class SubscribersList
{
public:
    SubscribersList();
    //~SubscribersList() = default;
    // SubscribersList(const SubscribersList& a_other) = default
    // SubscribersList& operator=(const SubscribersList& a_other) = default

    void Push(const DistributionInfo& a_data);
    void Pop(DistributionInfo& a_retval);
    size_t Size() const NOEXCEPTIONS;
    void Remove(SubscribersListItr a_toRemove) NOEXCEPTIONS;

    SubscribersListItr FindSubscriber(const Shared_Ptr<IHandleEvent>& a_subscriber) NOEXCEPTIONS;
    SubscribersListItr Begin() NOEXCEPTIONS;
    SubscribersListItr End() NOEXCEPTIONS;

    void Print() const NOEXCEPTIONS;
    
    
private:
    typedef std::vector<DistributionInfo> List;
    List m_list;
};

} // namespace smart_home

#endif //SUBSCRIBERS_LIST_HPP