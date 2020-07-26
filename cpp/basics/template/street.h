#ifndef STREET_T_H
#define STREET_T_H

#include <vector>
#include "building.h"
using namespace std;

template<class SID,class BID>
class Street_t
{
    public:
        Street_t();
        ~Street_t();
        Street_t(const Street_t& _st);
        Street_t& operator=(const Street_t& _st);

        void SetStreetID(SID _id);
        const SID& GetStreetID()const;
        void AddBuilding2Street(const Building_t<BID>& _building);
        const Building_t<BID>& GetBuilding(const BID& _buildingID)const throw(const char *);

    private:
        SID m_streetId;
        vector <Building_t<BID> > m_st;
};

template<class SID,class BID>
Street_t<SID,BID>::Street_t():m_streetId(){} 

template<class SID,class BID>
Street_t<SID,BID>::~Street_t(){}

template<class SID,class BID>
Street_t<SID,BID>::Street_t(const Street_t& _st)
{
    m_st = _st.m_st;
    m_streetId = _st.m_streetId;
}

template<class SID,class BID>
Street_t<SID,BID>& Street_t<SID,BID>:: operator=(const Street_t& _st)
{
    if(this != _st)
    {
        m_st = _st.m_st;
        m_streetId = _st.m_streetId;
    }

    return *this;
}

template<class SID,class BID>
void Street_t<SID,BID>::SetStreetID(SID _stID)
{
    m_streetId = _stID;
}

template<class SID,class BID>
const SID& Street_t<SID,BID>::GetStreetID()const
{
    return m_streetId;
}

template<class SID, class BID>
void Street_t<SID,BID>::AddBuilding2Street(const Building_t<BID>& _building)
{
    m_st.push_back(_building);
}

template<class SID, class BID>
const Building_t<BID>& Street_t<SID,BID>::GetBuilding(const BID& _buildingID)const throw(const char *)
{
    for(size_t i = 0; i < m_st.size() ; ++i)
    {
        if(_buildingID == m_st[i].GetBuildingID())
        {
            return m_st[i];
        }
    }
    
    if(m_st.size())
    {
        throw("building not find"); 
    }

    throw("street is empty"); 
    
}
/* Street_t – 	template class; is a container of buildings.
		ID of street can be of ANY type : strings "Herzl", or even integers as in New York – 42, 20..
		Functionality of class: setStreetID and getStreetID¸ AddBuilding2Street, getBuilding */

#endif /* STREET_T_H*/