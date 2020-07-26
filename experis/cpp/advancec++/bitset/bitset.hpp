#ifndef BITSET_HPP_
#define BITSET_HPP_

#include <limits>
#include <algorithm>
#include "bitset_reference.hpp"
#include "details.hpp"

namespace experis {

template<size_t N>
class Bitset {

public:
    static const size_t NUM_OF_ELEM = (N / details::NUM_OF_BITS) + 1;
    Bitset();
    //~Bitset() = default;
    //Bitset(const Bitset& a_other) = default;
    //Bitset& operator=(const Bitset& a_other) = default;

    void SetALLOn();
    void SetALLOff();
    void SetBitOnTo(size_t a_index, bool a_val);
    size_t CountOnBits();
    size_t CountOffBits();
    void MirrorBitSet();
    void FlipBitSet(size_t a_index);

    BitsetReference operator[](size_t a_index);
    bool operator[](size_t a_bitIndex) const;
    Bitset operator&(const Bitset& a_other) const;
    Bitset operator|(const Bitset& a_other) const;
    Bitset operator^(const Bitset& a_other) const;
    Bitset& operator~(void);
    Bitset& operator&=(const Bitset& a_other);
    Bitset& operator|=(const Bitset& a_other);
    Bitset& operator^=(const Bitset& a_other); 

private:
    details::BITSET_TYPE CalcOffset(size_t a_Index);
    details::BITSET_TYPE* CalcWord(size_t a_Index);

    details::BITSET_TYPE m_bitArr[NUM_OF_ELEM];
};

#include "bitset_inl.hpp"

}// experis

#endif //BITSET_HPP_
