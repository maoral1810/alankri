#ifndef ADD_THREADS_ASYNCONIZE_HPP
#define ADD_THREADS_ASYNCONIZE_HPP

#include <cstddef> // size_t

#include "runnable.hpp"
#include "thread_pool.hpp"

namespace advcpp {

class AsyncronizeTask : public Runnable {
public:
    enum WHAT_TO_DO {
        ADD_THREAD = 0,
        REMOVE_THREAD
    };
    
    AsyncronizeTask(ThreadPool& a_threadPool , size_t a_numOfThreads, WHAT_TO_DO a_func);
    //~AsyncronizeTask = default;
    //AsyncronizeTask(const AsyncronizeTask& a_other) = defualt;
    //AsyncronizeTask& operator=(const AsyncronizeTask& a_other) = default;

    virtual void Run();

private:
    ThreadPool& m_threadPool;
    size_t m_numOfThreads;
    WHAT_TO_DO m_work;
};

}// advcpp
#endif // ADD_THREADS_ASYNCONIZE_HPP
