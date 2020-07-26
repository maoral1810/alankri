#include "bus.h"
#include "car.h"

size_t Bus_t::m_defualtSeats = 65;
string Bus_t::m_defualtLine("out of service");

Bus_t::Bus_t():m_numOfSeats(m_defualtSeats), m_line(m_defualtLine)
{
    SetName("Bus");
}

Bus_t::Bus_t(size_t _Seats): m_numOfSeats(_Seats), m_line(m_defualtLine)
{
    SetName("Bus");    
}

Bus_t::Bus_t(string _line): m_numOfSeats(m_defualtSeats), m_line(_line)
{
    SetName("Bus");    
}

Bus_t::Bus_t(size_t _Seats, string _line):m_numOfSeats(_Seats), m_line(_line)
{
    SetName("Bus");    
}

Bus_t::~Bus_t(){}

Bus_t::Bus_t(const Bus_t& _bus):Car_t(_bus)//??
{
    SetName(GetName());
    SetGear(GetGear());
    m_line = _bus.m_line;
    m_numOfSeats = _bus.m_numOfSeats;
}

Bus_t& Bus_t::operator=(Bus_t& _equalBus) // can copy only type,capcity,gear
{
    Car_t::operator=(_equalBus);
    m_line = _equalBus.m_line;
    m_numOfSeats = _equalBus.m_numOfSeats;

    return *this;

}        