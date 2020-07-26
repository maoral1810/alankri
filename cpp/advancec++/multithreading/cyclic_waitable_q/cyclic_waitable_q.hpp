#ifndef __CYCLIC_WAITABLE_Q_HPP__
#define __CYCLIC_WAITABLE_Q_HPP__

#include <vector>
#include "semaphore.hpp"
#include "mutex.hpp"
#include "condision_variable.hpp"


namespace experis{
template<class T>
class WaitCycQ {

public:
    WaitCycQ(size_t a_queueSize)throw();
    ~WaitCycQ()throw();
    
    void Enqueue(T a_val);
    void Dequeue(T* a_data);

    bool HasFreeSpaceToWrite()const { return (m_numOfElem < m_capacity);}

private:
    WaitCycQ(const WaitCycQ& a_other);
    WaitCycQ& operator=(const WaitCycQ& a_other);

    std::vector<T> m_vec;
    size_t m_capacity;
    size_t m_readerInx;
    size_t m_writerInx;
    MyMutex m_queueLock;
    CondVar m_emptySpaces;
    CondVar m_dataToRead;
    size_t m_numOfConsumers;
    size_t m_numOfProducers;
    size_t m_numOfElem;
    bool m_isShutdown;
};

#include "cyclic_waitable_q_inl.hpp"
}// namespace experis
#endif //__CYCLIC_WAITABLE_Q_HPP__