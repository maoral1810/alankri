#include <string>
#include <cstdlib>
#include <sstream>
#include <limits.h>
#include <cstring>
#include "expression_node.h"
#include "operator_node.h"
#include "number_node.h"

namespace experis{ 

ExpNode* Parcer(const std::string& a_expression)
{
    std::stringstream expStr;
    expStr.str(a_expression);

    static OpNode::OP_TYPE assciTable[UCHAR_MAX];
    memset(assciTable, '0' , UCHAR_MAX * sizeof(OpNode::OP_TYPE));
    // reset the LUT
    assciTable['+'] = OpNode::PLUS;
    assciTable['-'] = OpNode::SUB;
    assciTable['/'] = OpNode::DEV;
    assciTable['*'] = OpNode::MULT;
    assciTable['^'] = OpNode::POW;
    assciTable['%'] = OpNode::MODULO;

    int firstNum;
    expStr >> firstNum;
    if(expStr.fail())
    {
        throw(std::invalid_argument ("bad expression"));
    }

    ExpNode* leftExp = new NumNode(firstNum);
    
    while(1)
    {   
        char op;
        expStr >> op;
        if(expStr.fail())
        {
            throw(std::invalid_argument ("bad expression"));
        }

        int Number;
        expStr >> Number;
        if(expStr.fail())
        {
            throw(std::invalid_argument ("bad expression"));
        }

        OpNode::OP_TYPE opType = assciTable[op];

        ExpNode* rightExp = new NumNode(Number);
        OpNode* opNode = new OpNode(opType,leftExp, rightExp);
        leftExp = opNode;

        if(expStr.eof())
        {
            break;
        }
    }

    return leftExp;
}

}// namespace experis
