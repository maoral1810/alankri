#include <iostream>
#include <stdio.h>
#include <string> 
#include "virtIO_t.h"
#include "binIO_t.h"
#include "assciIO_t.h"

void CreateFile(char _type);

void write(VirtIO_t* _filePtr);
void read(VirtIO_t* _filePtr);

using namespace std;

int main()
{
    char type;

    while (1)
    {
        cout<<endl<<"please enter a file type b[inary file] / a[ssci file]" <<endl;
        cin>>type;

        if(type == 'b' || type == 'a')
        {
            CreateFile(type);
        }
        else
        {
            break;
        }       
    }

    cout<<"goodbye :)"<<endl;
}


void write(VirtIO_t* _filePtr)
{
    char type;
    int status = 1;
    
    while(status)
    {
        cout<<"choose type: i[nt],s[hort],c[har],l[ong],f[loat],d[ouble],b[reak]"<<endl;
        cin>>type;
        cout<<endl<<"write<<";
        
        switch (type)
        {
            case 'i':
            {
                int i = 0;
                cin>>i;
                *_filePtr << i;
                *_filePtr << ' ';
                break;
            }   
            case 'f':
            {
                float f = 0;
                cin>>f;
                *_filePtr << f;
                *_filePtr << ' ';
                break;
            }
            case 'd':
            {
                double d = 0;
                cin>>d;
                *_filePtr << d;
                *_filePtr << ' ';
                break;
            }
            case 's':
            {
                short s = 0;
                cin>>s;
                *_filePtr << s;
                *_filePtr << ' ';
                break;
            }
            case 'l':
            {
                long l = 0;
                cin>>l;
                *_filePtr << l;
                *_filePtr << ' ';
                break;
            }
            case 'c':
            {
                char c = 0;
                cin>>c;
                *_filePtr << c;
                *_filePtr << ' ';
                break;
            }

            default:status = 0; break;
        }
    }
}

void read(VirtIO_t* _filePtr)
{
    char type;
    int status = 1;
    
    while(status)
    {
        cout<<"choose type: i[nt],s[hort],c[har],l[ong],f[loat],d[ouble],b[reak]"<<endl;
        cin>>type;
        char c; 

        switch (type)
        {
            case 'i':
            {
                int i = 0;
                *_filePtr >> i;
                cout<<i<<endl;
                *_filePtr >> c;
                break;
            }   
            case 'f':
            {
                float f = 0;
                *_filePtr >> f;
                cout<<f<<endl;
                *_filePtr >> c;
                break;
            }
            case 'd':
            {
                double d = 0;
                *_filePtr >> d;
                cout<<d<<endl;
                *_filePtr >> c;
                break;
            }
            case 's':
            {
                short s = 0;
                *_filePtr >> s;
                cout<<s<<endl;
                *_filePtr >> c;
                break;
            }
            case 'l':
            {
                long l = 0;
                *_filePtr >> l;
                cout<<l<<endl;
                *_filePtr >> c;
                break;
            }
            case 'c':
            {
                char c = 0;
                *_filePtr >> c;
                cout<<c<<endl;
                *_filePtr >> c;
                break;
            }

            default:status = 0; break;
        }
    }

}

void CreateFile(char _type)
{
    string fileName;
    string mode;
    char option;
    int status = 1;
    VirtIO_t *filePtr;

    cout<< "please enter file name(string)"<<endl;
    cin>>fileName;
    cout<<"mode(r,r+,w,w+,a,a+)"<<endl;
    cin>>mode;

    if(_type == 'a')
    {
        filePtr = new AssciIO_t(fileName, mode);
    } 
    else
    {
        filePtr = new BinIO_t(fileName, mode);
    }
    
    while(status)
    {
        cout<< "entar option: w|r|g(et position)|s(etpos)|p(remition)|![get Status]"<<endl;
        cin>>option;
        switch (option)
        {
            case 'w':
            {
                write(filePtr);
                break;
            }
            case 'r':
            {
                read(filePtr);
                break;
            }
            case 'g':
            {
                cout<< "Postion: "<< filePtr->GetPos() <<endl;
                break;
            }
            
            case 's':
            {
                size_t pos;
                cout<< "enter Postion: "<< endl;
                cin>>pos;
                filePtr->SetPos(pos);
                break; 
            }
            case '!':
            {
                int stat = filePtr->GetStatus();
                cout<<"Status: ";

                switch (stat)
                {
                case 0:
                    cout<<"ok_e"<<endl;
                    break;
                case 1:
                    cout<<"cant_open_file_e"<<endl;
                    break;
                case 2:
                    cout<<"bad_access_e"<<endl;
                    break;
                case 3:
                    cout<<"writeErr_e"<<endl;
                    break;
                case 4:
                    cout<<"readErr_e"<<endl;
                    break;
                default:
                    break;
                }
                break; 
            }
            case 'p':
            {
                int premition = filePtr->GetPremition();
                cout<<"premition: ";
                switch (premition)
                {
                    case 0:
                        cout<<"write only"<<endl;
                        break;
                    case 1:
                        cout<<"read only"<<endl;
                        break;
                    case 2:
                        cout<<"write & read"<<endl;
                        break;
                    default:break;
                }
            }
            default: status = 0; break;
        }
    }
}
