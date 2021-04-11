#pragma once

#include "IOperand.h"
#include <stack>
#include <map>


using Fptr = void(*)(std::stack<const IOperand*>&);

void initPubs(std::map<std::string, Fptr>& pubOperations,
    std::map<std::string, Fptr>& pubOthers,
    std::map<std::string, eOperandType>& pubTypes);