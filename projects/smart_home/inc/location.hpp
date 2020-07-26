#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <cstddef> // size_t

#include <string>

#include "common_utils.hpp"

const std::string ANY = "*";

namespace smart_home
{
class Location {
public:
    Location(std::string a_room , std::string a_floor);
    //~Location() = default;
    //Location(const Location& a_other) = default;
    //Location& operator=(const Location& a_other) = default;

    std::string GetFloor() const NOEXCEPTIONS;
    std::string GetRoom() const NOEXCEPTIONS;

    bool operator==(const Location& a_other) const NOEXCEPTIONS;

private:
    std::string m_floor;
    std::string m_room;
};

} // namespace smart_home

#endif // LOCATION_HPP