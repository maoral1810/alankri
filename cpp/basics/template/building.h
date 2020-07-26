#ifndef BUILDING_T_H
#define BUILDING_T_H

#include <vector>

template <class BID>

class Building_t
{
    public:
        Building_t();
        ~Building_t();
        Building_t(const Building_t& _building);
        Building_t& operator=(const Building_t& _building);

        void SetBuildingID(const BID& _id);
        const BID& GetBuildingID()const;

    private:
        BID m_id;
};

template <class BID>
Building_t<BID>::Building_t():m_id(){}

template <class BID>
Building_t<BID>::~Building_t(){}

template <class BID>
void Building_t<BID>::SetBuildingID(const BID& _id)
{
    m_id = _id;
}

template <class BID>
const BID& Building_t<BID>::GetBuildingID()const
{
    return m_id;
}

template <class BID>
Building_t<BID>::Building_t(const Building_t& _building)
{
    m_id = _building.m_id;
}

template <class BID>
Building_t<BID>& Building_t<BID>::operator=(const Building_t& _building)
{
/*     if(this != _building) */
    {
        m_id = _building.m_id;
    }

    return *this;
}

/*Building_t – 	template class. ID of buiding can be of ANY type :
		Example: IDs can be integers ( 1,3,5,7 2,4…) or even strings "A10" , "17Bet"…

		Functionality of class: setBuidingID and getBuildingID*/

#endif /* BUILDING_T_H*/

