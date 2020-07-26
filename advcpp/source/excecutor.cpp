#include "excecutor.hpp"
#include "thread.hpp"
#include "runnable.hpp"

namespace advcpp{

Exceutor::Exceutor(ThreadSWork* a_runnable)
    : m_tasks(a_runnable)
    , m_thread(new Thread(a_runnable))
{}

void Exceutor::Join()
{
    m_thread->Join();
}

void Exceutor::Detach()
{
    m_thread->Detach();
}

void Exceutor::Cancel()
{
    m_thread->Cancel();
}

bool Exceutor::TryTimeJoin(const struct timespec& a_timeout)
{
    return m_thread->TimeJoin(a_timeout);
}

bool Exceutor::IsThreadFinish() NOEXCEPTIONS
{
    return m_tasks->IsFinish();
}

}// advcpp