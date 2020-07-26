#ifndef BUS_T_H__
#define BUS_T_H__

#include <stddef.h>
#include "car.h"

class Bus_t:public Car_t
{
    public:
        Bus_t();
        Bus_t(size_t _Seats);
        Bus_t(string line);
        Bus_t(size_t _Seats, string _line);
        ~Bus_t();
        Bus_t(const Bus_t& _bus); 
        Bus_t& operator=(Bus_t& _equalBus); // can copy only type,capcity,gear
        inline const string& GetLine()const{return m_line;}
        inline size_t GetSeats()const{return m_numOfSeats;}

    private:
        static size_t m_defualtSeats;
        static string m_defualtLine;
        size_t m_numOfSeats;
        string m_line;
};

#endif /* BUS_T_H__*/