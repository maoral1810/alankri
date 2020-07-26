#include "asyncronize_task.hpp"

namespace advcpp {

AsyncronizeTask::AsyncronizeTask(ThreadPool& a_threadPool ,size_t a_numOfThreads, WHAT_TO_DO a_func)
    : m_threadPool(a_threadPool)
    , m_numOfThreads(a_numOfThreads)
    , m_work(a_func)
{}

void AsyncronizeTask::Run()
{
    switch (m_work)
    {
        case ADD_THREAD:
            m_threadPool.AddThreads(m_numOfThreads, true);
            break;
            
        case REMOVE_THREAD:
            m_threadPool.RemoveThreads(m_numOfThreads, true);
            break;

        default: assert(!"can't do work "); break;
    }
}

}// advcpp