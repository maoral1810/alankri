#ifndef PAGE_T_H__
#define PAGE_T_H__

#include <stddef.h> // size_t
#include "manager.h"

class MemPage_t:public MemManager_t
{
    public:
        MemPage_t();
        MemPage_t(size_t _capcity);
        virtual ~MemPage_t();
        virtual size_t Read(void* _rBuffer, size_t _nBytes);
        virtual size_t Read(void* _rBuffer, size_t _pos, size_t _nBytes);
        virtual size_t Write(const void* _wBuffer,size_t _nBytes);
        virtual size_t Write(const void* _wBuffer, size_t _nBytes, size_t _pos);
        size_t GetPageCapacity()const{return m_capacity;}

    protected:
        size_t ReadToBuffer(void* _rBuffer, size_t _nBytes, size_t _pos)throw(const char *);
        size_t WriteToPage(const void* _wBuffer, size_t _nBytes, size_t _pos)throw(const char *);

    private:
        static size_t m_defaultCapacity;
        size_t m_capacity;
        char* m_page;
        static void SetDefaultPageSize(size_t _pageSize);
        MemPage_t(const MemPage_t& _page){;} 
        MemPage_t& operator=(const MemPage_t& _equalPage){;}
        char* CreateFrom(size_t _capacity);
};
#endif /* PAGE_T_H__*/
/*
	memPage_t has to hold any data as a stream of bytes 
	object of type memPage_t can be constructed from:
	some default size ( for example 1024 bytes) with the size provided by user
	copy of object of type memPage_t is forbidden
	possibility to get and set current position in memory buffer
	to get following information about page status:
		is page empty 
is page full
actual size of the page ( how many bytes really written in page)
capacity of the page ( length )
	to read data from page – 2 functions :
    a) if position is not given, then from current position
    b) else from position given by user
	to write data into page
    a) if position is not given, then from current position
    b) else from position given by user*/