#ifndef __HASH_INL_H__
#define __HASH_INL_H__

#include "bucketContainer.h"

namespace experis
{
    template<class KEY, class VAL>
    Hash<KEY,VAL>::Hash(size_t a_size,HashFunction a_hashFunc, CompereFunction a_CmpFunc)
    :m_capacity(a_size),
    m_hashFunc(a_hashFunc),
    BucketContainer<KEY,VAL>(a_size, a_CmpFunc)
    {

    }

    template<class KEY, class VAL>
    bool Hash<KEY,VAL>::Add(const KEY& a_key, const VAL& a_val)
    {
        unsigned int hashIndex = m_hashFunc(a_key) % m_capacity;
        std::pair<KEY,VAL> data = std::make_pair(a_key,a_val);

        return BucketContainer<KEY,VAL>::Add(data, hashIndex);
    }

    template<class KEY, class VAL>
    BucketIter<std::pair<KEY,VAL> > Hash<KEY,VAL>::Find(const KEY& a_key)
    {
        unsigned int hashIndex = m_hashFunc(a_key) % m_capacity;

        return BucketContainer<KEY,VAL>::Find(a_key, hashIndex);
    }

    template<class KEY, class VAL>
    bool Hash<KEY,VAL>::Remove(const KEY& a_key)
    {
        unsigned int hashIndex = m_hashFunc(a_key) % m_capacity;

        return BucketContainer<KEY,VAL>::Remove(a_key, hashIndex);
    }

    template<class KEY, class VAL>
    size_t Hash<KEY,VAL>::Size()
    {
        size_t counter = 0;
        for(int i = 0; i < m_capacity; ++i)
        {
            counter += BucketContainer<KEY,VAL>::Size(i);
        }
        return counter;
    }

    template<class KEY, class VAL>
    BucketIter<std::pair<KEY,VAL> > Hash<KEY,VAL>::Begin()
    {
        return BucketContainer<KEY,VAL>::Begin();
    }

    template<class KEY, class VAL>
    BucketIter<std::pair<KEY,VAL> > Hash<KEY,VAL>::End()
    {
        return BucketContainer<KEY,VAL>::End();
    }

    template<class KEY, class VAL>
    size_t Hash<KEY,VAL>::ForEach(ActionFunction a_actionFunc ,void* a_contex)
    {
        return BucketContainer<KEY,VAL>::ForEach(a_actionFunc, a_contex);
    }
    
}// namespace experis

#endif //__HASH_INL_H__