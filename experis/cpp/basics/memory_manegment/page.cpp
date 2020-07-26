#include <iostream> // cout
#include <stddef.h> // size_t
#include <string.h> // memcpy
#include "page.h"
#include "manager.h"
using namespace std;

size_t MemPage_t::m_defaultCapacity = 6;

MemPage_t :: MemPage_t():MemManager_t(),m_capacity(m_defaultCapacity)
{
    m_page = CreateFrom(m_capacity);
}
 
MemPage_t::MemPage_t(size_t _capacity):MemManager_t(),m_capacity(_capacity)
{
    m_page = CreateFrom(m_capacity);
}

MemPage_t::~MemPage_t()
{
    delete[] m_page;
}

size_t MemPage_t::Read(void* _rBuffer, size_t _nBytes)
{
    if(!_rBuffer)
    {
        return 0;
    }

    return ReadToBuffer(_rBuffer, _nBytes, GetPos());
}
size_t MemPage_t::Read(void* _rBuffer, size_t _pos, size_t _nBytes)
{
    if(!_rBuffer || _pos > GetActualSize())
    {
        return 0;
    }

    return ReadToBuffer(_rBuffer, _nBytes, _pos);

}
size_t MemPage_t::Write(const void* _wBuffer, size_t _nBytes)
{
    if(!_wBuffer)
    {
        return 0;
    }

    return WriteToPage(_wBuffer, _nBytes, GetPos());
}

size_t MemPage_t::Write(const void* _wBuffer, size_t _nBytes, size_t _pos)
{
    if(!_wBuffer || _pos > GetActualSize() || _pos >= m_capacity)
    {
        return 0;
    }
    // TODO SetPos
    return WriteToPage(_wBuffer, _nBytes, _pos);
}

//--------------------- PRIVATE FUNCTIONS ------------------------------
char* MemPage_t::CreateFrom(size_t _capacity)
{
    return (new char(m_capacity));  
}

void MemPage_t::SetDefaultPageSize(size_t _pageSize)
{
    m_defaultCapacity = _pageSize;
}

size_t MemPage_t::WriteToPage(const void* _wBuffer, size_t _nBytes, size_t _pos) throw(const char *)
{
    if(_pos + _nBytes > m_capacity)
    {
        _nBytes = m_capacity - _pos; 
    }

    memcpy(m_page, _wBuffer, _nBytes);
    SetActualSize(_pos + _nBytes);
    
    SetPos(_pos + _nBytes);
     
    return _nBytes;
}

size_t MemPage_t::ReadToBuffer(void* _rBuffer, size_t _nBytes, size_t _pos)throw(const char *)
{
    size_t actualRBytes = _nBytes;
    
    if(m_capacity - _pos < _nBytes)
    {
        _nBytes = m_capacity - _pos; 
    }

    memcpy(_rBuffer, m_page, actualRBytes);
    
    SetPos(_pos + _nBytes);
    
    return _nBytes;
}