#ifndef EVENT_HPP
#define EVENT_HPP

#include <cstddef> // size_t
#include <string>

#include "common_utils.hpp"
#include "location.hpp"
#include "time_stamp.hpp"

namespace smart_home
{

class Event : private Uncopyable {
public:

    typedef std::string EVENT_TYPE;

    typedef std::pair<Location,Event::EVENT_TYPE> EventTopic;
    Event(Location a_location, EVENT_TYPE a_type,  TimeStamp a_time ); /* Payload a_payload*/

    // ~Event() = default;
    
    size_t GetID() const NOEXCEPTIONS;
    Location GetLocation() const NOEXCEPTIONS;
    const EVENT_TYPE& GetType() const NOEXCEPTIONS;
    TimeStamp GetTime() const NOEXCEPTIONS;

    bool operator==(const Event& a_other) const NOEXCEPTIONS;
    bool operator!=(const Event& a_other) const NOEXCEPTIONS;

private:
    static size_t m_eventId;
    size_t m_id;
    Location m_location;
    EVENT_TYPE m_type;
    TimeStamp m_time; 
    //Payload m_payload;
};


/* class EventTopic {
public:
    EventTopic(const Location& a_location, const Event::EVENT_TYPE& a_type);
    //~EventTopic = default;

    Event::EVENT_TYPE GetEventType() const NOEXCEPTIONS;
    Location GetEventLocation() const NOEXCEPTIONS;

    bool operator==(const EventTopic& a_other) const NOEXCEPTIONS;

private:
    Location m_location;
    Event::EVENT_TYPE m_type;
}; */

} // namespace smart_home


#endif // EVENT_HPP
    /*  enum EVENT_TYPE {
        TEMPATURE = 0,
        SMOKE,
        CAPACITY,
        LIGTH,
        WATER,
        DOORS,
        LOCK,
        ZIGBEE //???
    }; */