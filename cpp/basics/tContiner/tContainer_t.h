#ifndef TCONTINER_T_H
#define TCONTINER_T_H

#include <string>
#include <vector>
#include <typeinfo>
#include <algorithm>

using namespace std;
template <class T>
class SameT_t
{
    public:
        SameT_t(const T& _data):m_data(_data){}
        bool operator()(const T* _param)const{return (m_data == *_param);}
    
    private:
        T m_data;
};

template <class T, class CONT>
class TContainer_t
{
    typedef typename CONT::iterator iter_t;  

    public:
        TContainer_t(){};
        virtual ~TContainer_t(){RemoveAll();};
        bool IsEmpty()const{return m_container.empty();}
        size_t Size()const{return m_container.size();}
        virtual int Insert(const T* _elem){return Append(_elem) ? 1 : 0;}
        T* LastElement()const{return m_container.empty() ? 0 : *(m_container.rbegin());}
        T* FirstElement()const{return m_container.empty() ? 0 :*(m_container.begin());}
        T* FindSpecific(const T& _elem);
        T* Remove(const T& _i);
        virtual T* Append( const T* intP);
        void RemoveAll(){m_container.clear();}
        void RemoveAndDelete(const T& _remevedElem){delete Remove(_remevedElem);}
        void RemoveAndDeleteAll();
        T* operator[](const size_t& _index)const throw(string); //get
/*         T* operator[](const size_t& _index)throw(string); // set
 */
    protected:
        CONT m_container;
        iter_t	m_iter;

    private:
        TContainer_t(const CONT& _cont);
        TContainer_t operator=(const CONT& _cont){};
        iter_t FindIterator(const T& t){return find_if(m_container.begin(), m_container.end(),SameT_t<T>(t));}
};

//--------------------------- implemention --------------------------
template<class T, class CONT>
void TContainer_t<T,CONT>::RemoveAndDeleteAll()
{
    iter_t begin = m_container.begin();
    iter_t end = m_container.end();
    iter_t savePrev;

    while(begin != end)
    {
        savePrev = begin;
        ++begin;
        RemoveAndDelete(**savePrev);
    }
}

template<class T, class CONT>
T* TContainer_t<T,CONT>::Remove(const T& _cont)
{
    iter_t iter = FindIterator(_cont); 
    T* SaveData = *iter;
    m_container.erase(iter);

    return SaveData;
}
template<class T, class CONT>
T* TContainer_t<T,CONT>::FindSpecific(const T& _elem)
{
    iter_t iter = find_if(m_container.begin(), m_container.end(),SameT_t<T>(_elem));

    return iter != m_container.end() ? *iter : 0; 
}

template<class T, class CONT>
T* TContainer_t<T,CONT>::operator[](const size_t& _index)const throw(string) //get
{
    if (typeid(m_container) == typeid(vector<T*>))
    {
        return (*(vector<T*>*)(void*)&m_container)[_index];
    }
    else
    {
        if (_index > m_container.size())
        {
            return 0;
        }
        m_iter = m_container.begin();
        size_t i = 0;
 
        for(; i < _index; ++i) ++m_iter;
    } 
    
    return *m_iter;
}

/* template<class T, class CONT>
T* TContainer_t<T,CONT>::operator[](const size_t& _index)throw(string) // set
{
    return (T*)operator[](_index);
} */

template<class T, class CONT>
T* TContainer_t<T,CONT>::Append( const T* _intP) 
{ 
    int nElem = m_container.size();
    m_container.insert(m_container.end(), (T*)_intP); 
    return m_container.size() == nElem ? 0 : (T*)_intP;
}
/* 
- default CTOR
	- DTOR
	- not to allow copy;
- return true/false according to is array empty or not
	- return number of elements in array
	- insert a new element in the end of array
        	- return first element in container
        	- return last  element in container
	- find specific element by value ( parameter is T value )				^***
          		Use STL algorithm “find_if” . Such algorithm uses predicate that 
has to be written by user
	- remove specific element and returns pointer to it ( parameter is T value )		^***
	- remove all elements ( without deleting them )
	- remove and delete specific element ( parameter is T value )	
- remove and delete all elements 
- operator[] – pay attention, that class vector has operator[] and list not!!!
		So, use operator typeid in order to implement operator[] for vector 
		and list in a different way */

#endif //TCONTINER_T_H