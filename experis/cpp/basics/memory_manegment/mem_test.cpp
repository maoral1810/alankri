#include <iostream>
#include <string.h>
#include "Interactive_test.h"
#include "manager.h"
#include "pool.h"
#include "page.h"

using namespace std;

int main(void)
{
	int cont = 1;			// trigger to stop loop	
	unsigned int option;
    MemPool_t *myPool = 0;

    char buffer[100];
    char readBuffer[100];

	while (cont) 
    {
        size_t size = 6;
        size_t byteRes = 0;
        size_t pos = 0;
        size_t bytes = 0;
        char c;

		cout << "Choose option:\n" << endl;
        cout << "1:Create Pool" << endl;
		cout << "2:Read" << endl;
        cout << "3:Write" << endl;
        cout << "4:GetPoolPosition" << endl;
        cout << "5:GetPoolCapacity" << endl;
		cout << "Any another number - stop" << endl;

		cin >>  option;

		switch (option) 
        {
			case 1:
            {
                if(myPool)
                {
                    cout << "you have a pool allready" << endl;
                    break;
                }
                cout<<"\ndo you want to enter capcity for page(defualt = 6) y/n?"<< endl;
                cin>> c;

                if(c == 'y')  
                {
                    cout<< "enter page size"<< endl;
                    cin>> size;
                }
                
                myPool = new MemPool_t(size);

                cout<<"Pool create! page size = "<< size << "\n\n";

                break;
            }

			case 2:
            {
                memset(readBuffer,'\0',100);
                if(!myPool)
                {
                    cout<< "error !!!! please create a pool"<< endl;
                    break;
                }
                pos = myPool->GetPos();

                cout<< "\nplease insert how mach bytes you want to read from buffer"<<endl;
                cin>> bytes;

                cout<< "\nare you want to read from current pos (y/n)"<<endl;
                cin >> c;

                if(c != 'y')
                {
                    cout<< "please enter a position between 0 - " << myPool->GetActualSize() << endl;
                    cin>> pos;
                }

                try
                {
                    byteRes = myPool->Read(readBuffer,pos, bytes); 
                }
                catch(const char *exep)
                {
                    cout<< exep<<endl;
                }
                if(byteRes != bytes)
                {
                    cout << "you want to read "<< bytes << 
                    " but function can read only " << byteRes << " bytes" << endl;
                }
                else
                {
                    cout << "read sucsses with "<< byteRes << " bytes"<<endl;
                }
                
                cout<<"i read :" << readBuffer << endl;
                
                break;
            }
            case 3:
                if(!myPool)
                {
                    cout<< "error !!!! please create a pool"<< endl;
                    break;
                }
                pos = myPool->GetPos();
                cout<< "\nplease insert how mach bytes you want to write to buffer"<<endl;
                cin>> bytes;

                cout<< "\nare you want to write from current pos (y/n)"<<endl;
                cin >> c;

                if(c != 'y')
                {
                    cout<< "please enter a position between 0 - " << myPool->GetActualSize() << endl;
                    cin>> pos;
                }
                cout << "Type:" << endl;
                cin >> buffer;
                
                try
                {
                    byteRes = myPool->Write(buffer,pos,bytes); 
                }
                catch(const char *exep)
                {
                    cout<< exep<<endl;
                }
                
                if(byteRes != bytes)
                {
                    cout << "you want to write "<< bytes << 
                    " but function can write only " << byteRes << " bytes" << endl;
                }
                else
                {
                    cout << "write sucsses with "<< byteRes << " bytes"<<endl;
                }
                
                break;

            case 4:
                if(!myPool)
                {
                    cout<< "error !!!! please create a pool"<< endl;
                    break;
                }
                cout<< "position = " << myPool->GetPos() << endl;

                break;

            case 5:
                if(!myPool)
                {
                    cout<< "error !!!! please create a pool"<< endl;
                    break;
                }
                
                cout<< "capacity = " << myPool->GetPoolCapacity() << endl;

                break;
			default: cont = 0;	break;
		}
	}

	return 0;
}

