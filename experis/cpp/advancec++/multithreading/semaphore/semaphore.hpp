#ifndef __SEMAPHORE_HPP__
#define __SEMAPHORE_HPP__

#include <semaphore.h> 

namespace experis {

class MySemaphore {
public:
    MySemaphore(int a_semVal);
    ~MySemaphore();

    //API Function

    void Wait();
    void Post();

private:
    MySemaphore(const MySemaphore& a_other);
    MySemaphore& operator=(const MySemaphore& a_other);

    sem_t m_semaphore;
    int m_SemVal;
};

}// namespace experis


#endif //__SEMAPHORE_HPP__
