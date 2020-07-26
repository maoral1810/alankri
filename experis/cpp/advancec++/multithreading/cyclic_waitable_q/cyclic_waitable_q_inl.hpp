#include <new>
#include "cyclic_waitable_q.hpp"
#include "cyclic_waitable_q_exceptions.hpp"

template<class T>
WaitCycQ<T>::WaitCycQ(size_t a_queueSize)throw()
    : m_capacity(a_queueSize)
    , m_readerInx(0)
    , m_writerInx(0)
    , m_isShutdown(false)
    , m_queueLock()
    , m_vec(a_queueSize)
    , m_emptySpaces(m_queueLock)
    , m_dataToRead(m_queueLock)
{

}
template<class T>
WaitCycQ<T>::~WaitCycQ()throw() {
    m_isShutdown = true;

    m_emptySpaces.notifyAll();
    while(m_numOfProducers > 0) {
        m_emptySpaces.Wait();
    }

    m_dataToRead.notifyAll();
    while(m_numOfConsumers > 0) {
        m_dataToRead.Wait();
    }
}
template<class T>
void WaitCycQ<T>::Enqueue(T a_val) {
    m_queueLock.Lock();
    while(HasFreeSpaceToWrite()) {
        m_emptySpaces.Wait();
        ++m_numOfProducers;
    }
    
    if(m_isShutdown) {
    --m_numOfConsumers;
    /* throw ShutdownException; */
    throw(0);
    
    }
    try{
        m_vec[m_writerInx] = a_val;
        ++m_numOfElem;
        --m_numOfProducers;
    }
    catch(std::bad_alloc ex)
    {
        m_queueLock.Unlock();
        m_emptySpaces.notifyOne();
    }
    m_writerInx = (m_writerInx + 1) % m_capacity;
    m_queueLock.Unlock();
    m_dataToRead.notifyOne();
}

template<class T>
void WaitCycQ<T>::Dequeue(T* a_data) {

    m_queueLock.Lock();
    while((m_numOfElem == 0) && (!m_isShutdown)) {
        ++m_numOfConsumers;
        m_dataToRead.Wait();
    }
    if(m_isShutdown) {
        --m_numOfConsumers;
        /* throw ShutdownException; */
        throw(0);
    }
    try {
        *a_data = m_vec[m_readerInx];;
        m_readerInx = (m_readerInx + 1) % m_capacity;
        --m_numOfConsumers;
        m_queueLock.Unlock();
        m_emptySpaces.notifyOne();
    }
    catch(std::bad_alloc ex)
    {
        m_queueLock.Unlock();
        m_dataToRead.notifyOne();
        throw;
    }
}

