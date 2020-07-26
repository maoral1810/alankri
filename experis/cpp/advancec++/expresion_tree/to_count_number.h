#ifndef __TO_DO_COUNT_NUMBERS_H__
#define __TO_DO_COUNT_NUMBERS_H__

#include <string>   
#include "what_to_do.h"
#include "operator_node.h"

namespace experis{

class ToDoCountNum: public WhatToDo
{
public:
    ToDoCountNum(){}
    virtual ~ToDoCountNum(){}
    ToDoCountNum(const ToDoCountNum& a_other);

    virtual int Do(ExpNode* a_exp , int a_left, int a_right){
        a_exp->CountNumbers();
        return a_exp->CountNumbers() + a_left + a_right;
    }

private:
    ToDoCountNum& operator=(const ToDoCountNum& a_other);
};
}// namespace experis

#endif //__TO_DO_COUNT_NUMBERS_H__