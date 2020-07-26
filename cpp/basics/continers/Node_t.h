#ifndef NODE_T_H__
#define NODE_T_H__

template <class DATA>
class Node_t
{
    public:
        Node_t(DATA_data);
        ~Node_t();
        Node_t(const Node_t& _node);
        Node_t& operator=(const Node_t& _node);
        
    private:
        DATA *m_data;
        Node_t *m_Next;
        Node_t *m_Prev;
};

template <class DATA>
Node_t<DATA>::Node_t(DATA _data): m_Next(0), m_Prev(0)
{
    m_data = new DATA(_data);
}

template <class DATA>
Node_t<DATA>::~Node_t()
{
    delete m_data;
}

template <class DATA>
Node_t<DATA>::Node_t(const Node_t& _node)
{
    if(this != _node)
    {
        m_data = _node->m_data;
        m_Prev = _node->m_Prev;
        m_Next = _node->m_Next;
    }
}

template <class DATA>
Node_t<DATA>& Node_t<DATA>::operator=(const Node_t& _node)
{
    if(this != _node)
    {
        m_data = _node->m_data;
        m_Prev = _node->m_Prev;
        m_Next = _node->m.Next;
    }

    return *this;
}

#endif //NODE_T_H__