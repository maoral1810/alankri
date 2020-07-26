#include "thread_to_do.hpp" 
#include "thread_pool.hpp"

namespace experis {

ThreadSWork::ThreadSWork(ThreadPool& a_threadPool)
    : m_threadpool(a_threadPool)
{

}

void ThreadSWork::Run() {
    m_threadpool.ExecuteTask();
}

} // experis