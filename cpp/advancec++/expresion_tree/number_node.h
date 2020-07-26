#ifndef __NUMBER_NODE_H__
#define __NUMBER_NODE_H__

#include <iostream> // cout
#include "expression_node.h"

namespace experis
{

class NumNode : public ExpNode
{
public:
    typedef int Number;
    
    NumNode(Number a_num);
    ~NumNode(){};
    //API Function
    virtual int TraversePostOrder(WhatToDo& a_todo);
    virtual void Print()const{std::cout << m_num << ",";}
    virtual int CountNumbers()const{return 1;}
    virtual int CountNodes()const{return 1;}
    virtual int Calc(int a_left, int a_right)const{return m_num;}
private:
    Number m_num;
    
    //uncopyable
    NumNode(const NumNode& a_other);
    NumNode& operator=(const NumNode& a_other);
};


}//namespace experis
#endif //__NUMBER_NODE_H__