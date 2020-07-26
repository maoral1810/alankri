#include "km.h"
#include "meter.h"

KM KM::operator-(const KM& a_other)
{
    KM res(m_val - a_other.GetKm());
    return res;
}

KM operator+(const KM& a_km1, const KM& a_km2)
{
    KM res(a_km1.GetKm() + a_km2.GetKm());
    return res;
}

KM operator+(const KM& a_km, float a_other)
{
    KM res(a_km.GetKm() + a_other);
    return res;
}

KM operator*(const KM& a_km, float a_other)
{
    KM res(a_km.GetKm() * a_other);
    return res;
}

KM::operator Meter()
{
    Meter res(m_val * kmToMeter);
    return res;
}