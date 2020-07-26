#include <string>

#include "event.hpp"
#include "common_utils.hpp"

namespace smart_home
{

size_t Event::m_eventId = 0;

Event::Event(Location a_location, EVENT_TYPE a_type,  TimeStamp a_time)  /* Payload a_payload*/
    : m_id(++m_eventId)
    , m_location(a_location)
    , m_type(a_type)
    , m_time(a_time)
{}

bool Event::operator==(const Event& a_other) const NOEXCEPTIONS
{
    return ( (m_id == a_other.GetID() ) &&
            (m_location ==  a_other.m_location) &&
            (m_time == a_other.m_time)&& 
            (m_type == a_other.m_type) );
}

bool Event::operator!=(const Event& a_other) const NOEXCEPTIONS
{
    return !(this->operator==(a_other));
}

size_t Event::GetID() const NOEXCEPTIONS
{
    return m_id;
}

Location Event::GetLocation() const NOEXCEPTIONS
{
    return m_location;
}

const Event::EVENT_TYPE& Event::GetType() const NOEXCEPTIONS
{
    return m_type;
}

TimeStamp Event::GetTime() const NOEXCEPTIONS
{
    return m_time;
}

// ----------------- event topic --------------------
/* 
EventTopic::EventTopic(const Location& a_location, const Event::EVENT_TYPE& a_type)
    : m_location(a_location)
    , m_type(a_type)
{}

Event::EVENT_TYPE EventTopic::GetEventType() const NOEXCEPTIONS
{
    return m_type;
}

Location EventTopic::GetEventLocation() const NOEXCEPTIONS
{
    return m_location;
}

bool EventTopic::operator==(const EventTopic& a_other) const NOEXCEPTIONS
{
    return ( (m_location == a_other.m_location) && (m_type == a_other.m_type) );
} */

} // namespace smart_home
