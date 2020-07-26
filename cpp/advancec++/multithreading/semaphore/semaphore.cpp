#include <semaphore.h>
#include <errno.h>          // errno
#include <assert.h>
#include "semaphore.hpp" 
#include "semaphore_exceptions.hpp"

namespace experis {

MySemaphore::MySemaphore(int a_semVal)
    : m_SemVal(a_semVal)
{
    if(sem_init(&m_semaphore, 0, m_SemVal))
    {
        switch (errno) {
            case EINVAL:
                throw(InitEINVALExeption);
                break;

            case ENOSYS:
                throw(InitENOSYSExeption);
                break;
            
            default: assert(!"non doucument semaphore init error"); break;
        }
    }
}  

MySemaphore::~MySemaphore() {
    if(sem_destroy(&m_semaphore))
    {
        assert(!"semaphore not valid");
    }
}

void MySemaphore::Wait() {
    if(sem_wait(&m_semaphore)) {
        switch (errno) {
            case EINTR:
                throw(WaitEINTRExeption);
                break;

            case EINVAL:
                throw(WaitEINVALExeption);
                break;
            
            case ETIMEDOUT:
                throw(WaitETIMEDOUTExeption);
                break;

            default: assert(!"non doucument semaphore wait error"); break;
        }
    }
}

void MySemaphore::Post(){
    if(sem_post(&m_semaphore)) {
        switch (errno) {
            case EINVAL:
                throw(postEINVALExeption);
                break;
            case EOVERFLOW:
                throw(postEOVERFLOWExeption);
                break;
            default: assert(!"non doucument semaphore post error"); break;
        }
    }
}

}// namespace experis