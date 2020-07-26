#include <new>
#include <iterator>
#include "vertex.h"

namespace experis
{

Vertex::UID Vertex::m_idCounter = 0;

Vertex::Vertex()
    :m_uid(m_idCounter++)
{

}

bool Vertex::AddEdge(const UID& a_target)
{
    // defualt constractor of edge implicitly
    edgeCont::iterator m_iter = std::find(m_edges.begin(), m_edges.end(), a_target);
    if(m_iter != m_edges.end())
    {
        return false;
    }
    
    try
    {
        m_edges.push_back(a_target); 
    }
    catch(std::bad_alloc)
    {
        return false;
    }

    return true;
}

}//namespace experis
