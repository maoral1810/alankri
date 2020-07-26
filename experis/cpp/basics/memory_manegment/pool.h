#ifndef POOL_T_H__
#define POOL_T_H__

#include "page.h"
#include "manager.h"
#include <vector>
using namespace std;

class MemPool_t:public MemManager_t 
{
    public:
        MemPool_t();
        MemPool_t(size_t _capcity);

        virtual size_t Read(void* _rBuffer, size_t _nBytes);
        virtual size_t Read(void* _rBuffer, size_t _pos, size_t _nBytes);
        virtual size_t Write(const void* _wBuffer,size_t _nBytes);
        virtual size_t Write(const void* _wBuffer, size_t _pos, size_t _nBytes);
        virtual ~MemPool_t();
        size_t GetPoolCapacity()const{return (m_pageCapcity * m_vec.size());}

    private:
        size_t m_pageCapcity;
        MemPool_t(const MemPool_t& _pool){;}
        MemPool_t& operator=(MemPool_t& _equalPool){;}
        vector <MemPage_t *> m_vec;
        size_t MyRead(void* _wBuffer, size_t _pos, size_t _nBytes)throw(const char *);
        size_t MyWrite(const void* _wBuffer, size_t _pos, size_t _nBytes)throw(const char *);

        
};

#endif /* POOL_T_H__*/

/* following functionality:
	object of type memPool_t has to be constructed with one empty page 
	copy of objects of type memPool_t is forbidden
	possibility to get and set current position in memPool_t
( take in consideration how many bytes are really written in memPool_t)
	to get following information about Memory Pool  status:
		empty  ?
actual size of the object memPool_t  ( how many bytes really written in pool)
	to read data from Memory Pool – 2 functions :
    c) if position is not given, then from current position
    d) else from position given by user
	to write data into Memory Pool
    c) if position is not given, then from current position
    d) else from position given by user
	to provide possibility to set and to get default size of memory page ( one for all pages ) */