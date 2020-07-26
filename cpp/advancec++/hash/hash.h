#ifndef __HASH_H__
#define __HASH_H__

#include <vector>
#include <string>
#include <utility> // make_pair
#include <iterator>
#include <stdlib.h> // ssize_t
#include "bucketContainer.h"

namespace experis
{
template<class KEY, class VAL>
class Hash : private BucketContainer<KEY,VAL>
{
typedef std::pair<KEY,VAL> HashData;
typedef bool(*ActionFunction)(VAL& a_val, void* _a_contex);
typedef unsigned int(*HashFunction)(const KEY& a_key);
typedef bool(*CompereFunction)(const KEY& a_key, const KEY& a_otherKey);
public:

    // constructor
    explicit Hash(size_t a_size,HashFunction a_hashFunc, CompereFunction a_CmpFunc);
    //~Hash() = defualt;
    //Hash(const Hash& a_other) = defualt;
    //Hash& operator=(const Hash& a_other) = defualt;

    // API Functions
    bool Add(const KEY& a_key, const VAL& a_val);
    BucketIter<HashData> Find(const KEY& a_key);
    bool Remove(const KEY& a_key);
    size_t ForEach(ActionFunction a_actionFunc ,void* a_contex);
    size_t Size();
    BucketIter<HashData> Begin();
    BucketIter<HashData> End();

    VAL Get(const KEY& a_key){return BucketContainer<KEY,VAL>::Get(a_key);} 

private:
    size_t m_capacity;
    HashFunction m_hashFunc;
};

}// namespace experis

#include "hash_inl.h"

#endif //#define __HASH_H__