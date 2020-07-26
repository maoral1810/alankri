#ifndef __OPERATOR_NODE_H__
#define __OPERATOR_NODE_H__

#include <iostream> //cout
#include "expression_node.h"

namespace experis{

typedef int (*BinaryCalcFunc)(int,int);
int Modulo(int x ,int y);
int Plus(int x ,int y);
int Multiply(int x ,int y);
int Substruct(int x ,int y);
int Devide(int x ,int y);
int Power(int x ,int y);

static const BinaryCalcFunc OPERATOR_CLAC[] {
    Modulo,
    Multiply,
    Plus,
    Substruct,
    Devide,
    Power
};

static const std::string OPERATOR_SYMBOLS[] {
    "%",
    "*",
    "+",
    "-",
    "/",
    "^"
};

class OpNode : public ExpNode {
public:
    enum OP_TYPE { 
        MODULO = 0,
        MULT,
        PLUS,
        SUB,
        DEV,
        POW 
    };

    OpNode(OP_TYPE a_operator, ExpNode* a_leftExp, ExpNode* a_rightExp);
    ~OpNode()
    {
        delete this->m_left;
        delete this->m_right;
    }
    //OpNode(const OpNode& a_other) = default;

    //API Function
    virtual int TraversePostOrder(WhatToDo& a_todo);
    virtual void Print()const{std::cout << OPERATOR_SYMBOLS[m_operator] << ",";}
    virtual int CountNumbers()const{ return 0; }
    virtual int CountNodes()const{ return 1; }
    virtual int Calc(int a_left, int a_right)const{return OPERATOR_CLAC[m_operator](a_left, a_right);}
    
private:
    OpNode& operator=(const OpNode& a_other);
    
    OP_TYPE m_operator;
    ExpNode* m_left;
    ExpNode* m_right;
};


}// namespace experis
#endif //__OPERATOR_NODE_H__