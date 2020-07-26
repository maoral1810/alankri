#ifndef CITY_T_H
#define CITY_T_H

#include <vector>
#include "street.h"
using namespace std;

template<class CID,class SID,class BID>
/* City_t -	template class;  is container of streets 
		ID of City can be of ANY type : strings "Herzl", or any another type
		Functionality of class: SetCityID and GetCityID¸ AddStreet, getStreet
 */
class City_t
{
    public:
        City_t();
        ~City_t();
        City_t(const City_t& _city);
        City_t& operator=(const City_t& _city);

        void SetCityID(CID _id);
        const CID& GetCityID()const;
        void AddStreet(const Street_t<SID,BID>& _Street);
        const Street_t<SID,BID>& GetStreet(SID _StreetID)const throw(const char *);

    private:
        CID m_CityId;
        vector <Street_t<SID,BID> > m_city;
};

template<class CID,class SID,class BID>
City_t<CID,SID,BID>::City_t(){}

template<class CID,class SID,class BID>
City_t<CID,SID,BID>::~City_t(){}

template<class CID,class SID,class BID>
City_t<CID,SID,BID>::City_t(const City_t<CID,SID,BID>& _city)
{
    m_city = _city.m_city;
    m_CityId = _city.m_CityId;
}

template<class CID,class SID,class BID>
City_t<CID,SID,BID>& City_t<CID,SID,BID>::operator=(const City_t<CID,SID,BID>& _city)
{
    if(*this != _city)
    {
        m_city = _city.m_city;
        m_CityId = _city.m_CityId;
    }

    return *this;
}

template<class CID,class SID,class BID>
void City_t<CID,SID,BID>::SetCityID(CID _id)
{
    m_CityId = _id;
}

template<class CID,class SID,class BID>
const CID& City_t<CID,SID,BID>::GetCityID()const
{
    return m_CityId;
}

template<class CID,class SID,class BID>
void City_t<CID,SID,BID>::AddStreet(const Street_t<SID,BID>& _Street)
{
    m_city.push_back(_Street);
}

template<class CID,class SID,class BID>
const Street_t<SID,BID>& City_t<CID,SID,BID>::GetStreet(SID _StreetID)const throw(const char *)
{
    size_t citysize = m_city.size();

    for(size_t i = 0; i < citysize ; ++i)
    {
        if(_StreetID == m_city[i].GetStreetID())
        {
            return m_city[i];
        }
    }
    throw ("street not find"); 
/*     return 0; */
}


#endif /* CITY_T_H */