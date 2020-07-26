#ifndef __TO_DO_BIN_CALC_H_
#define __TO_DO_BIN_CALC_H_

#include <string>   
#include "what_to_do.h"
#include "operator_node.h"

namespace experis{

class ToDoBinCalc: public WhatToDo
{
public:
    ToDoBinCalc(){}
    virtual ~ToDoBinCalc(){}
    ToDoBinCalc(const ToDoBinCalc& a_other);
    ToDoBinCalc& operator=(const ToDoBinCalc& a_other);

    virtual int Do(ExpNode* a_exp , int a_left, int a_right){
        return a_exp->Calc(a_left, a_right);
    }
private:
    int leftOperand;
    int rigthOperand;
    int numCounter;
};
}// namespace experis

#endif //__TO_DO_BIN_CALC_H_