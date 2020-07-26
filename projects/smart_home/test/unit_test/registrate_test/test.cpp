#include "mu_test.h"

#include "ihandle_event.hpp"
#include "common_utils.hpp"
#include "distribution_list.hpp"
#include "distributer.hpp"
#include "event.hpp"
#include "location.hpp"
#include "time_stamp.hpp"
#include "controller_agent.hpp"
#include "agent_information.hpp"
#include "subscribers_list.hpp"

using smart_home::AgentInfo;
using smart_home::Event;
using smart_home::ControllerAgent;
using smart_home::SafeDistributionList;
using smart_home::Distributer;
using smart_home::Location;
using smart_home::SubscribersList;

class  TestHandleEvent : public smart_home::IHandleEvent
{
public:

    //TestHandleEvent() = default;
    virtual ~TestHandleEvent(){}

    virtual void HandleEvent(Shared_Ptr<smart_home::Event>& a_event) NOEXCEPTIONS
    {
        UNUSED(a_event);
    }
};

UNIT(Two_Controller_Registration_witout_overlap)
    
    smart_home::ChannelsQueues channels;
    Shared_Ptr<SafeDistributionList> dl(new SafeDistributionList);
    Shared_Ptr<Distributer> distributer(new Distributer(channels));

    Shared_Ptr<TestHandleEvent> controller1(new TestHandleEvent);
    Shared_Ptr<TestHandleEvent> controller2(new TestHandleEvent);

    Event::EventTopic evInfo1(Location("1","1"), "Light");
    Event::EventTopic evInfo2(Location("1","2"), "Light");
    Event::EventTopic evInfo3(Location("1","3"), "Light");

    Event::EventTopic evInfo4(Location("1","4"), "Light");
    Event::EventTopic evInfo5(Location("1","5"), "Light");
    Event::EventTopic evInfo6(Location("2","3"), "Light");
    
    dl->Registrate(controller1,evInfo1);
    dl->Registrate(controller1,evInfo2);
    dl->Registrate(controller1,evInfo3);

    dl->Registrate(controller2,evInfo4);
    dl->Registrate(controller2,evInfo5);
    dl->Registrate(controller2,evInfo6);

    SubscribersList subscriberslist1 = dl->SerachSubscribers(evInfo1);
    SubscribersList subscriberslist2 = dl->SerachSubscribers(evInfo2);
    SubscribersList subscriberslist3 = dl->SerachSubscribers(evInfo3);
    SubscribersList subscriberslist4 = dl->SerachSubscribers(evInfo4);
    SubscribersList subscriberslist5 = dl->SerachSubscribers(evInfo5);
    SubscribersList subscriberslist6 = dl->SerachSubscribers(evInfo6);

    ASSERT_EQUAL(1, subscriberslist1.Size());
    ASSERT_EQUAL(1, subscriberslist2.Size());
    ASSERT_EQUAL(1, subscriberslist3.Size());
    ASSERT_EQUAL(1, subscriberslist4.Size());
    ASSERT_EQUAL(1, subscriberslist5.Size());
    ASSERT_EQUAL(1, subscriberslist6.Size()); 
END_UNIT
 
UNIT(Two_Controller_Registration_with_overlap)
    smart_home::ChannelsQueues channels;
    Shared_Ptr<SafeDistributionList> dl(new SafeDistributionList);
    Shared_Ptr<Distributer> distributer(new Distributer(channels));

    Shared_Ptr<TestHandleEvent> controller1(new TestHandleEvent);
    Shared_Ptr<TestHandleEvent> controller2(new TestHandleEvent);

    Event::EventTopic evInfo1(Location("1","1"), "Light");
    Event::EventTopic evInfo2(Location("2","3"), "Light");
    Event::EventTopic evInfo3(Location("1","3"), "Light");

    Event::EventTopic evInfo4(Location("1","2"), "Light");
    Event::EventTopic evInfo5(Location("1","5"), "Light");
    
    dl->Registrate(controller1,evInfo1);
    dl->Registrate(controller1,evInfo2);
    dl->Registrate(controller1,evInfo3);

    dl->Registrate(controller2,evInfo4);
    dl->Registrate(controller2,evInfo5);
    dl->Registrate(controller2,evInfo2);

    SubscribersList subscriberslist1 = dl->SerachSubscribers(evInfo1);
    SubscribersList subscriberslist2 = dl->SerachSubscribers(evInfo2);
    SubscribersList subscriberslist3 = dl->SerachSubscribers(evInfo3);
    SubscribersList subscriberslist4 = dl->SerachSubscribers(evInfo4);
    SubscribersList subscriberslist5 = dl->SerachSubscribers(evInfo5);

    ASSERT_EQUAL(1, subscriberslist1.Size());
    ASSERT_EQUAL(2, subscriberslist2.Size());
    ASSERT_EQUAL(1, subscriberslist3.Size());
    ASSERT_EQUAL(1, subscriberslist4.Size());
    ASSERT_EQUAL(1, subscriberslist5.Size());

