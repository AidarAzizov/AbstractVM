#include "Creator.h"
#include <sstream>
#include <iomanip>

std::string getRightString(long double result, eOperandType maxType, int maxPrecision)
{
    std::ostringstream str;
    str << std::fixed << std::setprecision(maxPrecision);
    (maxType == Double) ? (str << (double)result) : (str << (float)result);

    return str.str();
}

std::string makeAdd(long double first, long double second, eOperandType maxType, int maxPrecision)
{
    if (maxType <= Int32)
        return std::to_string(((int64_t)first + (int64_t)second));
    return getRightString((long double)first + (long double)second,
        maxType, maxPrecision);
}
std::string makeSub(long double first, long double second, eOperandType maxType, int maxPrecision)
{
    if (maxType <= Int32)
        return std::to_string(((int64_t)first - (int64_t)second));
    return getRightString((long double)first - (long double)second,
        maxType, maxPrecision);
}
std::string makeDiv(long double first, long double second, eOperandType maxType, int maxPrecision)
{
    if (DBL_MIN > second)
        throw MyException("Happened div on zero.");
    if (maxType <= Int32)
        return std::to_string(((int64_t)first / (int64_t)second));
    return getRightString((long double)first / (long double)second,
        maxType, maxPrecision);
}
std::string makeMul(long double first, long double second, eOperandType maxType, int maxPrecision)
{
    if (maxType <= Int32)
        return std::to_string(((int64_t)first * (int64_t)second));
    return getRightString((long double)first * (long double)second,
        maxType, maxPrecision);
}
std::string makeMod(long double first, long double second, eOperandType maxType, int maxPrecision)
{
    if (maxType > Int32) throw MyException("Mod should be between only integer value.");
    if ((int64_t)second == 0) throw MyException("Happened mod on zero.");
    return std::to_string(((int64_t)first % (int64_t)second));
}

std::string createResult(const std::string& first, const std::string& second, eOperandType maxType, int maxPrecision, char operation)
{
    std::string result;
    long double first_d = 0, second_d = 0;

    if (sscanf(first.c_str(), "%Lf", &first_d) != 1)
        throw MyException("bad try read with sscanf() value " + first + " for " + operation + " operation");
    if (sscanf(second.c_str(), "%Lf", &second_d) != 1)
        throw MyException("bad try read with sscanf() value " + second + " for " + operation + " operation");

    switch (operation)
    {
    case '+':
        result = makeAdd(first_d, second_d, maxType, maxPrecision);
        break;
    case '-':
        result = makeSub(first_d, second_d, maxType, maxPrecision);
        break;
    case '/':
        result = makeDiv(first_d, second_d, maxType, maxPrecision);
        break;
    case '*':
        result = makeMul(first_d, second_d, maxType, maxPrecision);
        break;
    default: //is '%'
        result = makeMod(first_d, second_d, maxType, maxPrecision);
        break;
    }
    return result;
}

