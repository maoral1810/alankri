#include <iostream> // cout
#include "number_node.h"
#include "what_to_do.h"

namespace experis{

experis::NumNode::NumNode(Number a_num)
    :m_num(a_num)
{

}

int NumNode::TraversePostOrder(WhatToDo& a_todo)
{
    return a_todo.Do(this, 0, 0);
}

}// namespace experis