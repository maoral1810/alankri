#include <cmath>    //sqrt
#include "write_work.hpp"

namespace experis{

static bool IsPrime(int a_number)throw();

MyWrite::MyWrite(unsigned int a_from , unsigned int a_to, WaitCycQ<int>* a_queue)throw()
    : m_from(a_from)
    , m_to(a_to)
    , m_queue(a_queue)
{

}

void MyWrite::Run() {
    for(int i = m_from; i < m_to ; ++i)
    {
        if(IsPrime(i))
        {
            try {
                m_queue->Enqueue(i);
            }
            catch(...){
                // ?????
                break;
            }
        }
    }
}

static bool IsPrime(int a_number)throw() {
    size_t i;
    if(a_number == 2) {
        return true;
    }
    if(a_number % 2 == 0) {
        return false;
    }
    for(i = 3; i <= sqrt(a_number); i += 2) {
        if(a_number % i == 0) {
            return false;
        }
    }
    return true;
}

}// namespace experis