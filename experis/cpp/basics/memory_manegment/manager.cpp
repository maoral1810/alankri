#include "manager.h"
using namespace std;

MemManager_t::MemManager_t():m_actualSize(0),m_currentPos(0){}

MemManager_t::MemManager_t(const MemManager_t& _maneger){}

MemManager_t& MemManager_t::operator=(MemManager_t& _equalManeger){}

void MemManager_t::SetPos(size_t _pos)throw (const char *)
{
    // forward and check if current pos is aviable 
    if(_pos > m_actualSize)
    {
        throw("position is bigger then actualSize");
    }

    m_currentPos = _pos;

}

void MemManager_t::SetActualSize(size_t _nBytes)
{
    m_actualSize = _nBytes;
}