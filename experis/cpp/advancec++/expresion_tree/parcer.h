#ifndef __PARCER_H__
#define __PARCER_H__

#include <string>
#include "expression_node.h"

namespace experis{

    ExpNode* Parcer(const std::string& a_expression);
}// namepace experis

#endif //__PARCER_H__