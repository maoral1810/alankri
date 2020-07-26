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
#include "initilizer.hpp"

using smart_home::Event;
using smart_home::Location;
using smart_home::SensorAgent;
using smart_home::AgentInfo;
using smart_home::TimeStamp;
using smart_home::EventBus;
using smart_home::IRegistrar;
using smart_home::Initilizer;

UNIT(Initilizer_one_sensor_one_controller)
    
    Initilizer systemInitilizer("configurtion");

    ASSERT_THAT(1);

END_UNIT

TEST_SUITE(initilizer) 
    TEST(Initilizer_one_sensor_one_controller)
END_SUITE 