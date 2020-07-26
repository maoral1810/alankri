#include "bitset_reference.hpp" 

namespace experis {

BitsetReference::BitsetReference(details::BITSET_TYPE* a_index, unsigned char a_offset)
    : m_index(a_index)
    , m_offset(a_offset)
{
    
}

BitsetReference& BitsetReference::operator=(bool a_val) {
    details::BITSET_TYPE mask = 1 << m_offset;
    *m_index &= ~mask;
    *m_index |= a_val << m_offset;

    return *this;
}

BitsetReference::operator bool() const {
    details::BITSET_TYPE mask = 1 << m_offset;
    return (*m_index & mask);
}
/* 
bool BitsetReference::operator==(const BitsetReference& a_other) const {


}
    bool operator!=(const BitsetReference& a_other) const;
    operator bool() const;
 */


}// experis