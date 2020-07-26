#include <exception>
#include <utility>

#include <cassert> // assert
#include <cerrno> 

#include "thread_group.hpp"
#include "mutex.hpp"
#include "threads_work.hpp"
#include "poision_apple.hpp"
#include "thread.hpp"
#include "excecutor.hpp"

namespace advcpp {

static void CheckClockGetTimeStatus(int a_retval);

// ----------------------- class Exceutor --------------------

ThreadGroup::ThreadGroup()
    : m_mutex()
    , m_threads()
{
    
}

void ThreadGroup::AddThreads(size_t a_numOfThreads, ThreadPool& a_threadpool)
{
    MutexGuard lock(m_mutex);
    m_threads.reserve(m_threads.size() + a_numOfThreads);

    for(size_t i = 0; i < a_numOfThreads; ++i)
    {
        Exceutor excecutor(new ThreadSWork(a_threadpool));
        m_threads.push_back(excecutor);
    }
}

size_t ThreadGroup::RemoveFinishedThreads()
{
    MutexGuard lock(m_mutex);
    size_t countRemovedThreads = 0;
    Pool::reverse_iterator from = m_threads.rbegin();

    while(from != m_threads.rend())
    {
        if(from->IsThreadFinish())
        {
            std::swap(*from, m_threads.back());
            m_threads.back().Join();
            m_threads.pop_back();
            ++countRemovedThreads;
        }
        
        ++from;
    }

    return countRemovedThreads;
}

void ThreadGroup::JoinAll()
{
    MutexGuard lock(m_mutex);
    Pool::iterator begin = m_threads.begin();
    
    while (begin != m_threads.end())
    {
        begin->Join();
        ++begin;
    }

    m_threads.clear(); // maybe dont needed
}

void ThreadGroup::DetachAll()
{
    MutexGuard lock(m_mutex);
    Pool::iterator begin = m_threads.begin();
    
    while (begin != m_threads.end())
    {
        begin->Detach();
        ++begin;
    }

    m_threads.clear();
}

void ThreadGroup::CancelAll()
{
    MutexGuard lock(m_mutex);
    Pool::iterator begin = m_threads.begin();
    
    while (begin != m_threads.end())
    {
        begin->Cancel();
        ++begin;
    }
}

bool ThreadGroup::TimeJoinAll(size_t a_timeoutMicroSeconds)
{
    timespec timeUntilShutDown;
    clockid_t timeNow = CLOCK_MONOTONIC;
    int retval = clock_gettime(timeNow, &timeUntilShutDown);
    if(retval == -1)
    {
        CheckClockGetTimeStatus(retval);
    }

    timeUntilShutDown.tv_nsec += MicroToNano(a_timeoutMicroSeconds);
    
    MutexGuard lock(m_mutex);
    Pool::iterator begin = m_threads.begin();
    while(begin != m_threads.end())
    {
        if(false == begin->TryTimeJoin(timeUntilShutDown))
        {
            break;
        }
        ++begin;
    }

    return (begin == m_threads.end()) ? true : false;
}

size_t ThreadGroup::Size() NOEXCEPTIONS
{
    MutexGuard lock(m_mutex);
    return m_threads.size();
}

void ThreadGroup::Clear()
{
    m_threads.clear();
}

//------------ static functions ----------------
static void CheckClockGetTimeStatus(int a_retval)
{
    switch(a_retval)
    {
        case EFAULT:
            assert(!"tp points outside the accessible address space");
            break;
        case EINVAL:
            assert(!"The clk_id specified is not supported on this system");
            break;
        default:break;
    }
}

}// advcpp