#ifndef BITSET_REFERANCE_HPP_
#define BITSET_REFERANCE_HPP_

#include "details.hpp"

namespace experis { 

class BitsetReference {
public:
    explicit BitsetReference(details::BITSET_TYPE* a_index, unsigned char a_offset);
    //~BitsetReference() = defualt;
    //BitsetReference(const BitsetReference& a_other) = defualt;
    //BitsetReference& operator=(const BitsetReference& a_other) = defualt;
    BitsetReference& operator=(bool a_val);
    details::BITSET_TYPE* GetIndexVal() const { return m_index; }
    unsigned int GetOffset() const { return m_offset; }
/*
    bool operator==(const BitsetReference& a_other) const;
    bool operator!=(const BitsetReference& a_other) const;*/
    operator bool() const; 

private:
    details::BITSET_TYPE* m_index;
    unsigned char m_offset;
};

}// experis

#endif //BITSET_REFERANCE_HPP_