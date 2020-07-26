#include "graph.h"

namespace experis{

Graph::Graph(size_t a_size,HashFunction a_hashFunc, CompereFunction a_CmpFunc)
:m_graphContainer(Hash<UID,Vertex>(a_size, a_hashFunc, a_CmpFunc))
{

}

bool Graph::AddEdge(Vertex& a_vartex, Vertex& a_other)
{
    return a_vartex.AddEdge(a_other.GetUid());
}

bool Graph::AddVertex(const Vertex& a_vartex)
{
    return m_graphContainer.Add(a_vartex.GetUid(), a_vartex);
}

std::vector<Vertex> Graph::GetNeibours(const Vertex& a_vartex)
{
    try
    {
        Vertex::edgeCont vertexEdges = a_vartex.GetEdges();
        Vertex::edgeCont::const_iterator itr = vertexEdges.begin();
        std::vector<Vertex> vertexNeighbors;

        for(;itr != vertexEdges.end(); ++itr)
        {
            vertexNeighbors.push_back(m_graphContainer.Get((*itr).GetTargetUid()));
        }
        return vertexNeighbors;
    }
    catch(const std::out_of_range& a_exception)
    {
        throw std::out_of_range("No such vertex");
    }
}

Graph::VertexCont Graph::FindPath(const Vertex& a_from, const Vertex& a_to)
{
        VertexCont path;
        Graph::VertexCont vertexNeighbors = GetNeibours(a_from);

        path.push_back(a_from);

        if(std::find(vertexNeighbors.begin(), vertexNeighbors.end(), a_to) != vertexNeighbors.end())
        {
            path.push_back(a_to);
            return path;
        }
        else
        {
            std::map<Vertex::UID, bool> IsVisited;
            IsVisited[a_from.GetUid()] = true;
            return DFS(a_from, a_to, vertexNeighbors, IsVisited, path);
        }    
    }
}

std::vector<Vertex> Graph::DFS
(const Vertex& a_from,
const Vertex& a_to, 
const std::vector<Vertex>& vertexNeighbors,
std::map<Vertex::UID, bool>& IsVisited,
std::vector<Vertex>& path)
{
    if(a_from == a_to)
    {
        return path;
    }

    for(std::vector<Vertex>::const_iterator itr = vertexNeighbors.begin(); itr != vertexNeighbors.end(); itr++)
    {
        if(IsVisited[itr->GetUid()] == false)
        {
            IsVisited[itr->GetUid()] = true;
            path.push_back(*itr);
            return DFS(*itr, a_to, GetNeibours(*itr), IsVisited, path);
        }
    }

    if(!IsVisited[a_to.GetUid()])
    {
        //return empty path;
    }
    return path;
}

}// namspace experis