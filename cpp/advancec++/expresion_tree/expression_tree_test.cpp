#include <iostream>
#include <string>
#include <iterator>
#include <iostream> // cout
#include <utility> // make_pair
#include "expression_node.h"
#include "number_node.h"
#include "operator_node.h"
#include "unary_operator_node.h"
#include "to_print.h"
#include "to_BinCalc.h"
#include "to_count_number.h"
#include "to_count.h"
#include "to_uncalc.h"
#include "MUTest.h"
#include "parcer.h"


// ---------------------- static functions --------------------

// ---------------------- tree tests -----------------------
UNIT (DevideByZero)

experis::NumNode* zero = new experis::NumNode(0);
experis::NumNode* one = new experis::NumNode(1);
//experis::NumNode* two = new experis::NumNode(2);
experis::NumNode* three = new experis::NumNode(3);
//experis::NumNode* four = new experis::NumNode(4);
experis::NumNode* five = new experis::NumNode(5);
experis::NumNode* six = new experis::NumNode(6);

experis::OpNode* root = new experis::OpNode(experis::OpNode::PLUS, three, five);
experis::OpNode* exp1 = new experis::OpNode(experis::OpNode::MULT, root, one);
experis::OpNode* exp2 = new experis::OpNode(experis::OpNode::SUB, exp1, six);
experis::OpNode* exp3 = new experis::OpNode(experis::OpNode::DEV, exp2, zero);

experis::ToDoBinCalc calc;

try
{
    std::cout<< "sum = "<< exp3->TraversePostOrder(calc) << std::endl;
}
catch(const std::invalid_argument exp)
{
    std::cout <<std::endl<< "divide by zero" << std::endl;
    delete exp3;
}
    
END_UNIT
/* 
UNIT (UnaryOperator)

experis::NumNode zero(0);
experis::NumNode one(1);
experis::NumNode two(2);
experis::NumNode three(3);
experis::NumNode four(4);
experis::NumNode five(5);
experis::NumNode six(6);

experis::OpNode root(experis::OpNode::PLUS, three, six);
experis::UnaryOp onOper(experis::UnaryOp::SUB , root);
experis::UnaryOp onOperSqrt(experis::UnaryOp::SQRT, root);

onOper.Print();
std::cout<<std::endl;
std::cout<< "sum = "<< onOper.TraversePostOrder() << std::endl<<std::endl;

onOperSqrt.Print();
std::cout<<std::endl;
std::cout<< "sum = "<< onOperSqrt.Calc() << std::endl<<std::endl;

experis::UnaryOp onOperPow(experis::UnaryOp::POW, onOperSqrt);
onOperPow.Print();
std::cout<<std::endl;
std::cout<< "sum = "<< onOperPow.Calc() << std::endl<<std::endl;

END_UNIT 
*/
UNIT (PrintByWhatToDo)

//experis::NumNode* zero = new experis::NumNode(0);
experis::NumNode* one = new experis::NumNode(1);
//experis::NumNode* two = new experis::NumNode(2);
experis::NumNode* three = new experis::NumNode(3);
//experis::NumNode* four = new experis::NumNode(4);
//experis::NumNode* five = new experis::NumNode(5);
experis::NumNode* six = new experis::NumNode(6);

experis::OpNode* root = new experis::OpNode(experis::OpNode::PLUS, three, six);
experis::OpNode* oper = new experis::OpNode(experis::OpNode::SUB, root, one);

experis::ToDoPrint printFunc;

std::cout<< std::endl << oper->TraversePostOrder(printFunc) << std::endl;

experis::ToDoBinCalc calc;
std::cout<< std::endl << oper->TraversePostOrder(calc) << std::endl;

delete root;

END_UNIT 

UNIT (Delete)

experis::NumNode* one = new experis::NumNode(1);
experis::NumNode* three = new experis::NumNode(3);
experis::NumNode* five = new experis::NumNode(5);
experis::NumNode* fourty_two = new experis::NumNode(42);

experis::OpNode* root = new experis::OpNode(experis::OpNode::PLUS, three, five);
experis::OpNode* oper = new experis::OpNode(experis::OpNode::SUB, root, one);
experis::OpNode* oper2 = new experis::OpNode(experis::OpNode::MULT, oper, fourty_two);

experis::ToDoPrint printFunc;

oper2->TraversePostOrder(printFunc);
std::cout<<std::endl;

delete oper2;

END_UNIT

UNIT (Parcer)
    experis::ExpNode* percerResult = experis::Parcer("364+9-7");
    experis::ToDoPrint printFunc;
    percerResult->TraversePostOrder(printFunc);

    delete percerResult;

END_UNIT

UNIT(UnaryOperand)

experis::NumNode* zero = new experis::NumNode(0);
experis::NumNode* one = new experis::NumNode(1);
experis::NumNode* two = new experis::NumNode(2);
experis::NumNode* three = new experis::NumNode(3);
experis::NumNode* four = new experis::NumNode(4);
experis::NumNode* five = new experis::NumNode(5);
experis::NumNode* six = new experis::NumNode(6);

experis::OpNode* root = new experis::OpNode(experis::OpNode::PLUS, three, five);
experis::OpNode* oper = new experis::OpNode(experis::OpNode::SUB, root, one);
experis::OpNode* oper2 = new experis::OpNode(experis::OpNode::MULT, oper, six);
experis::UnaryOp* unOper = new experis::UnaryOp(experis::UnaryOp::SUB, oper2);

experis::ToDoPrint printFunc;
unOper->TraversePostOrder(printFunc);
//excepted resualt: 3,5,+,1,-,6,*,-

experis::ToUnaryCalc unCalc;
std::cout<< std::endl << unOper->TraversePostOrder(unCalc) << std::endl;
// excepted resualt: -42

END_UNIT

TEST_SUITE(expressionTree Test)

    TEST(PrintByWhatToDo)
    TEST(Delete)
    TEST(Parcer)
    TEST(DevideByZero)
    TEST(UnaryOperand)

END_SUITE



