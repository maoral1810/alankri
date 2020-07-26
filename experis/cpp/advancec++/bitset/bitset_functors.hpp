#ifndef BIT_SET_FUNCTORS_HPP
#define BIT_SET_FUNCTORS_HPP

#include <assert.h> // assert
#include "bitset.hpp"
#include "details.hpp"

namespace experis {

class ANDOp {
public:
    ANDOp(details::BITSET_TYPE* a_other , size_t a_size)
        : m_other(a_other)
        , m_index(0)
        , m_size(a_size)
    {
        
    }

    void operator()(details::BITSET_TYPE& a_word) {
       assert(m_index != m_size);
       a_word &= m_other[m_index];
       ++m_index;
    }

private:
    details::BITSET_TYPE* m_other;
    size_t m_index;
    size_t m_size;
};


class OrOp {
public:
    OrOp(details::BITSET_TYPE* a_other, size_t a_size)
        : m_other(a_other)
        , m_index(0)
        , m_size(a_size)
    {
        
    }

    void operator()(details::BITSET_TYPE a_word) {
       assert(m_index != m_size);
       m_other[m_index] |= a_word;
       ++m_index;
    }

private:
    details::BITSET_TYPE* m_other;
    size_t m_index;
    size_t m_size;
};

class XorOp {
public:
    XorOp(details::BITSET_TYPE* a_other, size_t a_size)
        : m_other(a_other)
        , m_index(0)
        , m_size(a_size)
    {
        
    }

    void operator()(details::BITSET_TYPE a_word) {
       assert(m_index != m_size);
       m_other[m_index] ^= a_word;
       ++m_index;
    }

private:
    details::BITSET_TYPE* m_other;
    size_t m_index;
    size_t m_size;
};

class NotOp {
public:
    NotOp(){}
    
    void operator()(details::BITSET_TYPE& a_word) {
        a_word = ~a_word;
    }
};

class Mirror {
public:
    Mirror(){}
    
    void operator()(char &byte) {
        const size_t mask_1 = 0x55; /*0b 0101 0101 */
        const size_t mask_2 = 0x33; /*0b 0011 0011 */
        const size_t mask_4 = 0x0f; /*0b 0000 1111 */
        
        //replace adjacent bits//
        byte = ((byte >> 1) & mask_1) | ((byte & mask_1) << 1);//replace couples
        byte = ((byte >> 2) & mask_2) | ((byte & mask_2) << 2);//replace nibbles
        byte = ((byte >> 4) & mask_4) | ((byte & mask_4) << 4);//replace bytes
    }  
};

class CountOn {
public:
    CountOn()
        : m_counter(0)
    {

    }
    // ~CountOn = default ;
    void operator()(details::BITSET_TYPE& a_word) {
        details::BITSET_TYPE m1 = (~(details::BITSET_TYPE)0) / 3;   // Binary 01010101...
        details::BITSET_TYPE m2 = (~(details::BITSET_TYPE)0) / 5;   // Binary 00110011...
        details::BITSET_TYPE m4 = (~(details::BITSET_TYPE)0) / 17;  // Binary 00001111...
        details::BITSET_TYPE h01 = (~(details::BITSET_TYPE)0) / 255; // Hex 0101...

        a_word = (a_word & m1) + ((a_word >> 1) & m1);
        a_word = (a_word & m2) + ((a_word >> 2) & m2);
        a_word = (a_word & m4) + ((a_word >> 4) & m4);

        m_counter += ((a_word * h01) >> (64 - 8)); // change 64 to macro NUM_OF_BITS
    }

    size_t GetVal() const{ return m_counter; }

private:
    size_t m_counter;
};



    //void operator()(details::BITSET_TYPE& a_word) {
/*         details::BITSET_TYPE mask1, mask2, mask3, mask4, mask5, mask6 
        mask1 = 0x5555555555555555 // 01010101...
        mask2 = 0x3333333333333333 // 00110011...
        mask3 = 0x0F0F0F0F0F0F0F0F // 00001111...
        mask4 = 0X00FF00FF00FF00FF // 8 zeroes, 8 ones, etc...
        mask5 = 0X0000FFFF0000FFFF // 16 zeroes, 16 ones, etc...
        mask6 = 0X00000000FFFFFFFF // 32 zeroes, 32 ones

        a_word = (a_word & mask1) + ((a_word >> 1) & mask1)
        a_word = (a_word & mask2) + ((a_word >> 2) & mask2)
        a_word = (a_word & mask3) + ((a_word >> 4) & mask3)
        a_word = (a_word & mask4) + ((a_word >> 8) & mask4)
        a_word = (a_word & mask5) + ((a_word >> 16) & mask5)
        a_word = (a_word & mask6) + ((a_word >> 32) & mask6)

        m_counter += uint8(a_word); */
}//experis
#endif //BIT_SET_FUNCTORS_HPP

/*     switch (op)
    {
        case '^'
            m_other[m_index] ^= a_word;
            break;

        case '&'
            m_other[m_index] &= a_word;
            break;

        case '|'
            m_other[m_index] |= a_word;
            break;
        
        case '~'
            m_other[m_index] = ~a_word;
            break;
    default:
        break;
    } */