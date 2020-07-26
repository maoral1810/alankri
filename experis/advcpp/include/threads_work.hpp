#ifndef THREAD_WORK_HPP
#define THREAD_WORK_HPP

#include "common_utils.hpp"
#include "runnable.hpp"

namespace advcpp {
class ThreadPool;
class ThreadSWork : public Runnable
{
public:
    ThreadSWork(ThreadPool& a_threadPool);
    //~ThreadSWork() = default;

    virtual void Run();
    bool IsFinish() NOEXCEPTIONS;

private:
    void Finish() NOEXCEPTIONS;

private:
    ThreadPool& m_threadPool;
    AtomicValue<bool> m_isFinish;
};

} // advcpp

#endif //THREAD_WORK_HPP