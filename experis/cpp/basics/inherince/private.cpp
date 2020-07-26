#include "private.h"

Private_t::Private_t()
{
    m_speed = 0;
    SetName("Private");
}

Private_t::Private_t(unsigned int _speed)
{
    m_speed = _speed;
    SetName("Private");
}

Private_t::~Private_t(){}


Private_t::Private_t(Private_t& _private)
{
    _private.m_speed = m_speed;
}

Private_t& Private_t::operator=(Private_t& _equalPrivate)
{
    Car_t::operator=(_equalPrivate);
    m_speed = _equalPrivate.m_speed;
    return *this;
}

unsigned int Private_t::GetSpeed()
{
    return m_speed;
}

void Private_t::Accelerate()
{
    m_speed += 10;
}

void Private_t::reduceSpeed()
{
    if(m_speed >= 10)
    {
        m_speed -= 10;    
    }
}