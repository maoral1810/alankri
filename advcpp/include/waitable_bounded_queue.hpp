#ifndef WAITABLE_BOUNDED_QUEUE_HPP
#define WAITABLE_BOUNDED_QUEUE_HPP

#include <vector>

#include "mutex.hpp"
#include "condition_variable.hpp"
#include "common_utils.hpp"
#include "cyclic_fifo.hpp"
#include "inl/functions_object_for_waitable_queue.hpp"

//! @brief Create a waitable boundede queue(FIFO) thread safe
//! @warning container need to have at least the functions: 
// 1)GetCapacity 2) Size 3)Insert 4)Remove 
//! @author Author Maor Alankri

namespace advcpp {

template<class T, class Container = CyclicFIFO<T> >
class WaitableBoundedQueue : private Uncopyable {
public:
    //!@brief CTOR of Waitable Bounded Queue  
    //!@param[in] a_queueSize - max number of elements(capacity) that can be stored in the queue
    WaitableBoundedQueue(size_t a_queueSize);

    //!@brief DTOR of Waitable Bounded Queue
    //! destroy object
    ~WaitableBoundedQueue() NOEXCEPTIONS;

    //!@brief Enqueue new val into tail of the Waitable Bounded Queue  
    //!@param[in] a_val - template element to enqueue
    //!@warning - can throw exceptions of bad alloc or shutingdown
    void Enqueue(const T& a_val);

    //!@brief dequeue val from the head of Waitable Bounded Queue  
    //!@param[in] a_val - template element to enqueue
    //!@warning - can throw exceptions of bad alloc or shutingdown
    void Dequeue(T& a_data);

    //!@brief turn on shutingdown flag
    //!@param[in] a_timeUntilShutDown - time until shutDownFlagIsUp (in micro Seconeds)
    //void ShutDownQueue(unsigned int a_timeUntilShutDown) NOEXCEPTIONS;

private:
    //!@brief turn on shutingdown flag 
    void queueIsShutingdown() NOEXCEPTIONS;

    //!@brief check the shutingdown flag Waitable Bounded Queue 
    //!@param[out] bool - true if is shutingdown or false if not 
    bool IsQueueShutingdown() NOEXCEPTIONS;
    
    //!@brief get access to queue for read or write ( threads syncronize ) 
    //!@param[in] - pointer to predicate function
    //!@warning - can throw shutingdown exception 
    template<class Predicate>
    void ThreadAccessToQueue(Predicate a_predicateFunc);
/* private:
   template<typename T,class Container ,class Predicate>
   friend class WaitFor; */

private:
    Container m_cont;
    Mutex m_queueLock;
    AtomicValue<bool> m_shutdownFlag;
    CondVar m_condVar;
};

#include "inl/waitable_bounded_queue_inl.hpp"

} // advcpp

#endif // WAITABLE_BOUNDED_QUEUE_HPP