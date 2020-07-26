#ifndef VECTOR_T_H__
#define VECTOR_T_H__
#include <stddef.h> //size_t
#include <string>
#include "continer_t.h"

template <class ELEM>

class Vector_t: public Container_t<ELEM>
{
    Vector_t();
    Vector_t(size_t _vecSize);
    virtual ~Vector_t();
    Vector_t(const Vector_t& _cont);
    Vector_t& operator=(const Vector_t& _cont);

    virtual Container_t<ELEM>& Append(const ELEM* _element, size_t _index);
    virtual Container_t<ELEM>& Prepend(const ELEM* _element, size_t _index);
    virtual ELEM* Find(const ELEM& _elem)const;
    virtual size_t Index(const ELEM& _elem)const;
    virtual void Insert(const ELEM& _elem);
    virtual ELEM* Remove(const ELEM& _elem) throw (const char *);
    virtual void RemoveAll();
    virtual void RemoveAndDelete(const ELEM& _elem)throw (const char *);
    virtual void RemoveAndDeleteAll();
    size_t GetCapacity()const{return m_capacity;}

    private:
        ELEM **m_vec;
        size_t m_size;     /* original allcated space for items           */
        size_t m_capacity;  /* actual allocated space for item             */

        void MoveVectorRight(size_t _index);
        void MoveVectorLeft(size_t _index);
        void Realloc();
};

template <class ELEM>
Vector_t<ELEM>::Vector_t():m_size(0), m_capacity(32)
{
    m_vec = new ELEM*[m_capacity];
    Container_t<ELEM>::AddContainer();
}

template <class ELEM>
Vector_t<ELEM>::~Vector_t()
{
    m_size = 0;
    delete[] m_vec;
    Container_t<ELEM>::SubContanier();
}

template <class ELEM>
Vector_t<ELEM>::Vector_t(size_t _vecSize):m_capacity(_vecSize),m_size(0)
{
    m_vec = new ELEM*[m_capacity];
    Container_t<ELEM>::AddContainer();
}

template <class ELEM>
Container_t<ELEM>& Vector_t<ELEM>::Append(const ELEM* _element, size_t _index)
{
    size_t i = Container_t<ELEM>::Count();
    
    if(_index > m_capacity || Index > Container_t<ELEM>::Count())
    {
        throw("index not valid");
    }

    if(m_capacity == Container_t<ELEM>::Count())
    {
        ELEM** newVec = new ELEM*[m_capacity * 2];//need to realloc
        newVec = m_vec;
        delete m_vec;
        m_vec = newVec;
    }

    MoveVectorRight(_index);

    m_vec[_index] = _element;
    Container_t<ELEM>::AddElement(); 
}

template <class ELEM>
Container_t<ELEM>& Vector_t<ELEM>::Prepend(const ELEM* _element, size_t _index)
{
    Append(_index - 1, _element);
}

template <class ELEM>
ELEM* Vector_t<ELEM>::Find(const ELEM& _elem)const
{
    size_t i = 0;

    while(i < this->Count())
    {
        if(m_vec[i] == _elem)
        {
            return m_vec[i];
        }
    }

    return 0;
}

template <class ELEM>
size_t Vector_t<ELEM>::Index(const ELEM& _elem)const
{
    size_t i = 0;

    while(i < Container_t<ELEM>::Count())
    {
        if(m_vec[i] == _elem)
        {
            return i;
        }
    }

    throw("element not found");
}

template <class ELEM>
void Vector_t<ELEM>::Insert(const ELEM& _elem)
{
    ELEM* toInsert = new ELEM (_elem);

    if(m_capacity == Container_t<ELEM>::Count())
    {
        Realloc();
    }

    m_vec[Container_t<ELEM>::Count()] = toInsert;
    Container_t<ELEM>::AddElement();
}

template <class ELEM>
Vector_t<ELEM>::Vector_t(const Vector_t<ELEM>& _cont):
m_size(_cont->m_size), m_capacity(_cont->m_capacity)
{
    m_vec = new ELEM*[m_capacity];

    size_t i = 0;
    for (; i < _cont.m_size; i++)
    {
        m_vec[i] = _cont.m_vec[i];
    }
    
    Container_t<ELEM>::AddContiner();
}

template <class ELEM>
Vector_t<ELEM>& Vector_t<ELEM>::operator=(const Vector_t<ELEM>& _cont)
{
    if (this != &_cont)
    {
        RemoveAndDeleteAll();
        m_size = _cont.m_size;
        m_capacity = _cont.m_capacity;

        delete[] m_vec; // only in case this->m_vec.m_capacity < _vec.m_size
        m_vec = new ELEM*[m_capacity];
        size_t i = 0;
        for (; i < _cont.m_size; i++)
        {
            m_vec[i] = _cont.m_vec[i];
        }
    }  

    return *this;
}

template <class ELEM>
ELEM* Vector_t<ELEM>::Remove(const ELEM& _elem)throw (const char *)
{
    size_t i = -1;
    i = this->Index(_elem);
    if(i != -1)
    {
        ELEM toReturn = m_vec[i];
        m_vec[i] = 0; // delete????
        MoveVectorLeft(i);
        if(toReturn == _elem)
        {
            return toReturn;
        }
    }
    
    throw("element not found, remove failed");
}

template <class ELEM>
void Vector_t<ELEM>::RemoveAndDelete (const ELEM& _value) throw (const char *)
{
    ELEM* elemToDelete;
    try
    {
        elemToDelete = Remove(_value);
    }
    catch (const char * _exep)
    {
        throw ("Object not found ,Vector RemoveAndDelete failed");
    }

    delete elemToDelete;
}
template <class ELEM>
void Vector_t<ELEM>::RemoveAll()
{
    m_size = 0;
}

template <class ELEM>
void Vector_t<ELEM>::RemoveAndDeleteAll()
{
    size_t i = 0;
    for (; i < m_size; i++)
    {
        delete m_vec[i];
    }
    m_size = 0;
}

//--------------------------- private functions----------------------------
template <class ELEM>
void Vector_t<ELEM>::MoveVectorRight(size_t _index)
{
    size_t i = 0;

    while(i != _index)
    {
        m_vec[i] = m_vec[i - 1];
        --i;
    }
}

template <class ELEM>
void Vector_t<ELEM>::MoveVectorLeft(size_t _index)
{
    while(this->Count - 1 != _index)
    {
        m_vec[_index] = m_vec[_index + 1];
        ++_index;
    }
}

template <class ELEM>
void Vector_t<ELEM>::Realloc()
{
    ELEM** newVec = new ELEM*[m_capacity * 2];
    newVec = m_vec;
    delete m_vec;
    m_vec = newVec;
}

#endif //VECTOR_T_H__