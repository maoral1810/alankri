#ifndef THREAD_GROUP_HPP    
#define THREAD_GROUP_HPP

#include <vector>

#include "runnable.hpp"
#include "thread.hpp"
#include "common_utils.hpp"

namespace smart_home
{
    
class ThreadGroup : private Uncopyable
{
public:
    typedef std::vector<Shared_Ptr<Thread> > Group;
public:
    ThreadGroup(std::vector<Shared_Ptr<Runnable> >& a_threadTasks);
    //~ThreadGroup() = default;

    void JoinAll();
private:
    Group m_group;
    std::vector<Shared_Ptr<Runnable> > m_threadTask;
};
} // namespace smart_home


#endif //THREAD_GROUP_HPP