#ifndef __METER_H__
#define __METER_H__
/* 
#include "squreMeter.h" */
/* #include "km.h" */
class SqureMeter;
class KM;
class Meter
{
public:
    Meter():m_val(0){;}
    explicit Meter(double _length):m_val(_length){;}
    //~Meter() = default
    //Meter(const Meter& _meter) = defualt
    //Meter& operator=(const Meter& a_other) = defualt 
    Meter operator-(const Meter& a_meter1);
    operator KM();
    
/* protected: */
    double GetMeter()const
    {return m_val;}
    void SetVal(double _val)
    {m_val = _val;}
    static const int MeterToKm = 1000;

private:
    double m_val;
};

Meter operator+(const Meter& a_meter1, const Meter& a_meter2);
Meter operator*(const Meter& a_meter, double a_other);
Meter operator*(double a_other, const Meter& a_meter);
SqureMeter operator*(const Meter& a_meter1, const Meter& a_meter2);
/* operator KM()const
{
}*/

#endif /*__METER_H__*/