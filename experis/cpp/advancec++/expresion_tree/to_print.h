#ifndef __TO_DO_PRINT_H__
#define __TO_DO_PRINT_H__

#include <string>   
#include "what_to_do.h"
#include "operator_node.h"

namespace experis{

class ToDoPrint: public WhatToDo
{
public:
    ToDoPrint(){}
    virtual ~ToDoPrint(){}
    ToDoPrint(const ToDoPrint& a_other);

    virtual int Do(ExpNode* a_exp , int a_left, int a_right) {
        a_exp->Print();
        return 0;
    }

private:
    ToDoPrint& operator=(const ToDoPrint& a_other);

};


}// namespace experis

#endif //__TO_DO_PRINT_H__