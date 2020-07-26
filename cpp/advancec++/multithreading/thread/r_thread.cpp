#include "r_thread.hpp"

namespace experis {

void RThread::DoWork() {
    m_runFunc->Run();
}

}// namespace experis
