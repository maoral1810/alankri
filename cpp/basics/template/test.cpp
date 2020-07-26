#include <iostream>
#include <vector>
#include <string> 
#include "building.h"
#include "street.h"
#include "city.h"

int main()
{
    int option;
    int status = 1;
    int ID = 0;
/*     string stringID("non id"); */
    Building_t<int> building;
    Street_t <int, int> street;
    City_t <int, int, int> city;
    
    while(status)
    {
        cout << "Choose option:\n" << endl;
        cout << "1:Set building ID" << endl;
        cout << "2:Set street ID" << endl;
        cout << "3:Set city ID" << endl;
        cout << "4:Get building ID" << endl;
        cout << "5:Get street ID" << endl;
        cout << "6:Get city ID" << endl;
        cout << "7:add building to street" << endl;
        cout << "8:add street to city" << endl;
        cout << "9:Get Building from street" << endl;
        cout << "10:Get street from city" << endl;
        cout << "Any another number - stop" << endl;

        cin >>  option;
        switch (option) 
        {
            case 1:

                cout<<"enter a number for the ID"<< endl;
                cin>> ID;

                building.SetBuildingID(ID);

                cout<< "building ID changed" << endl;
                break;

            case 2:

                cout<<"enter a number for the ID"<<endl;
                cin>> ID;

                street.SetStreetID(ID);

                cout<< "street ID changed" << endl;
                break;

            case 3:

                cout<<"enter a number for the ID"<< endl;
                cin>> ID;

                city.SetCityID(ID);

                cout<< "city ID changed" << endl;
                break;

            case 4:

                ID = building.GetBuildingID();
                cout<< ID << endl;
                break;

            case 5:

                ID = street.GetStreetID();
                cout<< ID << endl;
                break;

            case 6:

                ID = city.GetCityID();
                cout<< ID << endl;
                break;

            case 7:

                street.AddBuilding2Street(building);
                break;

            case 8:

                city.AddStreet(street);
                break;

            case 9:

                cout<<"enter a building ID"<< endl;
                cin>> ID;
                try
                {
                    street.GetBuilding(ID);
                }
                catch(const char *_exep)
                {
                    cout<<_exep<< endl;
                }
                
                break;

            case 10:

                cout<<"enter a street ID"<< endl;
                cin>> ID;
                try
                {
                    city.GetStreet(ID);
                }
                catch(const char *_exep)
                {
                    cout<<_exep<< endl;
                }
                
                break;
            default:
                status = 0;
                cout<< "Goodbye :) "<< endl;
                break;

        }
    }

    
}