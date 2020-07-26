#ifndef __TO_COUNT_H__
#define __TO_COUNT_H__

#include <string>   
#include "what_to_do.h"
#include "operator_node.h"

namespace experis{

class ToCount: public WhatToDo
{
public:
    ToCount(){}
    virtual ~ToCount(){}
    ToCount(const ToCount& a_other);

    virtual int Do(ExpNode* a_exp , int a_left, int a_right){
        a_exp->CountNodes();
        return a_exp->CountNodes() + a_left + a_right;
    }
private:
    ToCount& operator=(const ToCount& a_other);

};
}// namespace experis

#endif //__TO_COUNT_H__