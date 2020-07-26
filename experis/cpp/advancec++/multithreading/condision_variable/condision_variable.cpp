#include <pthread.h> // pthread_code_wait
#include "condision_variable.hpp"

namespace experis {

CondVar::CondVar(MyMutex& a_mutex)throw()
    : m_mutex(a_mutex)
{
    m_condVar = PTHREAD_COND_INITIALIZER;
}

CondVar::~CondVar()throw()
{

}

void CondVar::Wait()throw() {
    pthread_cond_wait(&m_condVar, m_mutex.GetMutex());
}

void CondVar::notifyOne()throw() {
    pthread_cond_signal(&m_condVar);
}

void CondVar::notifyAll()throw() {
    pthread_cond_broadcast(&m_condVar);
}

}// namespace experis