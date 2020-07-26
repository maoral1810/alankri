#include <exception>
#include <iostream> // cout for debug
#include "thread_pool.hpp"
#include "thread_to_do.hpp"

static volatile bool g_Is_Shutdown = true;

namespace experis {

ThreadPool::ThreadPool(size_t a_queueSize, size_t a_NumOfThreads) 
    : m_queue(a_queueSize)
    , m_threadTask(new ThreadSWork(*this))
    , m_threads(a_NumOfThreads, SharedPtr<Thread>(new Thread(m_threadTask.GetPtr())))
    , m_shutdownLock()
    , m_timeToShutdown(m_shutdownLock)
{

}

ThreadPool::~ThreadPool() {
    // clear all queue and therad_pool
}

void ThreadPool::AddTask(const SharedPtr<Runnable> a_task) {
    try {
        m_queue.Enqueue(a_task);
    }
    catch(... /* const std::expctions */) {
        std::cout << "add task failed!" << std::endl;
    }
}

void ThreadPool::AddThread() /* throw(std::bad_alloc) */ {
    m_threads.push_back( SharedPtr<Thread>( new Thread ( m_threadTask.GetPtr() ) ) );
}

void ThreadPool::Shutdown() {
    __sync_lock_test_and_set(&g_Is_Shutdown, false); // atomic
    m_timeToShutdown.Broadcast();
    while(!m_threads.empty()) {
        // delete thread??? how if we have sharedptr?(the join is in dtor of thread!)
    }

    m_threads.clear(); // clear thread_pool
}

void ThreadPool::ExecuteTask() {
    while(g_Is_Shutdown) {
        try {
            // condision_var if shutdown stop here
            SharedPtr<Runnable> val;
            m_queue.Dequeue(&val);
            val.GetPtr()->Run();
        }
        catch(...) {
            break;
        }
    }
    //delete 
}

} // experis