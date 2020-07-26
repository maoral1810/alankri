#include <iostream> // cout 
#include "meter.h"
#include "squreMeter.h"
#include "km.h"
#include "hotel.h"

static void TestMeter(void);
static void TestKM(void);
static void TestSqureMeter(void);
static void TestHotel(void);

using namespace std;

int main(void)
{
    TestMeter();
    TestKM();
    TestSqureMeter();
    TestHotel();
    
    return 0;
}

static void TestMeter(void)
{
    Meter m1(10.2);
    Meter m2(5);
    KM km(2.3);

    cout<< "\n--------------Meter Test---------------\n" << endl;
    cout<< "m1 = "<< m1.GetMeter() << endl;
    cout<< "m2 = "<< m2.GetMeter() << endl;
    
    cout<<"\nmeter * meter:\n" << "m1 * m2 = " << (m1 * m2).GetSqureMeter() << endl; 
    cout<<"\nmeter * factor:\n" << "m1 * 2 = " << (m1 * 2).GetMeter() << endl; 
    cout<<"\nkm * meter:\n" << "m1 * km = " << (m1 * km).GetSqureMeter() << endl;
    
    cout << "m1 = " << m1.GetMeter() << endl;
    m1 = m2;

    cout <<"\nassigment operator:\n"<<"m1 = m2\nm1 = " << m1.GetMeter() << endl;
    cout <<"\noperator -:\n" <<"m1 - m2 = "<< (m1 - m2).GetMeter() << endl;
}

static void TestKM(void)
{
    Meter m1(10.2);
    KM km1(2.3);
    KM km2(10);

    cout<< "\n--------------KM Test---------------\n" << endl;

    cout<< "km1 = "<< km1.GetKm() << endl;
    cout<< "km2 = "<< km2.GetKm() << endl;
    
    cout<<"\n KM * FACTOR:\n" << "km1 * 2 = " << (km1 * 2).GetKm() << endl; 
    
    cout<<"\nkm * meter:\n" << "m1 * km = " << (m1 * km1).GetSqureMeter() << endl;
    
    cout << "\nkm1 = " << km1.GetKm() << endl;
    km1 = km2;

    cout <<"\nassigment operator:\n"<<"km1 = km2\nkm1 = " << km1.GetKm() << endl;
    cout <<"\noperator -:\n" <<"km1 - km2 = "<< (km1 - km2).GetKm() << endl;
}

static void TestSqureMeter(void)
{
    Meter m1(9.99);
    SqureMeter sq(3.33);

    cout<< "\n--------------SqureMeter Test---------------\n" << endl;

    cout <<"m1 = "<< m1.GetMeter()<<"\nsq = "<< sq.GetSqureMeter() << endl;

    cout<<"\n SqureMeter * FACTOR:\n" << "sq * 2 = " << (sq * 2).GetSqureMeter() << endl;
    cout<<"\nSqureMeter / meter:\n" << "Sq / m1 = " << (sq / m1).GetMeter() << endl;
}

static void TestHotel(void)
{
    cout<< "\n--------------Hotel Test---------------\n" << endl;
    Hotel experies(1000, 1000);
    SqureMeter roomSize(12);
    experies.AddRoom(15,roomSize);
    experies.AddRoom(61, roomSize* 3);

    cout<<"Room 15: size = "<< experies.GetRoomSize(15).GetSqureMeter()<< endl;
    cout<<"Room 61: size = "<< experies.GetRoomSize(61).GetSqureMeter()<< endl;
    cout<<"Room not exsist: size = "<< experies.GetRoomSize(100).GetSqureMeter()<< endl;
    experies.AddRoom(61, roomSize * 6);
    cout<<"Room 61: size = "<< experies.GetRoomSize(61).GetSqureMeter()<< endl;

}