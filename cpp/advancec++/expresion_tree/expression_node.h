#ifndef __EXPRESSION_NODE_H__
#define __EXPRESSION_NODE_H__

#include "what_to_do.h"

namespace experis{
class WhatToDo;
class ExpNode
{
public:
    ExpNode(){}
    virtual ~ExpNode(){}
    //ExpNode(const ExpNode& a_other) = defautl;
    //ExpNode& operator=(const ExpNode& a_other) = default;
    
    //API Function
    virtual int TraversePostOrder(WhatToDo& a_todo) = 0;
    virtual void Print()const = 0;
    virtual int CountNumbers()const = 0;
    virtual int CountNodes()const = 0;
    virtual int Calc(int a_left, int a_right)const = 0;
};
}//namespace exsperis
#endif //__EXPRESSION_NODE_H__