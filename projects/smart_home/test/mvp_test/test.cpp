#include "mu_test.h"

#include "event_middlewere.hpp"
#include "event.hpp"
#include "ievent_pusher.hpp"
#include "ievent_puller.hpp"
#include "sensor_agent.hpp"
#include "event_bus.hpp"
#include "controller_agent.hpp"
#include "distribution_list.hpp"
#include "event_middlewere.hpp"
#include "thread.hpp"
#include "distributer.hpp"
#include "thread_group.hpp"
#include "event_deliver.hpp"
#include "runnable.hpp"
#include "initilizer.hpp"
#include "server.hpp"

#include <unistd.h>

using smart_home::SensorAgent;
using smart_home::ControllerAgent;
using smart_home::EventMiddlewere;
using smart_home::AgentInfo;
using smart_home::Event;
using smart_home::EventBus;
using smart_home::Location;
using smart_home::TimeStamp;
using smart_home::IEventPusher;
using smart_home::IEventPuller;
using smart_home::Thread;
using smart_home::SafeDistributionList;
using smart_home::Distributer;
using smart_home::EventChannel;
using smart_home::ThreadGroup;
using smart_home::EventDeliver;
using smart_home::Runnable;
using smart_home::Initilizer;
using smart_home::Server;

// TODO make sensor from so
// TODO make controller from so

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

UNIT(one_sensor_agent_one_controller)
    Location loc("room_1_A", "3");
    Location controllerLoc("room_999_Z", "0");
    
    const size_t eventBusCapacity = 20;
    
    // --- system --- 
    smart_home::ChannelsQueues channels;
    MakeChannels(channels);
    Shared_Ptr<EventBus> eventBus(new EventBus(eventBusCapacity));
    Shared_Ptr<Distributer> distributer(new Distributer(channels));
    Shared_Ptr<SafeDistributionList> dl(new SafeDistributionList);
    Shared_Ptr<EventMiddlewere> eventMiddlewere(new EventMiddlewere(eventBus, distributer, dl));

    // --- controller ---
    Shared_Ptr<AgentInfo> ligthControllerInfo(new AgentInfo("payload", "log", controllerLoc, "fire_detector", "room_1_A~3~light~"));
    Shared_Ptr<ControllerAgent> lightController(new ControllerAgent(ligthControllerInfo));
    lightController->Connect(dl, eventBus);

    // --- Threads ---
    std::vector<Shared_Ptr<Runnable> > threadGroupTasks;
    MakeThreadGroupTasks(threadGroupTasks, channels);
    ThreadGroup threadsGroup(threadGroupTasks);
    Thread middlewereThread(eventMiddlewere.get());
    
    // --- sensors ---
    Shared_Ptr<AgentInfo> doorSensorInfo (new AgentInfo("room-1-a-Door", "zigLock", loc, "ligth_detector", "light^")); 
    Shared_Ptr<SensorAgent> doorSensor(new SensorAgent(doorSensorInfo));
    doorSensor->Connect(dl, eventBus);

    // --- join ---
    eventBus->Shutdown();
    middlewereThread.Join();
    distributer->Shutdown();
    threadsGroup.JoinAll();
    
    doorSensor->Disconnect();

    // --- assert --- 
    ASSERT_PASS();
END_UNIT

