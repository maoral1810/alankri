#include <iostream>             //cout
#include "read_work.hpp"
#include "cyclic_waitable_q.hpp"

namespace experis {

MyRead::MyRead(int a_iteration , WaitCycQ<int>* a_queue)throw()
    : m_iteration(a_iteration)
    , m_queue(a_queue)
{

}

void MyRead::Run() {
    int data;
    /* for(int i = m_iteration ; i > 0 ; --i) */while(1)
    {
        try {
            m_queue->Dequeue(&data);
            std::cout << data << std::endl;
        }
        catch(...) {
            break;
        }
    }
}

}// namespace experis