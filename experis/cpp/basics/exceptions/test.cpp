#include <iostream>
#include "exeption.h"

using namespace std;

int main(void)
{
    size_t i = 0;

    for(i = 0; i < 10; ++i)
    {
        try
        {
            if(i % 3 == 0)
            {
                throw TExeption_t<int> (i, "the number divide by 3 witout reminder",__LINE__,__FILE__);
            }
        }
        catch(TExeption_t<int> _exception)
        {
            cout<<"in line:"<< _exception.GetLine() << " in file:" << 
            _exception.GetFile()<<" with value:"<< i <<" :"<< _exception.GetDecription()<< endl;
        }
    }   

    return 0;
}