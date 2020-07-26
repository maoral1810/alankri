#ifndef BITSET_INL_HPP_
#define BITSET_INL_HPP_

#include "bitset_functors.hpp"

template<size_t N>
Bitset<N>::Bitset()
    : m_bitArr()
{
    this->SetALLOff(); // neccery or it will be zero anyway in create?
}

/*
template<size_t N>
Bitset<N>::~Bitset() {

}

template<size_t N>  
Bitset<N>::Bitset(const Bitset& a_other)
    : m_bitArr(a_other.m_bitArr)
{

}

template<size_t N> 
Bitset<N>& Bitset<N>::operator=(const Bitset& a_other) {
    m_bitArr = a_other.m_bitArr;
} */


template<size_t N> 
BitsetReference Bitset<N>::operator[](size_t a_bitIndex) {
    BitsetReference referance(CalcWord(a_bitIndex), CalcOffset(a_bitIndex));

    return referance;
}

template<size_t N>
bool Bitset<N>::operator[](size_t a_bitIndex) const {
    BitsetReference referance(CalcWord(a_bitIndex), CalcOffset(a_bitIndex));

    return referance;
}

template<size_t N> 
void Bitset<N>::SetALLOn() {
    std::fill(m_bitArr, m_bitArr + NUM_OF_ELEM, -1);
    details::BITSET_TYPE mask = ( (1 << (CalcOffset(N) + 1) ) - 1);
    //m_bitArr[NUM_OF_ELEM - 1] &=  mask;

    //std::cout << "mask = " << mask << std::endl; 
/*     details::BITSET_TYPE* ptr = &(m_bitArr[NUM_OF_ELEM - 1]);
    for(size_t i = 0; i < CalcOffset(N); ++i) {
        std::cout << ptr[i] << std::endl; 
    } */
}

template<size_t N> 
void Bitset<N>::SetALLOff() {
    std::fill(m_bitArr, m_bitArr + NUM_OF_ELEM, 0);
}

template<size_t N> 
void Bitset<N>::SetBitOnTo(size_t a_index, bool a_val) {
    details::BITSET_TYPE mask = 1 << CalcOffset(a_index);

    (a_val) ? *CalcWord(a_index) |= mask : *CalcWord(a_index) &= ~mask; // change to operator []
} 

template<size_t N> 
void Bitset<N>::FlipBitSet(size_t a_index) {
    *CalcWord(a_index) ^= 1 << CalcOffset(a_index);
}


template<size_t N> 
size_t Bitset<N>::CountOnBits() {
    experis::CountOn functor;
    std::for_each(m_bitArr, m_bitArr + NUM_OF_ELEM, functor);
    return functor.GetVal();
}

template<size_t N> 
size_t Bitset<N>::CountOffBits() {
    return N - CountOnBits(); 
}


template<size_t N> 
void Bitset<N>::MirrorBitSet() {
    experis::Mirror functor;
    char* cloneByByte = reinterpret_cast<char*>(&(m_bitArr[0])); 
    std::for_each(cloneByByte, cloneByByte + (NUM_OF_ELEM * details::BITS_IN_BYTE), functor);
    // work only for chunk chunk
}



template<size_t N> 
Bitset<N> Bitset<N>::operator&(const Bitset& a_other) const {
    Bitset<N> clone(a_other);
    clone &= *this;
    
    return clone;
}

template<size_t N>
Bitset<N> Bitset<N>::operator|(const Bitset& a_other) const {
    Bitset<N> clone(a_other);
    experis::OrOp functor(clone.m_bitArr, NUM_OF_ELEM);
    std::for_each(m_bitArr, m_bitArr + NUM_OF_ELEM, functor);
    
    return clone;
}

template<size_t N>
Bitset<N> Bitset<N>::operator^(const Bitset& a_other) const{
    Bitset<N> clone(a_other);
    experis::XorOp functor(clone.m_bitArr, NUM_OF_ELEM);
    std::for_each(m_bitArr, m_bitArr + NUM_OF_ELEM, functor);
    
    return clone;
}

template<size_t N>
Bitset<N>& Bitset<N>::operator~(void) {
    std::for_each(m_bitArr, m_bitArr + NUM_OF_ELEM, experis::NotOp());
    
    return *this;
}


template<size_t N> 
Bitset<N>& Bitset<N>::operator&=(const Bitset& a_other) {
    std::for_each(m_bitArr, m_bitArr + NUM_OF_ELEM, experis::ANDOp(m_bitArr, NUM_OF_ELEM));
    return *this;
} 

 template<size_t N> 
Bitset<N>& Bitset<N>::operator|=(const Bitset& a_other) {
    std::for_each(m_bitArr, m_bitArr + NUM_OF_ELEM, experis::OrOp(m_bitArr, NUM_OF_ELEM));
    return *this;
}

template<size_t N> 
Bitset<N>& Bitset<N>::operator^=(const Bitset& a_other) {
    std::for_each(m_bitArr, m_bitArr + NUM_OF_ELEM, experis::XorOp(m_bitArr, NUM_OF_ELEM));
    return *this;
}

// ------------------- PRIVATE FUNCTIONS ----------
template<size_t N> 
details::BITSET_TYPE Bitset<N>::CalcOffset(size_t a_Index) {
    return a_Index % details::NUM_OF_BITS;
}
    
template<size_t N> 
details::BITSET_TYPE* Bitset<N>::CalcWord(size_t a_Index){
    return &(m_bitArr[a_Index / details::NUM_OF_BITS]);
}


#endif //BITSET_INL_HPP_