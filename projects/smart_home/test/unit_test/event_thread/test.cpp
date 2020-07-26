#include "mu_test.h"

#include <vector>

#include "ihandle_event.hpp"
#include "isearch.hpp"
#include "common_utils.hpp"
#include "disterbution_list.hpp"
#include "distributer.hpp"
#include "event.hpp"
#include "location.hpp"
#include "time_stamp.hpp"
#include "controller_agent.hpp"
#include "subscribers_list.hpp"
#include "event_middlewere.hpp"
#include "event_channel.hpp"
#include "event_deliver.hpp"
#include "thread.hpp"
#include "thread_group.hpp"
#include "runnable.hpp"

using smart_home::AgentInfo;
using smart_home::Event;
using smart_home::ControllerAgent;
using smart_home::SafeDistributionList;
using smart_home::Distributer;
using smart_home::Location;
using smart_home::IEventPuller;
using smart_home::IEventPusher;
using smart_home::EventBus;
using smart_home::ISearcher;
using smart_home::EventChannel;
using smart_home::EventDeliver;
using::smart_home::Thread;
using::smart_home::TimeStamp;
using::smart_home::EventAddress;
using::smart_home::ThreadGroup;
using::smart_home::Runnable;

void MakeChannels(smart_home::ChannelsQueues& a_channels)
{
    a_channels.reserve(smart_home::NUM_OF_CHANNELS);

    for(size_t i = 0; i < smart_home::NUM_OF_CHANNELS; ++i)
    {
        a_channels.push_back(Shared_Ptr<EventChannel>(new EventChannel()));
    }
}

void MakeThreadGroupTasks(smart_home::ThreadGroupTasks& a_tasks, smart_home::ChannelsQueues& a_channels)
{
    a_tasks.reserve(smart_home::NUM_OF_CHANNELS);

    for(size_t i = 0; i < smart_home::NUM_OF_CHANNELS ; ++i)
    {
        a_tasks.push_back(Shared_Ptr<Runnable>(new EventDeliver(a_channels[i])));
    }
}

UNIT(Event_Thread_Flow_One_Controller)

    Location loc("room_1_A", "3");
    Location controllerLoc("room_999_Z", "0");
    Event::EVENT_TYPE type("door_open");
    const size_t numOfEvent = 100;

    // --- system --- 
    smart_home::ChannelsQueues channels;
    MakeChannels(channels);
    Shared_Ptr<Distributer> distributer(new Distributer(channels));
    Shared_Ptr<SafeDistributionList> dl(new SafeDistributionList);
    Shared_Ptr<IEventPusher> dummy;

    // --- controller ---
    smart_home::ReleventTopics topics;
    topics.reserve(1);
    topics.push_back(Event::EventTopic(loc, type));

    Shared_Ptr<AgentInfo> ligthControllerInfo(new AgentInfo("payload", "log", controllerLoc, "fire_detector", "config"));
    Shared_Ptr<ControllerAgent> lightController(new ControllerAgent(ligthControllerInfo, topics));

    lightController->Connect(dl, dummy);

    // --- Threads ---
    std::vector<Shared_Ptr<Runnable> > threadGroupTasks;
    MakeThreadGroupTasks(threadGroupTasks, channels);
    ThreadGroup threadsGroup(threadGroupTasks);

    Shared_Ptr<Event> eventForTest(new Event(loc, type, TimeStamp()));
    EventAddress data(eventForTest, lightController);
    
    for(size_t i = 0; i < numOfEvent; ++i)
    {
        channels[0]->Push(data);
    }

    distributer->Shutdown();
    // --- assert --- 
    ASSERT_EQUAL(lightController->GetEventHandlerCounter(), numOfEvent);

END_UNIT

TEST_SUITE(Event_Thread)
    TEST(Event_Thread_Flow_One_Controller) 
END_SUITE