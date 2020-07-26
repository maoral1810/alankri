#include "server.hpp"
#include "initilizer.hpp"
#include "thread_group.hpp"
#include "event_deliver.hpp"

namespace smart_home
{

static void MakeThreadGroupTasks(smart_home::ThreadGroupTasks& a_tasks, smart_home::ChannelsQueues& a_channels);

Server::Server(Shared_Ptr<Initilizer>& a_systemInfo)
    : m_systemInfo(a_systemInfo)
    , m_channelsThreads()
    , m_middelewereThread()
{}

void Server::ConnectSystem()
{
    AgentsCont& agents = m_systemInfo->GetAgents();
    Shared_Ptr<SafeDistributionList> dl = m_systemInfo->GetDistributionList();
    Shared_Ptr<EventBus> eventBus = m_systemInfo->GetEventBus();
    Shared_Ptr<EventMiddlewere> eventMiddlewere = m_systemInfo->GetMiddlewere();
    
    std::vector<Shared_Ptr<Runnable> > threadGroupTasks;
    MakeThreadGroupTasks(threadGroupTasks, m_systemInfo->GetChannels());
    m_channelsThreads = Shared_Ptr<ThreadGroup>(new ThreadGroup(threadGroupTasks));
    
    for(size_t i = 0; i < agents.size(); ++i)
    {
        agents[i]->Connect(dl, eventBus);
    }

    Shared_Ptr<Thread> middlewereThread(new Thread(eventMiddlewere.get()));
    m_middelewereThread = middlewereThread;
}

void Server::DisconnectSystem()
{
    Shared_Ptr<EventBus> eventBus = m_systemInfo->GetEventBus();
    Shared_Ptr<Distributer> distributer = m_systemInfo->GetDistributer(); 

    eventBus->Shutdown();
    m_middelewereThread->Join();
    distributer->Shutdown();
    m_channelsThreads->JoinAll();

    AgentsCont& agents = m_systemInfo->GetAgents();
    for(size_t i = 0; i < agents.size(); ++i)
    {
        agents[i]->Disconnect();
    }
}

static void MakeThreadGroupTasks(smart_home::ThreadGroupTasks& a_tasks, smart_home::ChannelsQueues& a_channels)
{
    a_tasks.reserve(smart_home::NUM_OF_CHANNELS);

    for(size_t i = 0; i < smart_home::NUM_OF_CHANNELS ; ++i)
    {
        a_tasks.push_back(Shared_Ptr<Runnable>(new EventDeliver(a_channels[i])));
    }
}


} // namespace smart_home
