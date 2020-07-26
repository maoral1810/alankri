#ifndef __BUCKET_CONTAINER_H__
#define __BUCKET_CONTAINER_H__

#include <vector>
#include "BucketItr.h"
#include "bucket.h"
namespace experis
{

template<class KEY,class VAL>
class BucketContainer
{
typedef std::pair<KEY,VAL> HashData;
typedef unsigned int(*HashFunction)(KEY a_key);
typedef bool(*CompereFunc)(const KEY& a_key, const KEY& a_otherKey);
typedef bool(*ActionFunction)(VAL& a_val, void* _a_contex);

public:    
    BucketContainer(size_t a_numOfElem, CompereFunc a_cmpFunc);
    //~BucketContainer() = defualt;
    //BucketContainer(const BucketContainer& a_other) = defualt;
    //BucketContainer& operator= (const BucketContainer& a_other) = defualt;

    //API Functions

    /* 
        Adds HashData to the bucket in a_index (if key in not uniqe, update VAL)
        throw bad_alloc if push to bucket fail   
    */
    bool Add(const HashData& a_data, unsigned int a_index);

    /* 
        Removes HashData from the bucket
        return true if remove sucsses
        return false if a_data not found
    */
    bool Remove(const KEY& a_key, unsigned int a_index);

    /*  
        Finds VAL in container.
        If VAL exists in bucket returns reference to it.
        If VAL doesn't exist or a_index is out of range, throws string??? exception.
    */
    BucketIter<std::pair<KEY,VAL> > Find(const KEY& a_key, unsigned int a_index);
    
    // return size of specific bucket(by index)
    size_t Size(unsigned int a_index){return m_container.at(a_index).Size();}

    //return itr to the first !empty bucket in container
    BucketIter<std::pair<KEY,VAL> > Begin();
    // return 1 element after the last elemet in container
    BucketIter<std::pair<KEY,VAL> > End();

    // activate Action Function on every element in container
    // return the num of element Action Function work on
    size_t ForEach(ActionFunction a_actionFunc ,void* a_contex);

    VAL Get(const KEY& a_key){return Bucket<KEY,VAL>::Get(a_key);}
    
private:
    std::vector<Bucket<KEY,VAL> > m_container;
    size_t m_capacity;
    CompereFunc m_cmpFunction;
};

#include "bucketContainer_inl.h"

}// namespace experies

#endif // __BUCKET_CONTAINER_H__