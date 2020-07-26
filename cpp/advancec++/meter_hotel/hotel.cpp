#include "hotel.h"

Hotel::Hotel(size_t a_modulo, size_t a_numOfRooms):
    m_modulo(a_modulo), m_numOfRooms(a_numOfRooms)
{

}

void Hotel::AddRoom(RoomNum a_num, const SqureMeter& a_size)
{
    m_rooms[a_num] = a_size;
}

