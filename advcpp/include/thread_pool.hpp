#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <exception>
#include <iostream> // cout for debug
#include <vector>

#include <cstddef> // size_t

#include "shared_ptr.hpp"
#include "thread_group.hpp"
#include "waitable_bounded_queue.hpp"
#include "runnable.hpp"
#include "thread.hpp"
#include "common_utils.hpp"

//! @brief Thread Pool 
//* Using WaitableQueue as a container ,Sheardptr , Thread
//* use stl vector as a container of threads
//! @author Author Maor Alankri

namespace advcpp {

class ThreadPool : private Uncopyable {
private:
    typedef std::vector<SharedPtr<Thread> > ThreadsCont;
public:
    //!@brief CTOR of ThreadPool  
    //!@param[in] a_queueSize - the size of the q(constant!! can't grow on demand)
    //!@param[in] a_numOfThreads - the size of thread container (can grow on demand)
    explicit ThreadPool(size_t a_queueSize = 1, size_t a_numOfThreads = g_numOfCores + 1 );

    //!@brief DTOR of ThreadPool  
    ~ThreadPool();

    //!@brief Add Tasks to ThreadPool  
    //!@param[in] a_task - shared pointer to task
    // the task be add to waitableQueue of tasks
    void AddTask(const SharedPtr<Runnable>& a_task) NOEXCEPTIONS; 

    //!@brief Add Threads to ThreadPool  
    //!@param[in] a_numOfThreads - the number of threads that will be add to thread pool
    //!@param[in] syncFlag - if true, the function wait until all thread will be add to threadpool (syncronize)
    //                       if false, the function NOT wait until all thread will be add to threadpool (asyncronize)
    void AddThreads(size_t a_numOfThreads = 1, bool syncFlag = true);

    //!@brief Remove Threads From ThreadPool  
    //!@param[in] a_numOfThreads - the number of threads that will be removed from thread pool
    //!@param[in] syncFlag - if true, the function wait until all thread will be removed from threadpool (syncronize)
    //                       if false, the function NOT wait until all thread will be removed from threadpool (asyncronize)
    void RemoveThreads(size_t a_numOfThreads = 1, bool syncFlag = true);

    //!@brief Shutdown ThreadPool (exit normally)
    // 1)do not accept new tasks    
    // 2)finish all tasks including those in the queue
    //!@param[in] a_timeoutMicroSeconds - the time to ???
    //!@retval bool: true if all tasks in Queue are finish in the time, false otherwise
    //! if shutdown call with default(0) , the function wait until all the threads will finish/
    //! always return true! 
    bool Shutdown(size_t a_timeoutMicroSeconds = 0);
    
    //!@brief Shutdown ThreadPool Imediate
    // 1)wait for all currently executing to finish, 
    // 2)do not accept new tasks
    // 3)do not start executing any pending tasks in the queue
    //!@param[in] a_timeoutMicroSeconds - the time to ???
    //!@retval bool: true if all thread are finish in their work in time, false otherwise
    bool ShutdownImediate(size_t a_timeoutMicroSeconds = 0);

    //!@brief Shutdown ThreadPool Aggressive
    // 1)stop currently executing tasks 
    // 2)do not accept new ones
    // 3)do not start any pending tasks in the queue
    //!@warning active task stop work that in process(work will be lost)
    void ShutdownAggressive();

    void StopAll();

    size_t Size();

private:
    friend class ThreadSWork;
    void ExecuteTask();

    friend class ThreadGroup;
    void GetTask(SharedPtr<Runnable>& a_runnable);

private:
    static const int g_numOfCores;

    ThreadGroup m_threadsGroup; 
    WaitableBoundedQueue<SharedPtr<Runnable> > m_tasksQueue;
    SharedPtr<ThreadSWork> m_threadTask;
};

} // advcpp

#endif //THREAD_POOL_HPP

/*

AddThreads and removeThreads are:
async or sync you get to choose if they wait till the add/remove is actually done, 
if you can do both make the function receive an argument to select the behavior
Removing a thread from the pool: 
we do not care which one: is it one that is waiting in the queue or one currently executing a task



*/