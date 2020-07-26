#ifndef __HOTEL_H__
#define __HOTEL_H__

#include <map>
#include <cstdio>
#include "squreMeter.h"

/* class SqureMeter; */

class Hotel
{
public:
    typedef unsigned int RoomNum;
    Hotel(size_t a_modulo, size_t a_numOfRooms);
    //~Hotel() = default;

    void AddRoom(RoomNum a_num, const SqureMeter& a_size);
    const SqureMeter GetRoomSize(RoomNum a_num){return m_rooms[a_num % m_numOfRooms];}
    
private:
    std::map<RoomNum,SqureMeter> m_rooms;
    size_t m_numOfRooms;
    size_t m_modulo;
    // class not copyable
    Hotel(const Hotel& a_other);
    Hotel& operator=(const Hotel& a_other);
};

#endif //__HOTEL_H__