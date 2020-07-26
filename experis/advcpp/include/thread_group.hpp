#ifndef THREAD_GROUP_HPP
#define THREAD_GROUP_HPP

#include <vector>

#include <cstddef> // size_t

#include "shared_ptr.hpp"
#include "common_utils.hpp"
#include "thread.hpp"
#include "mutex.hpp"
#include "threads_work.hpp"
#include "excecutor.hpp"

//! @brief Thread Group 
//* uniting pool of thread and mutex(all functions are thread safe)
//* use stl vector as a container of threads
//! @author Author Maor Alankri

namespace advcpp {

class ThreadGroup : private Uncopyable {
private:
    typedef std::vector<Exceutor> Pool;

public:
    ThreadGroup();
    // ~ThreadGroup = default;
    
    void AddThreads(size_t a_numOfThreads, ThreadPool& a_threadpool);
    size_t RemoveFinishedThreads();

    bool TimeJoinAll(size_t a_timeoutMicroSeconds);
    void JoinAll();
    void DetachAll();
    void CancelAll();
    void Clear();
    
    size_t Size() NOEXCEPTIONS;

private:
    Mutex m_mutex;
    Pool m_threads;
    //SharedPtr<ThreadSWork> m_threadTask;
};

}// advcpp
#endif // THREAD_GROUP