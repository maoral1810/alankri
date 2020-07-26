#ifndef DLIST_T_H
#define DLIST_T_H

#include <new>
#include "continer_t.h"
//#include "Node_t.h"

template <class ELEM>

class Dlist_t:public Container_t<ELEM>
{
    Dlist_t();
    virtual ~Dlist_t(){};
    Dlist_t(const Dlist_t& _dlist);
    Dlist_t& operator=(const Dlist_t& _dlist);

    virtual void Append(const ELEM* _element, size_t _index)throw (const char *);
    virtual void Prepend(const ELEM* _element, size_t _index)throw (const char *);
    virtual ELEM* Find(const ELEM& _elem)const;
    virtual size_t Index(const ELEM* _elem)const throw(const char *);
    virtual void Insert (const ELEM* _data) throw (const char *);
    virtual ELEM* Remove(const ELEM& _elem)throw (const char *);
    virtual void RemoveAll();
    virtual void RemoveAndDelete(const ELEM& _elem) throw (const char *);
    virtual void RemoveAndDeleteAll();

    private:
        class Node_t
        {
            public:
                Node_t() : m_data(0), m_prev(0), m_next(0){ }
                Node_t(ELEM _data): m_data((ELEM*)_data), m_prev(0), m_next(0) {}
                ~Node_t();
                Node_t(const Node_t& _node);
                Node_t& operator=(const Node_t& _node);
                
            private:
                ELEM *m_data;
                Node_t *m_next;
                Node_t *m_prev;
        };

        Node_t m_head;
        Node_t m_tail;

        void ListCopyFrom(const Dlist_t& _dlist);
        void NodeConnectBefore(Node_t* _futureNext, Node_t* _newNode);
        Node_t* NodeLocate(const ELEM& _data) const;
        void NodeDisconnect(Node_t* _nodeToRemove);
};

template <class ELEM>
Dlist_t<ELEM>::Dlist_t()
{
    m_head.m_Next = m_tail;
    m_head.m_Prev = m_head;
    m_tail.m_Prev = m_head;
    m_tail.m_Next = m_tail;
    Container_t<ELEM>AddContiner(); 
}

template <class ELEM>
Dlist_t<ELEM>::Dlist_t(const Dlist_t& _dlist)
{
    ListCopyFrom(_dlist);   
    Container_t<ELEM>AddContiner();
}

template <class ELEM>
Dlist_t<ELEM>& Dlist_t<ELEM>::operator=(const Dlist_t& _dlist)
{
    RemoveAll();
    ListCopyFrom(_dlist);
}

template <class ELEM>
void Dlist_t<ELEM>::Append(const ELEM* _element, size_t _index)throw (const char *)
{
    if (!_element)
    {
        throw ("Null element ,DLList Append");
    }

    Node_t* iter = m_head.m_next;
    size_t i = 0;
    while (i < _index && iter != &m_tail)
    {
        iter = iter->m_next;
        i++;
    }

    if (i == _index)
    {
        iter = iter->m_next;
        Node_t* newNode = new Node_t(_element);
        NodeConnectBefore(iter, newNode);
        return *this;
    }

    throw("Index out of bounds ,DLList Append");
}

template <class ELEM>
void Dlist_t<ELEM>::Prepend(const ELEM* _element, size_t _index)throw (const char *)
{
    if (!_element)
    {
        throw ("Null element ,DLList Prepend");
    }

    Node_t* iter = m_head.m_next;
    size_t i = 0;
    while (i < _index && iter != &m_tail)
    {
        iter = iter->m_next;
        i++;
    }

    if (i == _index)
    {
        Node_t* newNode = new Node_t(_element);
        NodeConnectBefore(iter, newNode);
        return *this;
    }

    throw ("Index out of bounds,DLList Prepend");
}

template <class ELEM>
ELEM* Dlist_t<ELEM>::Find(const ELEM& _elem)const
{
    Node_t* nodeLocated = NodeLocate(_elem);
    return (nodeLocated) ? nodeLocated->m_data : 0;
}

