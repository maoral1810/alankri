#include "threads_work.hpp" 
#include "thread_pool.hpp"
#include "common_utils.hpp"

namespace advcpp {

ThreadSWork::ThreadSWork(ThreadPool& a_threadPool)
    : m_threadPool(a_threadPool)
    , m_isFinish(false)
{

}

void ThreadSWork::Run() {
    m_threadPool.ExecuteTask();
    Finish();
}

bool ThreadSWork::IsFinish() NOEXCEPTIONS
{
    return m_isFinish.Get();
}

void ThreadSWork::Finish() NOEXCEPTIONS
{
    m_isFinish.Aquire();
}


} // advcpp