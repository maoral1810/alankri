#ifndef __BUCKET_ITERATOR_H__
#define __BUCKET_ITERATOR_H__

#include <iterator>
#include <vector>

namespace experis
{

template<class DATA>
class BucketIter
{
    typedef typename std::vector<DATA>::iterator ITERATOR;
public:
    BucketIter(ITERATOR a_iter)
    : m_iter(a_iter)
    {

    }
    //~iterator()= defualt;
    //iterator(const iterator& a_other)= defualt;
    //iterator& operator=(const iterator& a_other) = defualt;

    BucketIter& operator++(){++m_iter;return *this;}
    DATA& operator*(){return *m_iter;}
    bool operator==(BucketIter a_iter){return m_iter == a_iter.m_iter;}
    bool operator!=(BucketIter a_iter){return !(m_iter == a_iter.m_iter);}
    
private:
    ITERATOR m_iter;
};

}//namespace experis

#endif //__BUCKET_ITERATOR_H__