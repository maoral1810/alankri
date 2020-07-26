#include "car.h"
#include <stddef.h> //size_t
#include <string.h> /* strcmp*/

size_t Car_t::m_defualCapcity = 1000;
size_t Car_t::m_gid = 0;
string Car_t:: m_defualtGear("automatic");

Car_t::Car_t():m_capacity(m_defualCapcity), m_id(++m_gid)
{
    m_gear = m_defualtGear;
}

Car_t::Car_t(size_t _capacity):m_capacity(_capacity), m_id(++m_gid)
{
    m_gear = m_defualtGear;
}

Car_t::Car_t(const Car_t& _car):m_id(++m_gid)
{
    m_capacity = _car.m_capacity;
    m_gear = _car.m_gear;
    m_name = _car.m_name;
}

Car_t& Car_t::operator=(Car_t& _equalCar)const{}

bool Car_t::operator<(Car_t& _toCompereCapcity)const
{
    return (m_capacity < _toCompereCapcity.m_capacity);
}

bool Car_t::IsSameName(const Car_t& _toCompereName)const
{
    return(m_name == _toCompereName.m_name);
}

size_t Car_t::SetDefaultCapcity(size_t _newCapcity)
{
    size_t oldCapcity = m_defualCapcity;
    m_defualCapcity = _newCapcity;
    return oldCapcity;
}

