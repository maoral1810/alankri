#ifndef ASSCIIO_T_H
#define ASSCIIO_T_H

#include <stdio.h>//FILE, fprintf, fscanf
#include <string>
#include <stddef.h> //size_t
#include "virtIO_t.h"

using namespace std;

class AssciIO_t:public VirtIO_t
{
    public:
        AssciIO_t():VirtIO_t(){;}
        AssciIO_t(const string& _fileName, const string& _mode):VirtIO_t(_fileName,_mode){;}
        virtual ~AssciIO_t(){}
        // all operator func throw(const char *)
        // write to file functions
        virtual AssciIO_t& operator<<(const int& _data){return MyWrite(_data,"%d");}
        virtual AssciIO_t& operator<<(const unsigned int& _data){return MyWrite(_data, "%ud");}
        virtual AssciIO_t& operator<<(const char& _data){return MyWrite(_data, "%c");}
        virtual AssciIO_t& operator<<(const unsigned char& _data){return MyWrite(_data, "%uc");}
        virtual AssciIO_t& operator<<(const long& _data){return MyWrite(_data, "%l");}
        virtual AssciIO_t& operator<<(const unsigned long& _data){return MyWrite(_data, "%ld");}
        virtual AssciIO_t& operator<<(const short& _data){return MyWrite(_data, "%d");}
        virtual AssciIO_t& operator<<(const unsigned short& _data){return MyWrite(_data, "%ud");}
        virtual AssciIO_t& operator<<(const float& _data){return MyWrite(_data, "%f");}
        virtual AssciIO_t& operator<<(const double& _data){return MyWrite(_data, "%lf");}
        // read to file functions
        virtual AssciIO_t& operator>>(int& _data){return MyRead(_data,"%d");}
        virtual AssciIO_t& operator>>(unsigned int& _data){return MyRead(_data, "%ud");}
        virtual AssciIO_t& operator>>(char& _data){return MyRead(_data, "%c");}
        virtual AssciIO_t& operator>>(unsigned char& _data){return MyRead(_data, "%uc");}
        virtual AssciIO_t& operator>>(long& _data){return MyRead(_data, "%l");};
        virtual AssciIO_t& operator>>(unsigned long& _data){return MyRead(_data, "%ld");}
        virtual AssciIO_t& operator>>(short& _data){return MyRead(_data, "%d");}
        virtual AssciIO_t& operator>>(unsigned short& _data){return MyRead(_data, "%ud");}
        virtual AssciIO_t& operator>>(float& _data){return MyRead(_data, "%f");}
        virtual AssciIO_t& operator>>(double& _data){return MyRead(_data, "%lf");}

    private:
        AssciIO_t(const AssciIO_t& _binIO);
        AssciIO_t& operator=(const AssciIO_t& _binIO);

        template<class TYPE>
        AssciIO_t& MyWrite(const TYPE& _data, const char* _format);//throw(const char *);
        
        template<class TYPE>
        AssciIO_t& MyRead(TYPE& _data, const char* _format);//throw(const char *);
};

template<class TYPE>
AssciIO_t& AssciIO_t::MyWrite(const TYPE& _data, const char* _format)
{
    if(GetPremition() == RO)
    {   
        SetStatus(bad_access_e);
        throw("fail with write(invalid mode)");
    }

    fprintf(GetFd(), _format, _data);
    fflush(GetFd());
    if(ferror(GetFd()))
    {
        SetStatus(writeErr_e);
        throw("failed with write!ferror");
    }

    return *this;
}

template<class TYPE>
AssciIO_t& AssciIO_t::MyRead(TYPE& _data, const char* _format)
{
    if(GetPremition() == WO)
    {   
        SetStatus(bad_access_e);
        throw("fail with read(invalid mode)");
    }

    fscanf(GetFd(), _format, &_data);
    if(ferror(GetFd()))
    {
        SetStatus(writeErr_e);
        throw("failed with read!ferror");
    }

    return *this;
}
#endif //ASSCIIO_T_H