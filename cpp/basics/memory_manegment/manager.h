#ifndef MANAGER_T_H__
#define MANAGER_T_H__

#include <stddef.h> // size_t
using namespace std;

class MemManager_t
{
    public:
        MemManager_t();
        virtual ~MemManager_t(){;}
        inline size_t GetPos()const{return m_currentPos;}
        inline size_t GetActualSize()const{return m_actualSize;}
        inline bool IsEmpty()const{return (m_actualSize == 0);}
        virtual size_t Read(void* _rBuffer, size_t _nBytes) = 0;
        virtual size_t Read(void* _rBuffer, size_t _pos, size_t _nBytes) = 0;
        virtual size_t Write(const void* _wBuffer,size_t _nBytes) = 0;
        virtual size_t Write(const void* _wBuffer, size_t _nBytes, size_t _pos) = 0;

    protected:
        void SetPos(size_t _pos) throw (const char *);
        void SetActualSize(size_t _nBytes);
        
    private:
        size_t m_actualSize;
        size_t m_currentPos;
        MemManager_t(const MemManager_t& _maneger); // copy is fobiden  
        MemManager_t& operator=(const MemManager_t& _equalManeger);       
};

#endif /* MANAGER_T_H__*/
/*
	object of type memManager_t  can 't be constructed  
	possibility to get and set current position in memory 
	to get following information about memory  status:
		memory  empty ?
actual size of the memory  ( how many bytes really written in memory)
	to read data from memory – 2 functions:
    a)  if position is not given, then from current position
    b) else from position given by user
	to write data into memory – 2 functions:
    a) if position is not given, then from current position
    b) else from position given by user
*/