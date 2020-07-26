#ifndef SERVER_HPP
#define SERVER_HPP

#include "initilizer.hpp"
#include "common_utils.hpp"
#include "thread_group.hpp"

namespace smart_home {

class Server {
public:
    Server(Shared_Ptr<Initilizer>& a_systemInfo);
    //~Server() = default;

    void ConnectSystem();
    void DisconnectSystem();

private:
    Shared_Ptr<Initilizer> m_systemInfo;
    Shared_Ptr<ThreadGroup> m_channelsThreads;
    Shared_Ptr<Thread> m_middelewereThread;
};

}// namespace smart_home

#endif //__RUNNABLE_HPP__