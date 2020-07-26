#ifndef BINIO_T_H
#define BINIO_T_H

#include <stdio.h> //FILE, write, read
#include <string>
#include <stddef.h> //size_t
#include "virtIO_t.h"

using namespace std;

class BinIO_t:public VirtIO_t
{
    public:
        BinIO_t():VirtIO_t(),m_buf(0), m_write(0){}
        BinIO_t(const string& _fileName, const string& _mode):VirtIO_t(_fileName,_mode),m_buf(0), m_write(0){}
        virtual ~BinIO_t(){}
        
        // all operator func throw(const char *)
        // write to file functions
        virtual BinIO_t& operator<<(const int& _data){return MyWrite(&_data, sizeof(int));}
        virtual BinIO_t& operator<<(const unsigned int& _data){return MyWrite(&_data, sizeof(unsigned int));}
        virtual BinIO_t& operator<<(const char& _data){return MyWrite(&_data, sizeof(char));}
        virtual BinIO_t& operator<<(const unsigned char& _data){return MyWrite(&_data, sizeof(unsigned char));}
        virtual BinIO_t& operator<<(const long& _data){return MyWrite(&_data, sizeof(long));}
        virtual BinIO_t& operator<<(const unsigned long& _data){return MyWrite(&_data, sizeof(unsigned long));}
        virtual BinIO_t& operator<<(const short& _data){return MyWrite(&_data,sizeof(short));}
        virtual BinIO_t& operator<<(const unsigned short& _data){return MyWrite(&_data, sizeof(unsigned short));}
        virtual BinIO_t& operator<<(const float& _data){return MyWrite(&_data, sizeof(float));}
        virtual BinIO_t& operator<<(const double& _data){return MyWrite(&_data, sizeof(double));}
        BinIO_t& operator<<(const void* _buffer);
        // read to file functions
        virtual BinIO_t& operator>>(int& _data){return MyRead(&_data, sizeof(int));}
        virtual BinIO_t& operator>>(unsigned int& _data){return MyRead(&_data, sizeof(unsigned int));}
        virtual BinIO_t& operator>>(char& _data){return MyRead(&_data, sizeof(char));}
        virtual BinIO_t& operator>>(unsigned char& _data){return MyRead(&_data, sizeof(unsigned char));}
        virtual BinIO_t& operator>>(long& _data){return MyRead(&_data, sizeof(long));}
        virtual BinIO_t& operator>>(unsigned long& _data){return MyRead(&_data, sizeof(unsigned long));}
        virtual BinIO_t& operator>>(short& _data){return MyRead(&_data,sizeof(short));}
        virtual BinIO_t& operator>>(unsigned short& _data){return MyRead(&_data, sizeof(unsigned short));}
        virtual BinIO_t& operator>>(float& _data){return MyRead(&_data, sizeof(float));}
        virtual BinIO_t& operator>>(double& _data){return MyRead(&_data, sizeof(double));}
        BinIO_t& operator>>(void* _buffer);

        void operator,(size_t _len);//throw const char * 

    private:
        void *m_buf;
        bool m_write;

        template<class TYPE>
        BinIO_t& MyWrite(const TYPE* _data, size_t _dataSize);//throw(const char *);
        
        template<class TYPE>
        BinIO_t& MyRead(TYPE*_data, size_t _dataSize);//throw(const char *);
        
        BinIO_t(const BinIO_t& _binIO);
        BinIO_t& operator=(const BinIO_t& _binIO);
};

template<class TYPE>
BinIO_t& BinIO_t::MyWrite(const TYPE* _data, size_t _dataSize)
{
    size_t bytes;   
    
    if(GetPremition() == RO)
    {   
        SetStatus(bad_access_e);
        throw("fail with write(invalid mode)");
    }

    bytes = fwrite(_data, _dataSize , 1, GetFd());
    if(ferror(GetFd()))
    {
        SetStatus(writeErr_e);
        throw("failed with write!ferror");
    }

    return *this;
}

template<class TYPE>
BinIO_t& BinIO_t::MyRead(TYPE*_data, size_t _dataSize)
{
    size_t bytes;
    if(GetPremition() == WO)
    {   
        SetStatus(bad_access_e);
        throw("fail with read(invalid mode)");
    }

    bytes = fread(_data, _dataSize, 1, GetFd());
    if(ferror(GetFd()))
    {
        SetStatus(readErr_e);
        throw("failed with read!ferror");
    }

    return *this;
}

BinIO_t& BinIO_t::operator<<(const void* _buffer)
{
    if(!_buffer)
    {
        throw("Invalid Buffer");
    }
    m_buf = (void *)_buffer;
    m_write = 1;
}

BinIO_t& BinIO_t::operator>>(void* _buffer)
{
    if(!_buffer)
    {
        throw("Invalid Buffer");
    }
    m_buf = _buffer;
    m_write = 0;
}

void BinIO_t::operator,(size_t _len)
{
    if(!m_buf)
    {
        SetStatus(bad_access_e);
        throw("int operator , buffer null");
    }
    if(m_write)
    {
        MyWrite(m_buf,_len);
    }
    else
    {
        MyRead(m_buf,_len);
    }
}


#endif /* BINIO_T_H*/