END_UNIT

UNIT(Two_Controller_Registration_one_all_rooms_two_witout_overlap)
    smart_home::ChannelsQueues channels;
    Shared_Ptr<SafeDistributionList> dl(new SafeDistributionList);
    Shared_Ptr<Distributer> distributer(new Distributer(channels));

    Shared_Ptr<TestHandleEvent> controller1(new TestHandleEvent);
    Shared_Ptr<TestHandleEvent> controller2(new TestHandleEvent);

    Event::EventTopic evInfo1(Location("*","1"), "Light");
    Event::EventTopic evInfo2(Location("1","1"), "Light");

    Event::EventTopic evInfo3(Location("2","3"), "Light");
    Event::EventTopic evInfo4(Location("2","4"), "Light");
    
    dl->Registrate(controller1,evInfo1);
    dl->Registrate(controller2,evInfo3);
    dl->Registrate(controller2,evInfo4);

    SubscribersList subscriberslist1 = dl->SerachSubscribers(evInfo2);
    SubscribersList subscriberslist2 = dl->SerachSubscribers(evInfo3);
    SubscribersList subscriberslist3 = dl->SerachSubscribers(evInfo4);

    ASSERT_EQUAL(subscriberslist1.Size(), 1);
    ASSERT_EQUAL(subscriberslist2.Size(), 1);
    ASSERT_EQUAL(subscriberslist3.Size(), 1);

END_UNIT

UNIT(Two_Controller_Registration_one_all_rooms_two_with_overlap)
    smart_home::ChannelsQueues channels;
    Shared_Ptr<SafeDistributionList> dl(new SafeDistributionList);
    Shared_Ptr<Distributer> distributer(new Distributer(channels));

    Shared_Ptr<TestHandleEvent> controller1(new TestHandleEvent);
    Shared_Ptr<TestHandleEvent> controller2(new TestHandleEvent);

    Event::EventTopic evInfo1(Location("*","1"), "Light");

    Event::EventTopic evInfo2(Location("1","1"), "Light");
    Event::EventTopic evInfo3(Location("2","1"), "Light");
    
    dl->Registrate(controller1,evInfo1);
    dl->Registrate(controller2,evInfo2);
    dl->Registrate(controller2,evInfo3);

    SubscribersList subscriberslist1 = dl->SerachSubscribers(evInfo2);
    SubscribersList subscriberslist2 = dl->SerachSubscribers(evInfo3);

    ASSERT_EQUAL(subscriberslist1.Size(), 2);
    ASSERT_EQUAL(subscriberslist2.Size(), 2);

END_UNIT

UNIT(Two_Controller_Registration_one_and_two_diffrent_floor_same_rooms)
    smart_home::ChannelsQueues channels;
    Shared_Ptr<SafeDistributionList> dl(new SafeDistributionList);
    Shared_Ptr<Distributer> distributer(new Distributer(channels));

    Shared_Ptr<TestHandleEvent> controller1(new TestHandleEvent);
    Shared_Ptr<TestHandleEvent> controller2(new TestHandleEvent);

    Event::EventTopic evInfo1(Location("1","1"), "Light");
    Event::EventTopic evInfo2(Location("2","1"), "Light");

    Event::EventTopic evInfo3(Location("1","2"), "Light");
    Event::EventTopic evInfo4(Location("2","2"), "Light");
    
    dl->Registrate(controller1,evInfo1);
    dl->Registrate(controller1,evInfo2);
    dl->Registrate(controller2,evInfo3);
    dl->Registrate(controller2,evInfo4);

    SubscribersList subscriberslist1 = dl->SerachSubscribers(evInfo1);
    SubscribersList subscriberslist2 = dl->SerachSubscribers(evInfo2);
    SubscribersList subscriberslist3 = dl->SerachSubscribers(evInfo3);
    SubscribersList subscriberslist4 = dl->SerachSubscribers(evInfo4);

    ASSERT_EQUAL(subscriberslist1.Size(), 1);
    ASSERT_EQUAL(subscriberslist2.Size(), 1);
    ASSERT_EQUAL(subscriberslist3.Size(), 1);
    ASSERT_EQUAL(subscriberslist4.Size(), 1);
END_UNIT

