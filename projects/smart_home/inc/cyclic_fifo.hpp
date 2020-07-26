#ifndef FIFO_CONTAINER_HPP
#define FIFO_CONTAINER_HPP

#include <cstddef> // size_t
#include <queue>

#include "common_utils.hpp"

//! @brief Create a Generic data type Queue of a given size
//* The Queue wraps around stl container
//* Concept: First In First Out Container
//! @author Author Maor Alankri

namespace smart_home {

template<typename T>
class CyclicFIFO {
private:
    enum CONTANIER_ACTION
    {
        WRITE = 0,
        READ
    };
    typedef std::queue<T> Container;
public:

    //!@brief CTOR of queue  
    //!@param[in] a_size - max number of elements(capcity) that can be stored in the queue
    CyclicFIFO(size_t a_size);

    // ~CyclicFIFO() = default;
    // CyclicFIFO(const CyclicFIFO& a_other);
    // CyclicFIFO& operator=(const CyclicFIFO& a_other);

    //!@brief insert new element to the next pos in queue(end of the queue)  
    //!@param[in] a_val - value to store in queue
    //!@retval bool return false if the queue is full or true otherwise
    //!@warning need to catch bad_alloc  exceptions in use
    bool Insert(const T& a_val);
    
    //!@brief remove Element from the head of the queue  
    //!@param[in] a_val - return value the removed from queue 
    //!@warning need to catch bad_alloc  exceptions in use
    bool Remove(T& a_val);
    
    //!@brief return the size of the queue  
    size_t Size() const NOEXCEPTIONS;

    //!@brief return the capacity of the queue  
    size_t GetCapacity() const NOEXCEPTIONS;

private:
    //!@brief return if queue is full 
    bool IsFull() const NOEXCEPTIONS;

    //!@brief return if queue is empty
    bool IsEmpty() const NOEXCEPTIONS;
    
private:
    Container m_cont;
    size_t m_capacity;
};

#include "inl/cyclic_fifo_inl.hpp"

} // namespace smart_home

#endif //FIFO_CONTAINER_HPP