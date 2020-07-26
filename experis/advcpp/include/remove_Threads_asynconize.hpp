#ifndef REMOVE_THREADS_ASYNCONIZE_HPP
#define REMOVE_THREADS_ASYNCONIZE_HPP

#include <cstddef> // size_t

#include "runnable.hpp"
#include "thread_pool.hpp"

namespace advcpp {

class RemoveThreadAsyncronize : public Runnable {
public:
    RemoveThreadAsyncronize(ThreadPool& a_threadPool ,size_t a_numOfThreads);
    //~RemoveThreadAsyncronize = default;
    //RemoveThreadAsyncronize(const RemoveThreadAsyncronize& a_other) = defualt;
    //RemoveThreadAsyncronize& operator=(const RemoveThreadAsyncronize& a_other) = default;

    virtual void Run();

private:
    ThreadPool& m_threadpool;
    size_t m_numOfThreads;
};

}// advcpp
#endif // REMOVE_THREADS_ASYNCONIZE_HPP