UNIT(Two_Controller_Registration_one_and_two_same_floor_same_rooms_diffrent_type)
    smart_home::ChannelsQueues channels;
    Shared_Ptr<SafeDistributionList> dl(new SafeDistributionList);
    Shared_Ptr<Distributer> distributer(new Distributer(channels));

    Shared_Ptr<TestHandleEvent> controller1(new TestHandleEvent);
    Shared_Ptr<TestHandleEvent> controller2(new TestHandleEvent);

    Event::EventTopic evInfo1(Location("1","1"), "Light");
    Event::EventTopic evInfo2(Location("2","1"), "Light");

    Event::EventTopic evInfo3(Location("1","1"), "Fire");
    Event::EventTopic evInfo4(Location("2","1"), "Fire");
    
    dl->Registrate(controller1,evInfo1);
    dl->Registrate(controller1,evInfo2);
    dl->Registrate(controller2,evInfo3);
    dl->Registrate(controller2,evInfo4);

    SubscribersList subscriberslist1 = dl->SerachSubscribers(evInfo1);
    SubscribersList subscriberslist2 = dl->SerachSubscribers(evInfo2);
    SubscribersList subscriberslist3 = dl->SerachSubscribers(evInfo3);
    SubscribersList subscriberslist4 = dl->SerachSubscribers(evInfo4);

    ASSERT_EQUAL(subscriberslist1.Size(), 1);
    ASSERT_EQUAL(subscriberslist2.Size(), 1);
    ASSERT_EQUAL(subscriberslist3.Size(), 1);
    ASSERT_EQUAL(subscriberslist4.Size(), 1);
END_UNIT

UNIT(Two_Controller_Registration_one_and_two_same_floor_same_rooms_same_type)
    smart_home::ChannelsQueues channels;
    Shared_Ptr<SafeDistributionList> dl(new SafeDistributionList);
    Shared_Ptr<Distributer> distributer(new Distributer(channels));

    Shared_Ptr<TestHandleEvent> controller1(new TestHandleEvent);
    Shared_Ptr<TestHandleEvent> controller2(new TestHandleEvent);

    Event::EventTopic evInfo1(Location("1","1"), "Light");
    Event::EventTopic evInfo2(Location("2","1"), "Light");

    Event::EventTopic evInfo3(Location("1","1"), "Light");
    Event::EventTopic evInfo4(Location("2","1"), "Light");
    
    dl->Registrate(controller1,evInfo1);
    dl->Registrate(controller1,evInfo2);
    dl->Registrate(controller2,evInfo3);
    dl->Registrate(controller2,evInfo4);

    SubscribersList subscriberslist1 = dl->SerachSubscribers(evInfo1);
    SubscribersList subscriberslist2 = dl->SerachSubscribers(evInfo2);
    SubscribersList subscriberslist3 = dl->SerachSubscribers(evInfo3);
    SubscribersList subscriberslist4 = dl->SerachSubscribers(evInfo4);

    ASSERT_EQUAL(subscriberslist1.Size(), 2);
    ASSERT_EQUAL(subscriberslist2.Size(), 2);
    ASSERT_EQUAL(subscriberslist3.Size(), 2);
    ASSERT_EQUAL(subscriberslist4.Size(), 2);
END_UNIT

UNIT(Two_Controller_Registration_one_all_rooms_and_floors_two_only_same_floor_same_type)
    smart_home::ChannelsQueues channels;
    Shared_Ptr<SafeDistributionList> dl(new SafeDistributionList);
    Shared_Ptr<Distributer> distributer(new Distributer(channels));

    Shared_Ptr<TestHandleEvent> controller1(new TestHandleEvent);
    Shared_Ptr<TestHandleEvent> controller2(new TestHandleEvent);

    Event::EventTopic evInfo1(Location("*","*"), "Light");
    Event::EventTopic evInfo2(Location("1","1"), "Light");

    Event::EventTopic evInfo3(Location("4","1"), "Light");
    Event::EventTopic evInfo4(Location("5","1"), "Light");
    
    dl->Registrate(controller1,evInfo1);
    dl->Registrate(controller1,evInfo2);
    dl->Registrate(controller2,evInfo3);
    dl->Registrate(controller2,evInfo4);

    SubscribersList subscriberslist1 = dl->SerachSubscribers(evInfo2);
    SubscribersList subscriberslist2 = dl->SerachSubscribers(evInfo3);
    SubscribersList subscriberslist3 = dl->SerachSubscribers(evInfo4);

    ASSERT_EQUAL(subscriberslist1.Size(), 2);
    ASSERT_EQUAL(subscriberslist2.Size(), 2);
    ASSERT_EQUAL(subscriberslist3.Size(), 2);
END_UNIT

