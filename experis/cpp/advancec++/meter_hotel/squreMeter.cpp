#include "squreMeter.h"

SqureMeter operator+(const SqureMeter& a_SqrMeter1, const SqureMeter& a_SqrMeter2)
{
    SqureMeter res(a_SqrMeter1.GetSqureMeter() + a_SqrMeter2.GetSqureMeter());
    return res;
}

SqureMeter operator*(const SqureMeter& a_SqrMeter, double a_val)
{
    SqureMeter res(a_SqrMeter.GetSqureMeter() * a_val);
    return res;
}

SqureMeter operator/(const SqureMeter& a_SqrMeter, double a_val)
{
    SqureMeter res(a_SqrMeter.GetSqureMeter() / a_val);
    return res;
}

Meter SqureMeter::operator/(const Meter& a_meter)
{
    Meter res(m_val / a_meter.GetMeter());
    return res;
}

SqureMeter SqureMeter::operator-(const SqureMeter& a_SqrMeter)
{
    SqureMeter res(m_val - a_SqrMeter.GetSqureMeter());
    return res;
}

