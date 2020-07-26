#include <exception>
#include <iostream> // cout for debug

#include <ctime> // clock_t , clock_gettime
#include <sys/sysinfo.h> //get_nprocs

#include "thread_pool.hpp"
#include "threads_work.hpp"
#include "asyncronize_task.hpp"
#include "poision_apple.hpp"

namespace advcpp {

const int ThreadPool::g_numOfCores = get_nprocs();

ThreadPool::ThreadPool(size_t a_queueSize, size_t a_numOfThreads) 
    : m_threadsGroup() 
    , m_tasksQueue(a_queueSize)
{
    m_threadsGroup.AddThreads(a_numOfThreads, *this);
}

ThreadPool::~ThreadPool() 
{
    StopAll();
    m_threadsGroup.JoinAll();
}

void ThreadPool::AddTask(const SharedPtr<Runnable>& a_task) NOEXCEPTIONS
{
    m_tasksQueue.Enqueue(a_task);
}

void ThreadPool::AddThreads(size_t a_numOfThreads, bool syncFlag) 
{
    if(syncFlag == false)
    {
        AsyncronizeTask asynconizeAddThreads(*this, a_numOfThreads, AsyncronizeTask::ADD_THREAD);
        SharedPtr<Thread>( new Thread (&asynconizeAddThreads) );
    }
    else
    {
        m_threadsGroup.AddThreads(a_numOfThreads, *this);
    }
}

void ThreadPool::RemoveThreads(size_t a_numOfThreads, bool syncFlag) 
{
    if(syncFlag == false)
    {
        AsyncronizeTask asynconizeRemoveThreads(*this, a_numOfThreads, AsyncronizeTask::REMOVE_THREAD);
        SharedPtr<Thread>( new Thread (&asynconizeRemoveThreads));
    }
    else
    {
        size_t removedThreads = m_threadsGroup.RemoveFinishedThreads();
        // add poision apples as num of thread that we want to remove
        for(size_t i = 0; i < a_numOfThreads - removedThreads; ++i)
        {
            m_tasksQueue.Enqueue(SharedPtr<PoisionApple>(new PoisionApple()));
        }

        while(removedThreads != a_numOfThreads)
        {
            removedThreads += m_threadsGroup.RemoveFinishedThreads();
        } 
    }
    
}

//do not accept new tasks, finish all tasks including those in the queue
bool ThreadPool::Shutdown(size_t a_timeoutMicroSeconds) 
{
    StopAll(); // add poision apple for all threads 
    if(0 == a_timeoutMicroSeconds)
    {
        m_threadsGroup.JoinAll();
        m_threadsGroup.Clear();
        return true;
    }
    // try to finish all tasks and remove all thread in time
    
    return m_threadsGroup.TimeJoinAll(a_timeoutMicroSeconds);
}

//wait for all currently executing to finish, 
//do not accept new ones and do not start executing any pending tasks in the queue
bool ThreadPool::ShutdownImediate(size_t a_timeoutMicroSeconds) 
{
    if(0 == a_timeoutMicroSeconds)
    {
        m_threadsGroup.CancelAll();
        m_threadsGroup.JoinAll();
        return true;
    }
    
    m_threadsGroup.CancelAll();
    return m_threadsGroup.TimeJoinAll(a_timeoutMicroSeconds);
}

//stop currently executing tasks, do not accept new ones or start any pending tasks in the queue
void ThreadPool::ShutdownAggressive()
{

    //m_threadsGroup.StopAll();
/*     ThreadsCont::iterator begin = m_threadsGroup.begin();
    
    while (begin != m_threadsGroup.end())
    {
        ((*begin).GetPtr())->Exit();
        ++begin;
    } */
    // add pthread_exit(0) for all threads ??;
}

size_t ThreadPool::Size()
{
    return m_threadsGroup.Size();
}
//--------------- private functions ----------------------

void ThreadPool::StopAll()
{
    size_t numOfThreads = m_threadsGroup.Size();
    RemoveThreads(numOfThreads);
}

void ThreadPool::ExecuteTask()
{
    SharedPtr<Runnable> val;
    while(1) {
        m_tasksQueue.Dequeue(val);
        try {
                val->Run();
            }
        catch(PoisionAppleException& exp)
        {
            break;
        } catch(...) {
            assert(!"the runnable just throw an exception");
            // todo log
            continue;    
        }
    }
}

void ThreadPool::GetTask(SharedPtr<Runnable>& a_runnable)
{
    try {
        m_tasksQueue.Dequeue(a_runnable);
    }
    catch(...)
    {

    }
}

// ----------------- helpful functions -------------------



} // advcpp