UNIT(Two_Controller_Registration_one_all_floors_spacific_room_two_diffrent_room_same_floor_same_type)
    smart_home::ChannelsQueues channels;
    Shared_Ptr<SafeDistributionList> dl(new SafeDistributionList);
    Shared_Ptr<Distributer> distributer(new Distributer(channels));

    Shared_Ptr<TestHandleEvent> controller1(new TestHandleEvent);
    Shared_Ptr<TestHandleEvent> controller2(new TestHandleEvent);

    Event::EventTopic evInfo1(Location("1","*"), "Light");
    Event::EventTopic evInfo2(Location("2","*"), "Light");

    Event::EventTopic evInfo3(Location("1","6"), "Light");
    Event::EventTopic evInfo4(Location("2","19"), "Light");
    
    dl->Registrate(controller1,evInfo1);
    dl->Registrate(controller1,evInfo2);
    dl->Registrate(controller2,evInfo3);
    dl->Registrate(controller2,evInfo4);

    SubscribersList subscriberslist1 = dl->SerachSubscribers(evInfo3);
    SubscribersList subscriberslist2 = dl->SerachSubscribers(evInfo4);

    ASSERT_EQUAL(subscriberslist1.Size(), 2);
    ASSERT_EQUAL(subscriberslist2.Size(), 2);
END_UNIT

UNIT(Two_Controller_Registration_one_to_all_two_not)   // (* : * : *) + small overlap
    smart_home::ChannelsQueues channels;
    Shared_Ptr<SafeDistributionList> dl(new SafeDistributionList);
    Shared_Ptr<Distributer> distributer(new Distributer(channels));

    Shared_Ptr<TestHandleEvent> controller1(new TestHandleEvent);
    Shared_Ptr<TestHandleEvent> controller2(new TestHandleEvent);

    Event::EventTopic evInfo1(Location("*","*"), "*");
    Event::EventTopic evInfo2(Location("2","1"), "Light");

    Event::EventTopic evInfo3(Location("1","6"), "Light");
    Event::EventTopic evInfo4(Location("2","19"), "Fire");
    
    dl->Registrate(controller1, evInfo1);
    dl->Registrate(controller1, evInfo2);
    dl->Registrate(controller2, evInfo3);
    dl->Registrate(controller2, evInfo4);

    SubscribersList subscriberslist1 = dl->SerachSubscribers(evInfo3);
    SubscribersList subscriberslist2 = dl->SerachSubscribers(evInfo4);

    ASSERT_EQUAL(subscriberslist1.Size(), 2);
    ASSERT_EQUAL(subscriberslist2.Size(), 2);

END_UNIT
    
UNIT(Two_Controller_Registration_one_to_all_two_to_all)//(* : * : *) + all overlap
    smart_home::ChannelsQueues channels;
    Shared_Ptr<SafeDistributionList> dl(new SafeDistributionList);
    Shared_Ptr<Distributer> distributer(new Distributer(channels));

    Shared_Ptr<TestHandleEvent> controller1(new TestHandleEvent);
    Shared_Ptr<TestHandleEvent> controller2(new TestHandleEvent);

    Event::EventTopic evInfo1(Location("*","*"), "*");
    Event::EventTopic evInfo2(Location("2","1"), "Light");

    Event::EventTopic evInfo3(Location("2","1"), "Fire");
    Event::EventTopic evInfo4(Location("*","*"), "*");
    
    dl->Registrate(controller1, evInfo1);
    dl->Registrate(controller1, evInfo2);
    dl->Registrate(controller2, evInfo3);
    dl->Registrate(controller2, evInfo4);

    SubscribersList subscriberslist1 = dl->SerachSubscribers(evInfo2);
    SubscribersList subscriberslist2 = dl->SerachSubscribers(evInfo3);

    ASSERT_EQUAL(subscriberslist1.Size(), 3);
    ASSERT_EQUAL(subscriberslist2.Size(), 3);
END_UNIT 

TEST_SUITE(Regitration)
    TEST(Two_Controller_Registration_witout_overlap) //(ROOM : FLOOR : TYPE)
    TEST(Two_Controller_Registration_with_overlap)   //(ROOM : FLOOR : TYPE) + overlap
    TEST(Two_Controller_Registration_one_all_rooms_two_witout_overlap)// (* : FLOOR : TYPE)
    TEST(Two_Controller_Registration_one_all_rooms_two_with_overlap) //  (* : FLOOR : TYPE) + overlap
    TEST(Two_Controller_Registration_one_and_two_diffrent_floor_same_rooms) // (ROOM : FLOOR : TYPE) Floor Change same room
    TEST(Two_Controller_Registration_one_and_two_same_floor_same_rooms_diffrent_type) // (ROOM : FLOOR : TYPE) type change
    TEST(Two_Controller_Registration_one_and_two_same_floor_same_rooms_same_type) 
    TEST(Two_Controller_Registration_one_all_rooms_and_floors_two_only_same_floor_same_type)//(* : * : TYPE) + overlap
    TEST(Two_Controller_Registration_one_all_floors_spacific_room_two_diffrent_room_same_floor_same_type)//(ROOM : * : TYPE) + overlap
    TEST(Two_Controller_Registration_one_to_all_two_not)   //(* : * : *) + small overlap
    TEST(Two_Controller_Registration_one_to_all_two_to_all)//(* : * : *) + all overlap
END_SUITE




