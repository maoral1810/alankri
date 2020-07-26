#ifndef __TO_UNARY_CALC_H_
#define __TO_UNARY_CALC_H_

#include <string>   
#include "what_to_do.h"
#include "unary_operator_node.h"

namespace experis{

class ToUnaryCalc: public WhatToDo
{
public:
    ToUnaryCalc(){}
    virtual ~ToUnaryCalc(){}
    ToUnaryCalc(const ToUnaryCalc& a_other);

    virtual int Do(ExpNode* a_exp , int a_left, int a_right){
        return a_exp->Calc(a_left, a_right);
    }
private:
    ToUnaryCalc& operator=(const ToUnaryCalc& a_other);
    int leftOperand;
    int rigthOperand;
    int numCounter;
};
}// namespace experis

#endif //__TO_UNARY_CALC_H_