#ifndef __UNARY_OPERATOR_H__
#define __UNARY_OPERATOR_H__

#include "expression_node.h"
#include <cmath> //sqrt

typedef int (*UnaryCalcFunc)(int);

namespace experis
{

typedef int (*UnaryCalcFunc)(int);
int UnSqurt(int x);
int UnPlus(int x);
int UnSub(int x);
int UnPow(int x);

static const UnaryCalcFunc UNARY_OPERATOR_CLAC[]{
    UnSqurt,
    UnPlus,
    UnSub,
    UnPow
};

static const std::string UN_OPERATOR_SYMBOLS[]{
    "\/-",
    "+",
    "-",
    "^",
};

class UnaryOp:public ExpNode
{
public:
    enum UN_OP_TYPE{
        SQRT = 0,
        PLUS,
        SUB,
        POW
    };

    UnaryOp(UN_OP_TYPE a_Uoperator, ExpNode* a_Operand);
    ~UnaryOp(){};
    //UnaryOp(const UnaryOp& a_other);
    //UnaryOp& operator=(const UnaryOp& a_other);
    virtual int TraversePostOrder(WhatToDo& a_todo);
    virtual void Print()const{ std::cout << UN_OPERATOR_SYMBOLS[m_unaryOperator] << ",";}
    virtual int CountNumbers()const{ return 0; }
    virtual int CountNodes()const{ return 1; }
    virtual int Calc(int a_left, int a_right)const{ return UNARY_OPERATOR_CLAC[m_unaryOperator](a_left); }
    
private:
    UN_OP_TYPE m_unaryOperator;
    ExpNode* m_operand;
};

}//namespace experis


#endif //__UNARY_OPERATOR_H__


