#ifndef EXCECUTOR_HPP
#define EXCECUTOR_HPP

#include "shared_ptr.hpp"
#include "runnable.hpp"
#include "threads_work.hpp"
#include "thread.hpp"

namespace advcpp {

class Exceutor 
    {
    public:
        Exceutor(ThreadSWork* a_runnable);
        //~Exceutor = default;
        //Exceutor(const Exceutor& a_other)
        //Exceutor& operator=(const Exceutor& a_other)

        void Join();
        void Detach();
        void Cancel();
        bool TryTimeJoin(const struct timespec& a_timeout);
        bool IsThreadFinish() NOEXCEPTIONS;
private:
    SharedPtr<ThreadSWork> m_tasks;
    SharedPtr<Thread> m_thread; // allways after task
};

} // advcpp

#endif //EXCECUTOR_HPP