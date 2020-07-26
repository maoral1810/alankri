#ifndef __SQURE_METER_H__
#define __SQURE_METER_H__

#include "meter.h"
class Meter;
class SqureMeter
{
public:
    SqureMeter():m_val(0){;}
    explicit SqureMeter(double _val):m_val(_val){;}
    //~SqureMeter() = defualt
    //SqureMeter(const SqureMeter& _meter) = defualt;
    //SqureMeter& operator=(const SqureMeter& _meter) = defualt;
    Meter operator/(const Meter& a_meter);
    SqureMeter operator-(const SqureMeter& a_SqrMeter);
/* protected: */
    double GetSqureMeter()const{return m_val;}
/*     void SetSqureMeter(double _val)const{return m_val = _val;} */

private:
    double m_val;
};

SqureMeter operator+(const SqureMeter& a_SqrMeter1, const SqureMeter& a_SqrMeter2);
SqureMeter operator*(const SqureMeter& a_SqrMeter, double a_val);
SqureMeter operator/(const SqureMeter& a_SqrMeter, double a_val);

#endif //__SQURE_METER_H__


