#ifndef __EDGE_H__
#define __EDGE_H__

#include "../hash/bucket.h"
namespace experis
{
class Edge
{   
private:
    typedef size_t UID;
    typedef double Weigth;
public:
    Edge(UID a_target, Weigth a_weigth)
    :m_targetUid(a_target),
    m_weigth(a_weigth)
    {

    }
    Edge(UID a_target)
    :m_targetUid(a_target),
    m_weigth(1)
    {
        
    }
    // ~Edge() = defualt;
    // Edge(const &Edge a_edge) = defualt;
    // Edge& operator=(const &Edge a_edge) = defualt;
    bool operator==(const Edge& a_other){return ((m_targetUid == a_other.m_targetUid)&& (m_weigth == a_other.m_weigth));}
    //API Functions
    UID GetTargetUid(){return m_targetUid;}
    UID GetTargetWeigth(){return m_weigth;}

private:
    UID m_targetUid;
    Weigth m_weigth;
};

}// namespace experis

#endif //__EDGE_H__