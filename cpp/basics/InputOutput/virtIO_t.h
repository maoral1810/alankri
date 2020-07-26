#ifndef VIRTIO_T_H
#define VIRTIO_T_H

#include <stdio.h>
#include <string>
#include <stddef.h> //size_t

using namespace std;


class VirtIO_t
{
    public:
    typedef enum
    {		
        ok_e,
        cant_open_file_e, 
        bad_access_e,
        writeErr_e,
        readErr_e
    }ERR;

    typedef enum
    {
        WO,
        RO,
        WR
    }Premition;

        VirtIO_t():m_status(bad_access_e),m_fd(0){}
        VirtIO_t(const string& _fileName, const string& _mode);//need to do open
        virtual ~VirtIO_t(){Close();}
        
        void Open(const string& _fileName, const string& _mode);
        void Close();
        inline const string& GetPath()const{return m_fileName;}
        inline const string& GetMode()const{return m_mode;}
        inline FILE *GetFd()const{return m_fd;}
        inline ERR GetStatus()const{return m_status;}
        size_t GetPos()const; //throw const char*
        size_t FileLength();//const throw(const char *)
        void SetPos(size_t _newPos);//throw (int)
        Premition GetPremition()const{return m_permition;}
        // all operator func throw(const char *)
        // write to file functions
        virtual VirtIO_t& operator<<(const int& _data) = 0;
        virtual VirtIO_t& operator<<(const unsigned int& _data) = 0;
        virtual VirtIO_t& operator<<(const char& _data) = 0;
        virtual VirtIO_t& operator<<(const unsigned char& _data) = 0;
        virtual VirtIO_t& operator<<(const long& _data) = 0;
        virtual VirtIO_t& operator<<(const unsigned long& _data) = 0;
        virtual VirtIO_t& operator<<(const short& _data) = 0;
        virtual VirtIO_t& operator<<(const unsigned short& _data) = 0;
        virtual VirtIO_t& operator<<(const float& _data) = 0;
        virtual VirtIO_t& operator<<(const double& _data) = 0;
        // read to file functions
        virtual VirtIO_t& operator>>(int& _data) = 0;
        virtual VirtIO_t& operator>>(unsigned int& _data) = 0;
        virtual VirtIO_t& operator>>(char& _data) = 0;
        virtual VirtIO_t& operator>>(unsigned char& _data) = 0;
        virtual VirtIO_t& operator>>(long& _data) = 0;
        virtual VirtIO_t& operator>>(unsigned long& _data) = 0;
        virtual VirtIO_t& operator>>(short& _data) = 0;
        virtual VirtIO_t& operator>>(unsigned short& _data) = 0;
        virtual VirtIO_t& operator>>(float& _data) = 0;
        virtual VirtIO_t& operator>>(double& _data) = 0;

    protected:
        void SetStatus(ERR _newstatus){m_status = _newstatus;}

    private:
        string m_fileName;
        string m_mode;
        ERR m_status;
        FILE *m_fd;
        Premition m_permition;
        VirtIO_t(const VirtIO_t& _name);
        VirtIO_t& operator=(const VirtIO_t& _virt);
};

VirtIO_t::VirtIO_t(const string& _fileName, const string& _mode)//need to do open
{
    m_fileName = _fileName;
    m_mode = _mode;

    Open(_fileName, _mode);
}


void VirtIO_t::Open(const string&_name, const string& _mode)
{
    FILE *fd;

    if(!_mode.compare("r"))
    {
        m_permition = RO;
    }
    else if(!_mode.compare("w"))
    {
        m_permition = WO;
    }
    else
    {
        m_permition = WR;
    }
    
    fd = fopen(_name.c_str(), _mode.c_str());
    
    if(!fd)
    {
        SetStatus(cant_open_file_e);
        return;
    }

    m_fd = fd;
    m_fileName = _name;
    m_mode = _mode;
}

void VirtIO_t::Close()
{
    fclose(m_fd);
    m_fd = 0;
    m_status = bad_access_e;
}

size_t VirtIO_t::FileLength()
{
    if(m_fd == 0 || m_status != ok_e)
    {
        throw("open file before using len");
    }
    fseek(m_fd, -1, SEEK_END);
    return ftell(m_fd);
}

void VirtIO_t::SetPos(size_t _newPos)
{
    if(m_fd == 0 || _newPos > FileLength())
    {
        throw(0);
    }
    
    fseek(m_fd, _newPos, SEEK_SET);
}

size_t VirtIO_t::GetPos()const
{
    if(m_fd)
    {
        return ftell(m_fd);
    }

    throw("fail with get position, fd null");
}
#endif /* VIRTIO_T_H*/
