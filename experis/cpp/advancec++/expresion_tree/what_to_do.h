#ifndef __WHAT_TO_DO_H__
#define __WHAT_TO_DO_H__

#include <cmath>
/* #include "operator_node.h" */

namespace experis{

class OpNode;
class ExpNode;
class WhatToDo
{

public:
    //typedef OpNode::OP_TYPE OP_TYPE;
    enum OP_TYPE{ 
        MODULO = 0,
        MULT,
        PLUS,
        SUB,
        DEV,
        POW 
    };
    WhatToDo(){};
    virtual ~WhatToDo(){};
    WhatToDo(const WhatToDo& a_other);
    virtual int Do(ExpNode* a_exp , int a_left, int a_right) = 0;
 
private:
    WhatToDo& operator=(const WhatToDo& a_other);
};




}//namespace experis
#endif //__WHAT_TO_DO_H__