UNIT(two_sensor_agent_one_controller)
    Location loc1("room_1_A", "1");
    Location loc2("room_1_A", "3");
    Location controllerLoc("room_999_Z", "0");
    const size_t eventBusCapacity = 20;
    
    // --- system --- 
    smart_home::ChannelsQueues channels;
    MakeChannels(channels);
    Shared_Ptr<EventBus> eventBus(new EventBus(eventBusCapacity));
    Shared_Ptr<Distributer> distributer(new Distributer(channels));
    Shared_Ptr<SafeDistributionList> dl(new SafeDistributionList);
    Shared_Ptr<EventMiddlewere> eventMiddlewere(new EventMiddlewere(eventBus, distributer, dl));

    // --- controller ---
    Shared_Ptr<AgentInfo> fireControllerInfo(new AgentInfo("payload", "log", controllerLoc, "fire_detector", "room_1_A~1~smoke~room_1_A~3~temperature~"));
    Shared_Ptr<ControllerAgent> fireController(new ControllerAgent(fireControllerInfo));

    fireController->Connect(dl, eventBus);
    // --- Threads ---
    std::vector<Shared_Ptr<Runnable> > threadGroupTasks;
    MakeThreadGroupTasks(threadGroupTasks, channels);
    ThreadGroup threadsGroup(threadGroupTasks);
    Thread middlewereThread(eventMiddlewere.get());
    
    // --- sensors ---
    Shared_Ptr<AgentInfo> smokeSensorInfo (new AgentInfo("room-1-a-smoke", "smoke_detector", loc1, "smoke_detector", "smoke^")); 
    Shared_Ptr<SensorAgent> smokeSensor(new SensorAgent(smokeSensorInfo));

    Shared_Ptr<AgentInfo> temperatureSensorInfo (new AgentInfo("room-1-a-temperature", "temperature_detector", loc2, "temperature_detector", "temperature^")); 
    Shared_Ptr<SensorAgent> temperatureSensor(new SensorAgent(temperatureSensorInfo));
    
    smokeSensor->Connect(dl, eventBus);
    temperatureSensor->Connect(dl, eventBus);

    // --- join ---
    eventBus->Shutdown();
    middlewereThread.Join();
    distributer->Shutdown();
    threadsGroup.JoinAll();
    
    smokeSensor->Disconnect();
    temperatureSensor->Disconnect();

    // --- assert --- 
    ASSERT_PASS();
END_UNIT


UNIT(four_sensor_agent_two_controllers)
    Location loc1("room_1_A", "1");
    Location loc2("room_1_A", "1");
    Location loc3("room_5_B", "12");
    Location loc4("room_1_A", "1");
    Location controllerLoc("room_5_B", "0");

    const size_t eventBusCapacity = 20;
    //const size_t numOfSensors = 4;
    
    // --- system --- 
    smart_home::ChannelsQueues channels;
    MakeChannels(channels);
    Shared_Ptr<EventBus> eventBus(new EventBus(eventBusCapacity));
    Shared_Ptr<Distributer> distributer(new Distributer(channels));
    Shared_Ptr<SafeDistributionList> dl(new SafeDistributionList);
    Shared_Ptr<EventMiddlewere> eventMiddlewere(new EventMiddlewere(eventBus, distributer, dl));

    // --- controller ---
    Shared_Ptr<AgentInfo> fireControllerInfo(new AgentInfo("payload", "log", controllerLoc, "fire_detector", "room_1_A~1~smoke~room_1_A~1~temperature~room_5_B~12~smoke~"));
    Shared_Ptr<ControllerAgent> fireController(new ControllerAgent(fireControllerInfo));

    Shared_Ptr<AgentInfo> ligthControllerInfo(new AgentInfo("payload", "log", controllerLoc, "light_detector", "room_1_A~1~open_door~"));
    Shared_Ptr<ControllerAgent> lightController(new ControllerAgent(ligthControllerInfo));

    fireController->Connect(dl, eventBus);
    lightController->Connect(dl, eventBus);

    // --- Threads ---
    std::vector<Shared_Ptr<Runnable> > threadGroupTasks;
    MakeThreadGroupTasks(threadGroupTasks, channels);
    ThreadGroup threadsGroup(threadGroupTasks);
    Thread middlewereThread(eventMiddlewere.get());
    
    // --- sensors ---
    
    Shared_Ptr<AgentInfo> smokeSensor1Info (new AgentInfo("room-1-A-smoke", "smoke_detector", loc1, "smoke_detector", "smoke^")); 
    Shared_Ptr<SensorAgent> smokeSensor1(new SensorAgent(smokeSensor1Info));

    Shared_Ptr<AgentInfo> temperatureSensorInfo (new AgentInfo("room-1-A-temperature", "temperature_detector", loc2, "temperature_detector", "temperature^")); 
    Shared_Ptr<SensorAgent> temperatureSensor(new SensorAgent(temperatureSensorInfo));

    Shared_Ptr<AgentInfo> smokeSensor2Info (new AgentInfo("room-5-B-smoke", "smoke_detector", loc3, "smoke", "smoke^")); 
    Shared_Ptr<SensorAgent> smokeSensor2(new SensorAgent(smokeSensor1Info));

    Shared_Ptr<AgentInfo> doorSensorInfo (new AgentInfo("room-1-A-Door", "door_detector", loc4, "light_detector", "open_door^")); 
    Shared_Ptr<SensorAgent> doorSensor(new SensorAgent(doorSensorInfo));
    
    smokeSensor1->Connect(dl, eventBus);
    smokeSensor2->Connect(dl, eventBus);
    temperatureSensor->Connect(dl, eventBus);
    doorSensor->Connect(dl, eventBus);
    
    // Disconnet
    eventBus->Shutdown();
    middlewereThread.Join();
    distributer->Shutdown();
    threadsGroup.JoinAll();

    smokeSensor1->Disconnect();
    smokeSensor2->Disconnect();
    temperatureSensor->Disconnect();
    doorSensor->Disconnect();


    // --- assert --- 
    ASSERT_PASS();

