#ifndef FUNCTIONS_OBJECT_FOR_WATIABLE_QUEUE_HPP
#define FUNCTIONS_OBJECT_FOR_WATIABLE_QUEUE_HPP

#include <cstddef>
#include <iostream>

#include "../common_utils.hpp"
#include "mutex.hpp"
#include "condition_variable.hpp"
// -------------------------- functions objects -----------------
namespace advcpp
{

//-------------------------Shutdown--------------------------------

class Shutdown : private Uncopyable {
public:
    Shutdown(Mutex& a_mutex);
    ~Shutdown();

    void TurnOn();
    bool IsShutdown();

private:
    Mutex& m_mutex;
    bool m_isShutdown;
};

inline Shutdown::Shutdown(Mutex& a_mutex) 
    : m_mutex(a_mutex)
    , m_isShutdown(false)
{}

inline Shutdown::~Shutdown()
{}

inline void Shutdown::TurnOn()
{
    MutexGuard lock(m_mutex);
    m_isShutdown = true;
}

inline bool Shutdown::IsShutdown()
{
    MutexGuard lock(m_mutex);
    return m_isShutdown;
}
 
//-------------------------------------------------------------------
template<typename T, class Queue>
class IsQueueFull {
public:
    IsQueueFull(const Queue& a_queue, AtomicValue<bool>& a_shutdown);
    ~IsQueueFull();
    //IsQueueFull(const IsQueueFull& a_other) = default;
    //IsQueueFull& operator=(const IsQueueFull& a_other) = default;

    bool operator()() const;
    
private:
    const Queue& m_queue;
    AtomicValue<bool>& m_shutdown;
};

template<typename T, class Queue>
IsQueueFull<T,Queue>::IsQueueFull(const Queue& a_queue, AtomicValue<bool>& a_shutdown)
    : m_queue(a_queue)
    , m_shutdown(a_shutdown)
{}

template<typename T, class Queue>
IsQueueFull<T,Queue>::~IsQueueFull()
{}

template<typename T, class Queue>
bool IsQueueFull<T,Queue>::operator()() const 
{
    return ( (m_queue.Size() == m_queue.GetCapacity())  && !m_shutdown.Get() );
}
//-----------------------------------------------------------------
template<typename T, class Queue>
class IsQueueEmpty {
public:
    IsQueueEmpty(const Queue& a_queue, AtomicValue<bool>& a_shutdown);
    ~IsQueueEmpty();
    //IsQueueEmpty(const IsQueueEmpty& a_other) = default;
    //IsQueueEmpty& operator=(const IsQueueEmpty& a_other) = default;
    
    virtual bool operator()() const;

private:
    const Queue& m_queue;
    AtomicValue<bool>& m_shutdown;
};

template<typename T, class Queue>
IsQueueEmpty<T,Queue>::IsQueueEmpty(const Queue& a_queue, AtomicValue<bool>& a_shutdown)
    : m_queue(a_queue)
    , m_shutdown(a_shutdown)
{}

template<typename T, class Queue>
IsQueueEmpty<T,Queue>::~IsQueueEmpty()
{}

template<typename T, class Queue>
bool IsQueueEmpty<T,Queue>::operator()() const 
{
    return ( (m_queue.Size() == 0) && !m_shutdown.Get() );
}

//--------------------------------------------------
//------------------------------------------------------------
/* template<typename T,class Container ,class Predicate>
class WaitFor {
public:
    WaitFor(WaitableBoundedQueue<T, Container>& a_queue, Predicate m_predicateFunc); 
    ~WaitFor();

private:
    WaitableBoundedQueue<T, Container>& m_queue;
    Predicate m_predicateFunc;
};

template<typename T,class Container ,class Predicate>
WaitFor<T,Container,Predicate>::WaitFor(WaitableBoundedQueue<T,Container>& a_queue, Predicate a_predicateFunc)
    : m_queue(a_queue)
    , m_predicateFunc(a_predicateFunc)
{
    m_condVar.Wait(m_mutex ,m_predicateFunc);
}

template<typename T,class Container ,class Predicate>
WaitFor<T,Container,Predicate>::~WaitFor()
{}  */
//------------------------------------------
  

} //  advcpp


#endif // FUNCTIONS_OBJECT_FOR_WATIABLE_QUEUE_HPP