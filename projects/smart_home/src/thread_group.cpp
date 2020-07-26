#include "thread_group.hpp"

namespace smart_home
{

ThreadGroup::ThreadGroup(std::vector<Shared_Ptr<Runnable> >& a_threadTasks)
    : m_threadTask(a_threadTasks)
{
    m_group.reserve(NUM_OF_CHANNELS);

    for(size_t i = 0; i < NUM_OF_CHANNELS; ++i)
    {
        m_group.push_back(Shared_Ptr<Thread>( new Thread( (m_threadTask[i].get()) ) ) ); 
    }
} 

void ThreadGroup::JoinAll()
{
    for(size_t i = 0; i < m_group.size(); ++i)
    {
        m_group[i]->Join();
    }
}


} // namespace smart_home
