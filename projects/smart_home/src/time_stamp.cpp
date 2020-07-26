#include <ctime> // mktime , tm, time_t

#include "time_stamp.hpp"
#include "common_utils.hpp"

namespace smart_home
{

TimeStamp::TimeStamp()
{
    InitilizeCurrentTime();
}

void TimeStamp::InitilizeCurrentTime()
{
    time_t rawtime;
    
    time(&rawtime);
    m_timeInfo = *localtime( &rawtime );
    
    mktime(&m_timeInfo);
}

int TimeStamp::GetSeconds() const NOEXCEPTIONS
{
    return m_timeInfo.tm_sec;
}

int TimeStamp::GetMinutes() const NOEXCEPTIONS
{
    return m_timeInfo.tm_min;
}

int TimeStamp::GetHours() const NOEXCEPTIONS
{
    return m_timeInfo.tm_hour;
}

std::string TimeStamp::GetTimeAsString() const NOEXCEPTIONS
{
    std::string time;
    time += IntToAssci(m_timeInfo.tm_hour) + ":";
    time += IntToAssci(m_timeInfo.tm_min) + ":";
    time += IntToAssci(m_timeInfo.tm_sec);

    return time;
}

bool TimeStamp::operator==(const TimeStamp& a_other) const NOEXCEPTIONS
{
    return ( (m_timeInfo.tm_hour == a_other.m_timeInfo.tm_hour) &&
            (m_timeInfo.tm_min == a_other.m_timeInfo.tm_min) &&
            (m_timeInfo.tm_sec == a_other.m_timeInfo.tm_sec) );
}


} // namespace smart_home