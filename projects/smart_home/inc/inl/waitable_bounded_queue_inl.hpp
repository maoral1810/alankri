#ifndef WAITABLE_BOUNDED_QUEUE_INL
#define WAITABLE_BOUNDED_QUEUE_INL

#include <iostream>
#include <new> // bad_alloc
#include <unistd.h> // usleep
#include <cassert>

#include "waitable_bounded_queue_exceptions.hpp"
#include "functions_object_for_waitable_queue.hpp"
#include "common_utils.hpp"
#include "condition_variable.hpp"

//#define DEBUG
// ------------------------- API Functions -----------------------------
template<class T, class Container>
WaitableBoundedQueue<T,Container>::WaitableBoundedQueue(size_t a_queueSize)
    : m_cont(a_queueSize)
    , m_queueLock()
    , m_shutdownFlag(false)
    , m_condVar()
{
}

template<class T, class Container>
WaitableBoundedQueue<T,Container>::~WaitableBoundedQueue() NOEXCEPTIONS
{
    //queueIsShutingdown();
    m_shutdownFlag.Aquire();
    m_condVar.NotifyAll();
}

template<class T, class Container>
void WaitableBoundedQueue<T,Container>::Enqueue(const T& a_val) 
{
    CondVarGuard cv(m_condVar);
    {
        MutexGuard lock(m_queueLock);
        IsQueueFull<T,Container> predicateFunc(m_cont, m_shutdownFlag);// TODO *this
        ThreadAccessToQueue(predicateFunc);
        //WaitFor<T,Container,IsQueueFull<T,Container> >(*this, predicateFunc);
        assert(m_cont.Insert(a_val));
    }
}

template<class T, class Container>
void WaitableBoundedQueue<T,Container>::Dequeue(T& a_data) 
{
    CondVarGuard cv(m_condVar);
    {
        MutexGuard lock(m_queueLock);
        IsQueueEmpty<T,Container> predicateFunc(m_cont, m_shutdownFlag); // TODO *this
        ThreadAccessToQueue(predicateFunc);
        //WaitFor<IsQueueEmpty<T,Container> >(*this);
        assert(m_cont.Remove(a_data));
    }
}

template<class T, class Container>
void WaitableBoundedQueue<T,Container>::ShutDownQueue(unsigned int a_timeUntilShutDown) NOEXCEPTIONS
{
    usleep(a_timeUntilShutDown);
    queueIsShutingdown();
}

//------------------ private Functions -----------------------------
template<class T, class Container>
void WaitableBoundedQueue<T,Container>::queueIsShutingdown() NOEXCEPTIONS
{
    m_shutdownFlag.Aquire();
    m_condVar.NotifyAll();
}

template<class T, class Container>
bool WaitableBoundedQueue<T,Container>::IsQueueShutingdown() NOEXCEPTIONS
{
    return m_shutdownFlag.Get();
}

template<class T, class Container>
template<class Predicate>
void WaitableBoundedQueue<T,Container>::ThreadAccessToQueue(Predicate a_predicateFunc)
{
    m_condVar.Wait(m_queueLock, a_predicateFunc);
    if(m_shutdownFlag.Get())
    {
        throw WaitableBoundedQueueShutdownException();
    }
}

#endif // WAITABLE_BOUNDED_QUEUE_INL