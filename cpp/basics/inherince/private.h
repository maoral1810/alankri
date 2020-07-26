#ifndef PRIVATE_T_H__
#define PRIVATE_T_H__

#include "car.h"

class Private_t:public Car_t
{
    public:
        Private_t();
        ~Private_t();
        Private_t(unsigned int _speed);
        Private_t(Private_t& _private);
        Private_t& operator=(Private_t& _equalPrivate); // can copy only type,capcity,gear
        unsigned int GetSpeed();
        void Accelerate();
        void reduceSpeed();
        
    private:
        unsigned int m_speed;
};

#endif /* PRIVATE_T_H__*/