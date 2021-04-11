#include "AbstractVM.h"
#include <iomanip>

std::string const& Operand::toString(void) const { return StringVal; }
int Operand::getPrecision(void) const { return precision; }
eOperandType Operand::getType(void) const { return type; }
bool Operand::checkOtherDigits(const std::string& num)
{
    for (auto& it : num)
    {
        if (isdigit(it) && it != '0')
            return false;
    }
    return true;
}
bool Operand::checkAlpha(const std::string& num)
{
    for (auto& it : num)
    {
        if (it == '-') continue;
        if (!isdigit(it)) return true;
    }
    return false;
}
int Operand::countDigitAfterDot(const std::string& value)
{
    int result = 0;
    std::stringstream str(value.c_str());
    std::string copy = value;
    size_t pos;

    if ((pos = str.str().find_first_of("eEgG")) != std::string::npos && pos > 1)
    {

        result += atoi(str.str().substr(pos + 2, str.str().size() - pos).c_str());
        str.str(str.str().erase(pos, str.str().size() - pos));
        pos = value.find_first_not_of("+-0");

        if (value[pos] == '.') { while (value[++pos] == '0')result++; }
        else { while (value[pos++] != '.')result--; }
         
        return (result > 0) ? result : 0;
    }

    if (str.str().find(".") == std::string::npos) return result;
    for (int i = str.str().size() - 1; i >= 0; i--)
    {
        if (str.str()[i] == '.') break;
        result++;
    }

    return result;
}


IOperand const* IOperandCreator::createOperand(eOperandType type, std::string const& value) const
{
    return (this->*associater[type])(value);
}
IOperand const* IOperandCreator::createInt8(std::string const& value) const { return new Operand(value, Int8); }
IOperand const* IOperandCreator::createInt16(std::string const& value) const { return new Operand(value, Int16); }
IOperand const* IOperandCreator::createInt32(std::string const& value) const { return new Operand(value, Int32); }
IOperand const* IOperandCreator::createFloat(std::string const& value) const { return new Operand(value, Float); }
IOperand const* IOperandCreator::createDouble(std::string const& value) const { return new Operand(value, Double); }

IOperand const* Operand::operator+(IOperand const& rhs) const
{
    eOperandType resultType = (getType() > rhs.getType() ? getType() : rhs.getType());
    int resultPrecision = (getPrecision() > rhs.getPrecision() ? getPrecision() : rhs.getPrecision());

    std::string resultString = createResult(StringVal, rhs.toString(), resultType, resultPrecision, '+');
    return createOperand(resultType, resultString);
}
IOperand const* Operand::operator-(IOperand const& rhs) const
{
    eOperandType resultType = (getType() > rhs.getType() ? getType() : rhs.getType());
    int resultPrecision = (getPrecision() > rhs.getPrecision() ? getPrecision() : rhs.getPrecision());

    std::string resultString = createResult(StringVal, rhs.toString(), resultType, resultPrecision, '-');
    return createOperand(resultType, resultString);
}
IOperand const* Operand::operator*(IOperand const& rhs) const
{
    eOperandType resultType = (getType() > rhs.getType() ? getType() : rhs.getType());
    int resultPrecision = (getPrecision() > rhs.getPrecision() ? getPrecision() : rhs.getPrecision());

    std::string resultString = createResult(StringVal, rhs.toString(), resultType, resultPrecision, '*');
    return createOperand(resultType, resultString);
}
IOperand const* Operand::operator/(IOperand const& rhs) const
{
    eOperandType resultType = (getType() > rhs.getType() ? getType() : rhs.getType());
    int resultPrecision = (getPrecision() > rhs.getPrecision() ? getPrecision() : rhs.getPrecision());

    std::string resultString = createResult(StringVal, rhs.toString(), resultType, resultPrecision, '/');
    return createOperand(resultType, resultString);
}
IOperand const* Operand::operator%(IOperand const& rhs) const
{
    eOperandType resultType = (getType() > rhs.getType() ? getType() : rhs.getType());
    int resultPrecision = (getPrecision() > rhs.getPrecision() ? getPrecision() : rhs.getPrecision());

    std::string resultString = createResult(StringVal, rhs.toString(), resultType, resultPrecision, '%');
    return createOperand(resultType, resultString);
}

Operand::Operand(const std::string& value, eOperandType type)
{
    std::stringstream str(value.c_str());


    char symb = 0;
    int setPrecision = 0;
    int64_t checkInt;
    long double checkDouble;
    switch (type)
    {
    case Int8:
        str >> checkInt >> symb;
        if (str.str().size() > COUNT_NUM_INT || checkInt > INT8_MAX || checkInt < INT8_MIN)
            throw MyException("Int8_t overflowed.");
        if (symb || checkAlpha(str.str())) throw MyException("Int8_t has bad value.");
        break;
    case Int16:
        str >> checkInt >> symb;
        if (str.str().size() > COUNT_NUM_INT || checkInt > INT16_MAX || checkInt < INT16_MIN)
            throw MyException("Int16_t overflowed.");
        if (symb || checkAlpha(str.str())) throw MyException("Int16_t has bad value.");
        break;
    case Int32:
        str >> checkInt >> symb;
        if (str.str().size() > COUNT_NUM_INT || checkInt > INT32_MAX || checkInt < INT32_MIN)
            throw MyException("Int32_t overflowed.");
        if (symb || checkAlpha(str.str())) throw MyException("Int32_t has bad value.");
        break;
    case Float:
        str >> checkDouble >> symb;
        if (abs(checkDouble) > FLT_MAX || (abs(checkDouble) < FLT_MIN && checkDouble != 0.0) ||
            (!checkOtherDigits(str.str()) && checkDouble == 0.0))
            throw MyException("Float overflowed.");
        if (symb || str.str() == ".") throw MyException("Float has bad value.");
        break;
    case Double:
        str >> checkDouble >> symb;
        if (abs(checkDouble) > DBL_MAX || (abs(checkDouble) < DBL_MIN && checkDouble != 0.0) ||
            (!checkOtherDigits(str.str()) && checkDouble == 0.0))
            throw MyException("Double overflowed.");
        if (symb || str.str() == ".") throw MyException("Double has bad value.");
        break;
    }
    this->StringVal = value.c_str();
    this->precision = countDigitAfterDot(value);
    this->type = type;

    if (this->precision > MAX_PRECISION)
        this->precision = MAX_PRECISION;
}

const IOperand* Creator(const std::string& value, eOperandType type)
{
    static IOperandCreator IAmCreatorHere;

    return IAmCreatorHere.createOperand(type, value);
}
