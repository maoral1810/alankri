#include "mu_test.h"

#include <iostream>     // cout
#include <queue>
#include <tr1/memory> // shared_ptr

#include "common_utils.hpp"
#include "event.hpp"
#include "agent_information.hpp"
#include "ievent_puller.hpp"
#include "controller_agent.hpp"
#include "event_bus.hpp"
#include "subscribers_list.hpp"
#include "iregistrar.hpp"
#include "disterbution_list.hpp"

using smart_home::ControllerAgent;
using smart_home::AgentInfo;
using smart_home::SafeDistributionList;
using smart_home::IRegistrar;

UNIT(ControllerAgentTest)

    AgentInfo::AGENT_TYPE type = "fire_controler";
    std::string configuration = "configoration info bla bla bla";
    smart_home::Location loc("room_A_3", 56);
    Shared_Ptr<AgentInfo> fireControllerInfo(new AgentInfo("payload","log",loc, type, configuration));

    Shared_Ptr<IRegistrar> a_registrar(new SafeDistributionList(10));

    Shared_Ptr<ControllerAgent> fireController(new ControllerAgent(fireControllerInfo));
 
    fireController->Subscribe(a_registrar, "smoke");
    fireController->Subscribe(a_registrar, "tempature"); 
    
    ASSERT_THAT(1);
END_UNIT

TEST_SUITE(Controller) 
    TEST(ControllerAgentTest)
END_SUITE 