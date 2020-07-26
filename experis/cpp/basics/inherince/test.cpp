#include <iostream>
#include "Interactive_test.h"


using namespace std;

int main()
{
	int cont = 1;			// trigger to stop loop	
	unsigned int option;


	
	while (cont) {
		cout << "Choose option: " << endl;
		cout << "private functionlity: " << endl;
        cout << "1: GetSpeed " << endl;
		cout << "2: Accelerate " << endl;
		cout << "3: reduceSpeed  " << endl;
        cout << "4: GetName " << endl;
        cout << "5: GetCapcity" << endl;
        cout << "6: Set new capcity " << endl;
		cout << "Any another number - stop " << endl;

		cin >>  option;
		switch (option) 
        {
			case 1:
	   			cout << endl << pCar.GetSpeed() << endl; break;
			case 2:
				pCar.Accelerate();  break;
			case 3:
				pCar.reduceSpeed();  break;
            case 4:
                cout << pCar.GetName() << endl; break;
            case 5:
              cout << pCar.GetCapcity() << endl; break;
            case 6:
              cout<< "Enter a new capcity"<<endl;
              cin>> newCapcity;
              pCar.SetDefaultCapcity(newCapcity); break;  
			default: cont = 0;	break;
		}
	}

	return 0;
}

