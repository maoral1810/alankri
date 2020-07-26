#include <iostream>
#include <string.h>
#include <vector>
#include <list>
#include "Interactive_test.h"
#include "tContainer_t.h"

#define TYPE int
using namespace std;

int main(void)
{
/*     TContainer_t<int, list<int *> > lst;
	TContainer_t<int ,vector<int *>> vec; */
    bool Cflag = 10;
    int cont = 1;			// trigger to stop loop	
	unsigned int option;
    TContainer_t<TYPE ,vector<TYPE *> > container;
    cout<<"please choose container-> vector:0 list:1"<<endl;
/*     cin>>Cflag;
    
    if(Cflag)
    {
        TContainer_t<int ,list<int *> >* container = new TContainer_t<int ,list<int *> >();
    }
    else
    {
        TContainer_t<int ,vector<int *> >* container = new TContainer_t<int ,vector<int *> >();
    } */
 
	while (cont) 
    {
		cout << "Choose option:\n" << endl;
        cout << "1:IsEmpty:" << endl;
		cout << "2:Size" << endl;
        cout << "3:Insert" << endl;
        cout << "4:LastElement" << endl;
        cout << "5:FirstElement" << endl;
        cout << "6:FindSpecific:" << endl;
		cout << "7:Remove" << endl;
        cout << "8:RemoveAll" << endl;
        cout << "9:RemoveAndDelete" << endl;
        cout << "10:RemoveAndDeleteAll" << endl;
        cout << "11:GetByIndex[]" << endl;
        cout << "12:SetByIndex[]" << endl;
		cout << "Any another number - stop" << endl;

		cin >>  option;

		switch (option) 
        {
            case 1:
            {
                container.IsEmpty() ? cout<< "container is empty"<< endl 
                                    :cout<< "cointainer isn't empty"<<endl;
             
                break;
            }

			case 2:
            {
                cout<< "Size: " << container.Size() << endl;               
                break;
            }

            case 3:
            {   
                int data = 0;
                int *toStore = 0;
                cout<< "please enter a number to store in container"<<endl;
                cin>> data;
                toStore = new int(data);
                try
                {
                    container.Insert(toStore);
                }
                catch(int exp)
                {
                    if(!exp)
                    {
                        cout<< "failed to insert! data NULL" << endl;
                    }
                }
                
                

                break;
            }    

            case 4:
                {
                    const int *last = container.LastElement();
                    last ? cout<< "Last Element: "<< *last << endl : 
                    cout<< "Empty container"<<endl;
                }
                break;

            case 5:
                {
                    const int *first = container.FirstElement();
                    first ? cout<< "First Element: "<< *first << endl : 
                    cout<< "Empty container"<<endl;
                break;
                }

            case 6:
            {
                int tofind;
                cout<< "please enter a number to Find"<<endl;
                cin>>tofind;

                int *data = new int(tofind);

                if (*data == *(container.FindSpecific(tofind)))
                {
                    cout<< "Data Found"<<endl;
                }
                else
                {
                    cout<< "Data not Found"<<endl;
                }

                delete data;
                break;
            }

			case 7:
            {
                int data;

                cout<< "please enter data to Remove" << endl;
                cin>> data;

                try
                {
                    if(container.Remove(data))
                    {
                        cout<< "element removed!"<< endl;
                    }
                }
                catch(int exep)
                {
                    cout<< "Remove Failed! Data not found"<< endl; 
                }
                   
                break;
            }

            case 8:
            {
                container.RemoveAll();
                cout<< "container Remove all elemnts"<< endl;
                break;
            }

            case 9:
            {
                int data;

                cout<< "please enter data to RemoveAndDelete" << endl;
                cin>> data;

                try
                {
                    container.RemoveAndDelete(data);
                    cout<< "element removed!"<< endl;
                    
                }
                catch(int exep)
                {
                    cout<< "RemoveAndDelete Failed! Data not found"<< endl; 
                }
                      
                break;
            }

            case 10:
            {
                container.RemoveAndDeleteAll();
                cout<< "all elements are removed and delete"<< endl;
                break;
            }

            case 11:
            {
                size_t size = container.Size();
                size_t index;
                cout<< "please enter index for get between 0 - "<< size <<endl;
                cin>> index;
                cout<< container[index] << endl;
                break;
            }

            case 12:
            {
                size_t size = container.Size();
                size_t index = -1;
                int data;
                int *toInsert;
                while(index > size)
                {
                    cout<< "please enter index for get between 0 - "<< size <<endl;
                    cin>> index;
                }
            
               /*   cout<<"please enter data to insert"<<endl;
                cin>>data;
                toInsert = new int (data);
                container[index] = toInsert; */
                cout<< *container[index] << endl;
                break;
            }
			default: cont = 0;	break;
		}
	}

	return 0;
}

