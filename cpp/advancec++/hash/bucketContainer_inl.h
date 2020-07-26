#ifndef __BUCKET_CONTAINER_INL_H__
#define __BUCKET_CONTAINER_INL_H__

template<class KEY,class VAL>
BucketContainer<KEY,VAL>::BucketContainer
(size_t a_capacity, CompereFunc a_cmpFunc):
    m_capacity(a_capacity),
    m_cmpFunction(a_cmpFunc),
    m_container(a_capacity, Bucket<KEY,VAL>(a_cmpFunc))
{

}

template<class KEY,class VAL>
bool BucketContainer<KEY,VAL>::Add(const HashData& a_data, unsigned int a_index)
{
    // call to add of bucket
    return m_container.at(a_index).Add(a_data);
}

template<class KEY,class VAL>
bool BucketContainer<KEY,VAL>::Remove(const KEY& a_key, unsigned int a_index)
{
    //call bucket remove
    return m_container.at(a_index).Remove(a_key); //throws exception
}

template<class KEY,class VAL>
BucketIter<std::pair<KEY,VAL> > BucketContainer<KEY,VAL>:: Find
(const KEY& a_key, unsigned int a_index)
{
    return BucketContainer<KEY,VAL>::m_container.at(a_index).Find(a_key);
}

template<class KEY,class VAL>
BucketIter<std::pair<KEY,VAL> > BucketContainer<KEY,VAL>::Begin()
{
    size_t i = 0;
    for(; i < m_capacity; ++i)
    {
        if(m_container.at(i).Begin() != m_container.at(i).End())
        {
            return m_container.at(i).Begin();
        }
    }

    return m_container.at(i -1).End();
}

template<class KEY,class VAL>
BucketIter<std::pair<KEY,VAL> > BucketContainer<KEY,VAL>::End()
{
    return  m_container.at(m_capacity - 1).End();
}

template<class KEY,class VAL>
size_t BucketContainer<KEY,VAL>::ForEach(ActionFunction a_actionFunc ,void* a_contex)
{
    size_t counter = 0;

    for(int i = 0; i < m_capacity; ++i)
    {
        BucketIter<std::pair<KEY,VAL> > iter = m_container.at(i).Begin();
        while (iter != m_container.at(i).End())
        {
            if(!a_actionFunc((*iter).second, a_contex))
            {
                return counter;
            }

            ++counter;
            ++iter;
        }
    }

    return counter;
}
#endif //__BUCKET_CONTAINER_INL_H__