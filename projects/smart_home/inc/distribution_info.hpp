#ifndef DISTRIBUTION_INFO_HPP
#define DISTRIBUTION_INFO_HPP

#include <cstddef> // size_t


#include "common_utils.hpp"

namespace smart_home
{

class IHandleEvent;
class DistributionInfo
{
public:
    typedef size_t ChannelID;
public:
    DistributionInfo(Shared_Ptr<IHandleEvent>& a_controller) NOEXCEPTIONS;
    //~DistributionInfo() = default;

    Shared_Ptr<IHandleEvent> GetEventHandler() const NOEXCEPTIONS;
    size_t GetChannelNumber() const NOEXCEPTIONS;
    bool operator ==(const DistributionInfo& a_other);
    
private:
    static ChannelID m_id;
    ChannelID m_channelNumber;
    Shared_Ptr<IHandleEvent> m_controller;
};

} // namespace smart_home

#endif //DISTRIBUTION_INFO_HPP