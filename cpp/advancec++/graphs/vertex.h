#ifndef __VERTEX_H__
#define __VERTEX_H__

#include <cstdlib>
#include <list>
#include <algorithm>
#include "edge.h"

namespace experis
{
class Vertex
{
public:
    typedef std::vector<Edge> edgeCont;
    
    Vertex();
    //~Vertex() = defualt;
    //Vertex(const Vertex& a_vertex);
    //Vertex& operator=(const Vertex& a_vertex);
    typedef size_t UID;
    bool AddEdge(const UID& a_target);
    inline UID GetUid()const{return m_uid;}
/*     const edgeCont GetNeibours()const{} */
    const edgeCont& GetEdges()const{return m_edges;}
    bool operator==(const Vertex& a_other)const{return this->GetUid() == a_other.GetUid();}
    bool operator!=(const Vertex& a_other)const{return this->GetUid() != a_other.GetUid();}
    //E RemoveEdge(const )

private:
    UID m_uid;
    edgeCont m_edges;
    static UID m_idCounter;
    // uncopyable
};

}//namespace experis
#endif //__VERTEX_H__