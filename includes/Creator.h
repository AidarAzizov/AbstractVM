#pragma once

#include <iostream>
#include <cstring>
#include <stdint.h>
#include <string>

#include "IOperand.h"


std::string createResult(const std::string& first, const std::string& second, 
	eOperandType maxType, int maxPrecision, char operation);
