#ifndef FIFO_CONTAINER_INL_HPP
#define FIFO_CONTAINER_INL_HPP

#include <cstddef> // size_t
#include <cassert> // assert
#include "common_utils.hpp"

template<typename T>
CyclicFIFO<T>::CyclicFIFO(size_t a_size)
    : m_cont()
    , m_capacity(a_size)
{}

template<typename T>
bool CyclicFIFO<T>::Insert(const T& a_val) 
{
    if(IsFull())
    {
        return false;
    }
    
    m_cont.push(a_val);

    return true;
}

template<typename T>
bool CyclicFIFO<T>::Remove(T& a_val)
{
    if(IsEmpty())
    {
        return false;
    }
    
    a_val = m_cont.front();
    m_cont.pop();

    return true;
}

template<typename T>
bool CyclicFIFO<T>::IsFull() const NOEXCEPTIONS
{
    return m_cont.size() == m_capacity;
}

template<typename T>
bool CyclicFIFO<T>::IsEmpty() const NOEXCEPTIONS
{
    return m_cont.size() == 0;
}

template<typename T>
size_t CyclicFIFO<T>::Size() const NOEXCEPTIONS
{
    return m_cont.size();
}

template<typename T>
size_t CyclicFIFO<T>::GetCapacity() const NOEXCEPTIONS
{
    return m_capacity;
}

#endif // FIFO_CONTAINER_INL_HPP