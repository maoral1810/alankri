#include "meter.h"
#include "squreMeter.h"
#include "km.h"

Meter Meter::operator-(const Meter& a_meter1)
{
    Meter res(m_val - a_meter1.GetMeter());
    return res;
}

Meter operator+(const Meter& a_meter1, const Meter& a_meter2)
{
    Meter res(a_meter1.GetMeter() + a_meter2.GetMeter());
    return res;
}

SqureMeter operator*(const Meter& a_meter1, const Meter& a_meter2)
{
    SqureMeter res(a_meter1.GetMeter() * a_meter2.GetMeter());
    return res;
} 

Meter operator*(const Meter& a_meter, double a_other)
{
    Meter res(a_meter.GetMeter() * a_other);
    return res; 
}

Meter operator*(double a_other, const Meter& a_meter)
{
    Meter res(a_meter.GetMeter() * a_other);
    return res; 
}

Meter::operator KM()
{
    KM res(m_val / MeterToKm);
    return res;
}


