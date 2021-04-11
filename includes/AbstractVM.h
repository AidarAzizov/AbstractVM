#pragma once


#include <iostream>
#include <stdint.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <stack>
#include <map>
#include <set>

#include "IOperand.h"
#include "Creator.h"

#define MAX_PRECISION 308

#define COUNT_NUM_INT 15
#define MAX_COUNT_NUM 800

#define MIN_SIZE_FOR_OPERATION 2
#define SUCCESS_CODE 0
#define ERROR_CODE -1


template <typename T>
class Type
{
public:
    T val;
    Type(const T& val);
    operator T();
    T operator=(const T& val);
};

class IOperandCreator
{
protected:
    IOperand const* createInt8(std::string const& value) const;
    IOperand const* createInt16(std::string const& value) const;
    IOperand const* createInt32(std::string const& value) const;
    IOperand const* createFloat(std::string const& value) const;
    IOperand const* createDouble(std::string const& value) const;

    using Fptr = IOperand const* (IOperandCreator::*)(std::string const&) const;

    std::vector<Fptr> associater
    {
            &IOperandCreator::createInt8,
            &IOperandCreator::createInt16,
            &IOperandCreator::createInt32,
            &IOperandCreator::createFloat,
            &IOperandCreator::createDouble
    };
public:
    IOperand const* createOperand(eOperandType type, std::string const& value) const;
};

class Operand : public IOperand, public IOperandCreator
{
    int precision;
    eOperandType type;
    std::string StringVal;

    bool checkOtherDigits(const std::string& num);
    bool checkAlpha(const std::string& num);
    int countDigitAfterDot(const std::string& value);
public:
    Operand(const std::string& value, eOperandType type);

    int getPrecision(void) const override;
    eOperandType getType(void) const override;

    IOperand const* operator+(IOperand const& rhs) const override;
    IOperand const* operator-(IOperand const& rhs) const override;
    IOperand const* operator*(IOperand const& rhs) const override;
    IOperand const* operator/(IOperand const& rhs) const override;
    IOperand const* operator%(IOperand const& rhs) const override;
    std::string const& toString(void) const override;
};

const IOperand* Creator(const std::string& value, eOperandType type);

template <typename T>
T printAndExit(const T& whatReturn, const std::string& message)
{
    std::cout << message << std::endl;
    return whatReturn;
}


template <typename T>
Type<T>::Type(const T& val) { this->val = val; }

template <typename T>
Type<T>::operator T() { return val; }

template <typename T>
T Type<T>::operator=(const T& val) { this->val = val; }