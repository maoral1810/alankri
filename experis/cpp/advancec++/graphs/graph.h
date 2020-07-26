#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <cstdlib>
#include <list>
#include <set>
#include <stack>
#include <map>
#include "vertex.h"
#include "edge.h"
#include "../hash/hash.h"

/* static bool Less(Vertex& a_vartex, Vertex& a_other); */

namespace experis
{

class Graph
{
    typedef size_t UID;
    typedef std::vector<Vertex> VertexCont;
    
    typedef unsigned int(*HashFunction)(const UID& a_key);
    typedef bool(*CompereFunction)(const UID& a_key, const UID& a_otherKey);

public:
    Graph(size_t a_size, HashFunction a_hashFunc, CompereFunction a_CmpFunc);
    // ~Graph() = defualt;
    // Graph(const &Graph a_graph) = defualt;
    // Graph& operator=(const &Graph a_graph) = defualt;
    bool AddVertex(const Vertex& a_vartex);
    bool AddEdge(Vertex& a_vartex, Vertex& a_other);
    const Vertex& Get(UID& a_uid)const;
    VertexCont GetNeibours(const Vertex& a_vartex);
    VertexCont FindPath(const Vertex &a_vartex1, const Vertex& a_vertex2);
    VertexCont DFS
    (const Vertex& a_from,
    const Vertex& a_to, 
    const std::vector<Vertex>& vertexNeighbors,
    std::map<Vertex::UID, bool>& IsVisited,
    VertexCont& path);

private:
    Hash<UID, Vertex> m_graphContainer;
};



/* static bool Less(Vertex& a_vartex, Vertex& a_other)
{
    return a_vartex == a_other;
} */


}//namespace experis 
#endif //__GRAPH_H__