/* #include "mesearUnit.h" */

class Meter;
class KM 
{
public:

    KM():m_val(0){;}
    explicit KM(double _length):m_val(_length){};
    //~KM() = default
    //KM(const KM& _km) = defualt;
    //KM& operator=(const KM& a_other): defualt 
    KM operator-(const KM& a_other);
    operator Meter();
    double GetKm()const{return m_val;}

private:
    double m_val;
    static const int kmToMeter = 1000;
};

KM operator+(const KM& a_km1, const KM& a_km2);
KM operator+(const KM& a_km, float a_other);
KM operator*(const KM& a_meter, float a_other);