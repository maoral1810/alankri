#include <iostream> // cout
#include <string>
#include "unary_operator_node.h"

namespace experis{

int UnSqurt(int x){ return sqrt(x); }
int UnPlus(int x){ return x; }
int UnSub(int x){ return -x; }
int UnPow(int x){ return (static_cast<int>(pow(x,2))); }

UnaryOp::UnaryOp(UN_OP_TYPE a_Uoperator, ExpNode* a_Operand)
    :m_unaryOperator(a_Uoperator),
    m_operand(a_Operand)
{

}

int UnaryOp::TraversePostOrder(WhatToDo& a_todo)
{
    int operand = m_operand->TraversePostOrder(a_todo);

    return a_todo.Do(this, operand, 0);
}

}// namespace experis