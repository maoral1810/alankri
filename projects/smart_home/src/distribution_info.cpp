#include "distribution_info.hpp"

namespace smart_home
{

DistributionInfo::ChannelID DistributionInfo::m_id = 0;

DistributionInfo::DistributionInfo(Shared_Ptr<IHandleEvent>& a_controller) NOEXCEPTIONS
    : m_channelNumber(m_id++ % NUM_OF_CHANNELS)
    , m_controller(a_controller)
{}

Shared_Ptr<IHandleEvent> DistributionInfo::GetEventHandler() const NOEXCEPTIONS
{
    return m_controller;
}

size_t DistributionInfo::GetChannelNumber() const NOEXCEPTIONS
{
    return m_channelNumber;
}

bool DistributionInfo::operator ==(const DistributionInfo& a_other)
{
    return ( ( m_channelNumber == a_other.GetChannelNumber() ) &&
             ( m_controller == a_other.GetEventHandler() ) ); 
}
    
} // namespace smart_home
