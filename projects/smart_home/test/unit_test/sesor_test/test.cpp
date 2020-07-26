#include "mu_test.h"

#include <iostream>     // cout
#include <queue>
#include <tr1/memory> // shared_ptr

#include "common_utils.hpp"
#include "event.hpp"
#include "agent_information.hpp"
#include "ievent_pusher.hpp"
#include "sensor_agent.hpp"
#include "event_bus.hpp"
#include "iregistrar.hpp"

using smart_home::Event;
using smart_home::Location;
using smart_home::SensorAgent;
using smart_home::AgentInfo;
using smart_home::TimeStamp;
using smart_home::EventBus;
using smart_home::IRegistrar;

UNIT(Create_Event)
    Location loc("room_A_1","2");
    Event::EVENT_TYPE type = "TEMPATURE";
    TimeStamp time;
    Event event(loc, type, time);

    Event event2(loc, type, time);

    ASSERT_EQUAL(1, event.GetID());
    ASSERT_EQUAL(2, event2.GetID());
    ASSERT_EQUAL("2", event.GetLocation().GetFloor());
    ASSERT_EQUAL("room_A_1", event.GetLocation().GetRoom());
    ASSERT_EQUAL("TEMPATURE" , event.GetType());  
    std::cout << "event time: " << event.GetTime().GetHours() << ":" << event.GetTime().GetMinutes()
    << ":" <<  event.GetTime().GetMinutes() << '\n';

END_UNIT

UNIT(Agent_Information)
    AgentInfo::AGENT_TYPE type = "sprinkler";
    std::string configuration = "configoration info bla bla bla";
    Location loc("room_B_22", "99");
    std::string log = "lights";

    Shared_Ptr<AgentInfo> agent( new AgentInfo("payload", log, loc, type, configuration));

    ASSERT_EQUAL(1, agent->GetID());
    ASSERT_EQUAL("99", agent->GetLocation().GetFloor());
    ASSERT_EQUAL("room_B_22", agent->GetLocation().GetRoom());
    ASSERT_EQUAL( "configoration info bla bla bla", agent->GetConfiguration());
    ASSERT_EQUAL( "sprinkler", agent->GetType());

END_UNIT

UNIT(Create_Sensor_Check_Event_Push_And_Push)
    Event::EVENT_TYPE sensorType("Smoke");
    const size_t eventBusCapacity = 100;
    Location sensorLoc("room_1_A", "1");
    size_t numOfEvents = 10;

    Shared_Ptr<IRegistrar> reg;

    //System
    Shared_Ptr<EventBus> eventBus(new EventBus(eventBusCapacity));
    // sensor
    {
        Shared_Ptr<AgentInfo> smokeSensorInfo (new AgentInfo("room-5-B-smoke", "smoke_detector", sensorLoc, "smoke_detector", "")); 
        Shared_Ptr<SensorAgent> smokeSensor(new SensorAgent(smokeSensorInfo, sensorType, numOfEvents));

        smokeSensor->Connect(reg ,eventBus);
    }

    Shared_Ptr<Event> curEvent;

    for(size_t i = 0; i < numOfEvents; ++i)
    {
        eventBus->PullEvent(curEvent);
        ASSERT_THAT(curEvent->GetType() ==  sensorType);
        ASSERT_THAT(curEvent->GetLocation() == sensorLoc);
    }

END_UNIT

TEST_SUITE(Sensor) 
    TEST(Create_Event)
    TEST(Agent_Information)
    TEST(Create_Sensor_Check_Event_Push_And_Push)
END_SUITE 