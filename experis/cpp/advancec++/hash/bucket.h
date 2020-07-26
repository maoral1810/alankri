#ifndef __BUCKET_H__
#define __BUCKET_H__

#include <new>
#include <utility>
#include <iterator>
#include <vector>

#include "BucketItr.h"

namespace experis
{

template<class KEY,class VAL>
class Bucket
{
typedef std::pair<KEY,VAL> HashData;
typedef bool(*CompereFunc)(const KEY& a_key, const KEY& a_otherKey);

public:
    Bucket(CompereFunc a_cmpFunction):
    m_container(),
    m_cmpFunction(a_cmpFunction)
    {
        
    }
    //~Bucket(); 
    //Bucket(const Bucket& a_other);
    //Bucket& operator=(const Bucket& a_other);

    // API Function
    bool Add(const HashData& a_data);// throw bad_alloc
    
    bool Remove(const KEY& a_key);
    
    BucketIter<std::pair<KEY,VAL> > Find(const KEY& a_key);// throw string
    
    size_t Size()const{return m_container.size();}

    VAL Get(const KEY& a_key);
    BucketIter<std::pair<KEY,VAL> > Begin();
    BucketIter<std::pair<KEY,VAL> > End();

private:
    std::vector<HashData> m_container;
    CompereFunc m_cmpFunction;
};

#include "bucket_inl.h"

}//namespace experis

#endif //__BUCKET_H_