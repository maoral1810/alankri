#include <iostream>
#include <vector>
#include "pool.h"
#include "manager.h"
#include "page.h"

using namespace std;

MemPool_t::MemPool_t()
{
    MemPage_t *newPage = new MemPage_t;
    m_vec.push_back(newPage);
    m_pageCapcity = m_vec[0]->GetPageCapacity();
}

MemPool_t::MemPool_t(size_t _capcity)
{
    MemPage_t *newPage = new MemPage_t(_capcity);
    m_vec.push_back(newPage);
    m_pageCapcity = _capcity;
}

MemPool_t::~MemPool_t()
{
    size_t vectorSize = m_vec.size();

    for (size_t i = 0; i < vectorSize; ++i)
    {
        delete m_vec[i]; 
    }
}

size_t MemPool_t::Read(void* _rBuffer, size_t _nBytes)
{
    return MyRead(_rBuffer, GetPos(), _nBytes);
}

size_t MemPool_t::Read(void* _rBuffer, size_t _pos, size_t _nBytes)
{
    return MyRead(_rBuffer, _pos, _nBytes);
}

size_t MemPool_t::Write(const void* _wBuffer, size_t _nBytes)
{
    return MyWrite(_wBuffer, GetPos(), _nBytes);
}

size_t MemPool_t::Write(const void* _wBuffer, size_t _pos, size_t _nBytes)
{
    return MyWrite(_wBuffer, _pos, _nBytes);
}
//---------------------- private functions -----------------------------
size_t MemPool_t::MyRead(void* _Buffer, size_t _pos, size_t _nBytes)throw(const char *)
{
    size_t readBytes = 0;
    size_t page = _pos / m_pageCapcity;
    size_t sumBytes = 0;
    size_t curPos = _pos % m_pageCapcity;

    if(!_Buffer || _pos > GetActualSize())
    {
        return 0;
    }
    
    _nBytes = (GetActualSize() - _pos) < _nBytes ? (GetActualSize() - _pos):_nBytes;
    
    SetPos(_pos);
    
    while(0 != _nBytes)
    {
        readBytes = m_vec[page++]->Read(_Buffer, curPos ,_nBytes);
        _Buffer = (char *)_Buffer + readBytes;
        _nBytes -= readBytes;
        sumBytes += readBytes;
        curPos = 0;
    }
    
    SetPos(_pos + sumBytes);

    return sumBytes;
}
size_t MemPool_t::MyWrite(const void* _Buffer, size_t _pos, size_t _nBytes)throw(const char *)
{
    size_t writeBytes = 0;
    size_t page = _pos / m_pageCapcity;
    size_t sumBytes = 0;
    size_t pageToAdd = 0;
    size_t totalCapacity = 0;
    size_t totalBytes = 0;
    size_t curPos = _pos % m_pageCapcity;
    
    if(!_Buffer)
    {
        throw(_Buffer);
    }

    totalCapacity = m_pageCapcity * m_vec.size();
    totalBytes = _pos + _nBytes;

    if(totalBytes > totalCapacity)
    {
        pageToAdd = ((totalBytes - totalCapacity) / m_pageCapcity) + 1;
    }

    while(pageToAdd--)
    {
        MemPage_t *newPage = new MemPage_t(m_pageCapcity);
        // TODO throw alloc exepsion (how match page are created for delete)
        m_vec.push_back(newPage);
    }


    while(_nBytes != 0)
    {
        writeBytes = m_vec[page++]->Write(_Buffer, _nBytes, curPos);
        _Buffer = (char *)_Buffer + writeBytes;
        _nBytes -= writeBytes;
        sumBytes += writeBytes;
        SetPos(_pos + writeBytes);

        curPos = 0;
    }

    SetActualSize(_pos + sumBytes);

    return sumBytes;
}