template <class ELEM>
size_t Dlist_t<ELEM>::Index(const ELEM* _data) const throw (const char *)
{
    // can't send derefence to NodeLocate - no information about what members operators== compare

    if (!_data)
    {
        throw("Null element ,DLList Index" );
    }

    Node_t* iter = m_head.m_next;
    size_t index = 0;

    while (iter != &m_tail)
    {
        if (iter->m_data == _data)
        {
            return index;
        }
        iter = iter->m_next;
        index++;
    }

    throw("Element not found, DLList Index" );
}

template <class ELEM>
void Dlist_t<ELEM>::Insert (const ELEM* _data) throw (const char *)
{
    if (!_data)
    {
        throw("Null element, DLList Insert" );
    }

    Node_t* newNode = new Node_t(_data);
    NodeConnectBefore(&m_tail, newNode);
}

template <class ELEM>
ELEM* Dlist_t<ELEM>::Remove(const ELEM& _data) throw (const char *)
{
    Node_t* nodeLocated = NodeLocate(_data);

    if (nodeLocated)
    {
        ELEM* temp = nodeLocated->m_data;
        NodeDisconnect(nodeLocated);
        delete nodeLocated;
        return temp;
    }
    
    throw("Object not found ,DLList Remove");
}

template <class ELEM>
void Dlist_t<ELEM>::RemoveAll()
{
    Node_t* iter = m_head.m_next;

    while (iter != &m_tail)
    {
        Node_t* temp = iter;
        NodeDisconnect(iter);
        delete iter;
        iter = temp->m_next;
    }
}

template <class ELEM>
void Dlist_t<ELEM>::RemoveAndDelete(const ELEM& _data) throw (const char *)
{
    ELEM* nodeToDelete;
    try
    {
        nodeToDelete = Remove(_data);
    }
    catch (const char * _exep)
    {
        throw("Object not found ,DLList RemoveAndDelete" );
    }
    delete nodeToDelete;
}

template <class ELEM>
void Dlist_t<ELEM>::RemoveAndDeleteAll()
{
    Node_t* iter = m_head.m_next;

    while (iter != &m_tail)
    {
        Node_t* temp = iter;
        delete iter->m_data;
        NodeDisconnect(iter);
        delete iter;
        iter = temp->m_next;
    }
}

/* template <class ELEM>
void Dlist_t<ELEM>::RemoveAndDeleteAll()
{
    while(m_head.m_Next != m_tail)
    {
        m_head = m_head.m_Next;
        delete m_head.m_Prev;
    }  
} */

// ----------------------- node function ---------------------------------
template <class ELEM>
void Dlist_t<ELEM>::ListCopyFrom (const Dlist_t& _dlist)
{
    size_t i = 0;
    Node_t* iterDLL = _dlist.m_head.m_next;
    Node_t* iterThis = this->m_head.m_next;

    while (iterDLL != _dlist.m_tail)
    {
        Node_t* newNode = new Node_t(iterDLL->m_elem);
        NodeInsertBefore(iterThis, newNode);
        iterThis = iterThis->m_next;
        iterDLL = iterDLL->m_next;
    }
}

template <class ELEM>
void Dlist_t<ELEM>::NodeConnectBefore (Node_t* _futureNext, Node_t* _newNode)
{
    _newNode->m_prev = _futureNext->m_prev;
    _newNode->m_next = _futureNext;
    _futureNext->m_prev->m_next = _newNode;
    _futureNext->m_prev = _newNode;
}

template <class ELEM>
typename Dlist_t<ELEM>::Node_t* Dlist_t<ELEM>::NodeLocate(const ELEM& _data)const
{
    Node_t* iter = m_head.m_next;
    while (iter != &m_tail)
    {
        if (*(iter->m_data) == _data)
        {
            return iter;
        }
        iter = iter->m_next;
    }
    return 0;
}

template <class ELEM>
void Dlist_t<ELEM>::NodeDisconnect (Node_t* _nodeToRemove)
{
    _nodeToRemove->m_next->m_prev = _nodeToRemove->m_prev;
    _nodeToRemove->m_prev->m_next = _nodeToRemove->m_next;
}

#endif //DLIST_T_H