#ifndef __BUCKET_INL_H__
#define __BUCKET_INL_H__

template<class KEY,class VAL>
bool Bucket<KEY,VAL>::Add(const HashData& a_data)
{ 
    size_t i = 0;
    typename std::vector<HashData>::iterator itr = m_container.begin();
    while(itr != m_container.end())
    {
        if(m_cmpFunction((*itr).first, a_data.first))
        {
            (*itr).second = a_data.second;
            return false;
        }

        ++itr;
    }
    try
    {
        m_container.insert(itr, a_data);
    }
    catch(const std::bad_alloc& exp)
    {
        //throw();// what to throw
    }

    return true;
}

template<class KEY,class VAL>
bool Bucket<KEY,VAL>::Remove(const KEY& a_key)
{
    typename std::vector<HashData>::iterator itr = m_container.begin();
    
    while(itr != m_container.end())
    {
        if(m_cmpFunction((*itr).first, a_key))
        {
            m_container.erase(itr);
            return true;
        }
        ++itr;
    }

    return false;
}

template<class KEY,class VAL>
BucketIter<std::pair<KEY,VAL> > Bucket<KEY,VAL>::Find(const KEY& a_key)
{
    BucketIter<HashData> iter = Begin();
    while (iter != End())
    {
        if(m_cmpFunction((*iter).first, a_key))
        {
            break;
        }
        ++iter;
    }
    return iter;
}

template<class KEY,class VAL>
BucketIter<std::pair<KEY,VAL> > Bucket<KEY,VAL>::Begin()
{
    return BucketIter<std::pair<KEY,VAL> >(m_container.begin());
}

template<class KEY,class VAL>
BucketIter<std::pair<KEY,VAL> > Bucket<KEY,VAL>::End()
{
    return BucketIter<std::pair<KEY,VAL> >(m_container.end());
}

template<class KEY,class VAL>
VAL Bucket<KEY,VAL>:: Get(const KEY& a_key)
{
    BucketIter<std::pair<KEY,VAL> > findRes = Find(a_key);
    if(findRes != End())
    {
        return (*findRes).second;
    }
    
   throw(std::out_of_range("data not found"));
}

#endif //__BUCKET_INL_H__