END_UNIT

UNIT(one_sensor_agent_two_controllers)
    Location sensorLoc("room_1_A", "1");
    Location fireControllerLoc("room_5_B", "0");
    Location acControllerLoc("room_10_Z", "-5");

    const size_t eventBusCapacity = 20;
    
    // --- system --- 
    smart_home::ChannelsQueues channels;
    MakeChannels(channels);
    Shared_Ptr<EventBus> eventBus(new EventBus(eventBusCapacity));
    Shared_Ptr<Distributer> distributer(new Distributer(channels));
    Shared_Ptr<SafeDistributionList> dl(new SafeDistributionList);
    Shared_Ptr<EventMiddlewere> eventMiddlewere(new EventMiddlewere(eventBus, distributer, dl));

    // --- controller ---

    Shared_Ptr<AgentInfo> fireControllerInfo(new AgentInfo("payload", "log", fireControllerLoc, "fire_detector", "room_1_A~1~temperature~"));
    Shared_Ptr<ControllerAgent> fireController(new ControllerAgent(fireControllerInfo));

    Shared_Ptr<AgentInfo> acControllerInfo(new AgentInfo("payload", "log", acControllerLoc, "fire_detector", "room_1_A~1~temperature~"));
    Shared_Ptr<ControllerAgent> acController(new ControllerAgent(acControllerInfo));

    fireController->Connect(dl, eventBus);
    acController->Connect(dl, eventBus);

    // --- Threads ---
    std::vector<Shared_Ptr<Runnable> > threadGroupTasks;
    MakeThreadGroupTasks(threadGroupTasks, channels);
    ThreadGroup threadsGroup(threadGroupTasks);
    Thread middlewereThread(eventMiddlewere.get());
    
    // --- sensors ---
    Shared_Ptr<AgentInfo> temperatureSensorInfo (new AgentInfo("room-1-A-temperature", "temperature_detector", sensorLoc, "temperature", "temperature^")); 
    Shared_Ptr<SensorAgent> temperatureSensor(new SensorAgent(temperatureSensorInfo));
    
    temperatureSensor->Connect(dl, eventBus);

    // --- join ---
    
    eventBus->Shutdown();
    middlewereThread.Join();
    distributer->Shutdown();
    threadsGroup.JoinAll();

    temperatureSensor->Disconnect();
    fireController->Disconnect();
    acController->Disconnect();


    // --- assert --- 
/*     ASSERT_EQUAL(fireController->GetEventHandlerCounter(), numOfEvents);
    ASSERT_EQUAL(acController->GetEventHandlerCounter(), numOfEvents); */
    ASSERT_PASS();
END_UNIT


UNIT(initilizer)

    Shared_Ptr<Initilizer> systemInitilizer(new Initilizer("configurtion"));
    Shared_Ptr<Server> server(new Server(systemInitilizer));

    server->ConnectSystem();
    server->DisconnectSystem();
    
    ASSERT_PASS();
END_UNIT

UNIT(server_three_sensors_two_controllers)
    Shared_Ptr<Initilizer> systemInitilizer(new Initilizer("configurtion"));
    Shared_Ptr<Server> server(new Server(systemInitilizer));

    server->ConnectSystem();
    ASSERT_EQUAL(systemInitilizer->GetAgents().size(), 5);
    
    server->DisconnectSystem();
END_UNIT

TEST_SUITE(MVP_Test) 
    TEST(one_sensor_agent_one_controller)
    TEST(two_sensor_agent_one_controller)
    TEST(four_sensor_agent_two_controllers)
    TEST(one_sensor_agent_two_controllers)
    TEST(initilizer)
    TEST(server_three_sensors_two_controllers)
END_SUITE 