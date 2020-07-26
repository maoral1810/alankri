#include "location.hpp"
#include <string>

namespace smart_home
{
    
Location::Location(std::string a_room, std::string a_floor)
    : m_floor(a_floor)
    , m_room(a_room)
{}

bool Location::operator==(const Location& a_other) const NOEXCEPTIONS
{
    return ( (m_floor == a_other.m_floor) && (m_room == a_other.m_room) ); 
}

std::string Location::GetFloor() const NOEXCEPTIONS
{
    return m_floor;
}

std::string Location::GetRoom() const NOEXCEPTIONS
{
    return m_room;
}

} // namespace smart_home