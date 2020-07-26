#ifndef __CONTAINER_ITERATOR_H__
#define __CONTAINER_ITERATOR_H__

#include <iterator>
#include <vector>
#include "BucketItr.h"
#include "bucket.h"


namespace experis{

template<class DATA>
class ContainerIter{
        typedef BucketIter ITERATOR;
public:
    ContainerIter(ITERATOR a_iter)
    : m_iter(a_iter)
    {

    }
    //~ContainerIter()= defualt;
    //ContainerIter(const ContainerIter& a_other)= defualt;
    //ContainerIter& operator=(const ContainerIter& a_other) = defualt;

    ContainerIter& operator++(){
        ++m_iter;
        if(m_iter == Bucket<KEY,VAL>::End())
        {
            // forward to next bucket and return the begin of the bucket

        }
        return *this;
        }
    DATA& operator*(){return *m_iter;}
    bool operator==(BucketIter a_iter){return m_iter == a_iter.m_iter;}
    bool operator!=(BucketIter a_iter){return !(m_iter == a_iter.m_iter);}
};


#endif //__CONTAINER_ITERATOR_H__