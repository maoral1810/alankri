#ifndef CONTINER_T_H__
#define CONTINER_T_H__
#include <stddef.h> //size_t

template <class ELEM>

class Container_t 
{
    Container_t();
    ~Container_t();
    virtual Container_t<ELEM>& Append(size_t _index, const ELEM* _element) = 0;
    virtual Container_t<ELEM>& Prepend(size_t _index, const ELEM* _element) = 0;
    size_t Count()const{return m_numOfElement;}
    bool Contains(const ELEM& _elem)const;
    virtual ELEM* Find(const ELEM& _elem)const = 0;
    virtual size_t Index(const ELEM& _elem)const;
    virtual void Insert(const ELEM& _elem) = 0;
    bool IsEmpty()const{return m_numOfElement == 0;}

    virtual const ELEM* Remove(const ELEM& _elem) = 0;
    virtual void RemoveAll() = 0;
    virtual void RemoveAndDelete(ELEM& _elem) = 0;
    virtual void RemoveAndDeleteAll() = 0;

    protected:
        void SetNumOfElements(size_t _elements);
        inline void AddContainer(){++m_conteinerCount;}
        inline void SubContanier(){--m_conteinerCount;}
        inline void AddElement(){++m_numOfElement;}
        inline void SubElement(){--m_numOfElement;}

    private:
        size_t m_numOfElement;
        size_t m_conteinerCount;
        Container_t& operator=(const Container_t& _cont){};
        Container_t(const Container_t& _cont){};
 
};

template <class ELEM>
bool Container_t<ELEM>::Contains(const ELEM& _elem)const
{
    return Find(_elem) ? true :false;
}
/*             All Containers are containers of pointers to T !!!                                 
                                                
                                                
    • Default CTOR
    • Copy	CTOR
    • DTOR
    • Operator= 

    • append 			- element after index
    • prepend			- element before index
    • contains			- element in container
    • count				- number of elements in container
    • find  				- element in container
				  	   As a parameter gets T to be found 

    • index				- index of element in container
    • insert				- at end of container
    • isEmpty			

    • remove			- remove element from container
				  	  As a parameter gets T to be found and removed from container
    • removeAll 			- remove all elements from container
    • removeAndDelete		- remove and delete element from container
				  	  As a parameter gets T to be found and removed from container                    
    • removeAndDeleteAll		- remove and delete all elements from container


Note : elements are POINTERS !!! */

#endif //CONTINER_T_H__