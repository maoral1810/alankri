#include <iostream> // cout
#include <cmath>    // pow
#include <string>
#include "operator_node.h"
#include "number_node.h"
#include "what_to_do.h"

namespace experis{

OpNode::OpNode(OP_TYPE a_operator, ExpNode* a_leftExp, ExpNode* a_rightExp)
    : m_operator(a_operator), 
      m_left(a_leftExp),
      m_right(a_rightExp)
{

}

int OpNode::TraversePostOrder(WhatToDo& a_todo)
{
    int left = m_left->TraversePostOrder(a_todo);
    int right = m_right->TraversePostOrder(a_todo);

    return a_todo.Do(this, left, right);
}

// ----------------------------------------------------------------------------

int Modulo(int x ,int y){return x % y;}
int Plus(int x ,int y){return x + y;}
int Multiply(int x ,int y){return x * y;}
int Substruct(int x ,int y){return x - y;}
int Devide(int x ,int y){
    if(!y)
    {
        throw(std::invalid_argument("devide by zero"));
    }
    return x / y;
}
int Power(int x ,int y){return (static_cast<int>(pow(x,y)));}
}//namespace experis