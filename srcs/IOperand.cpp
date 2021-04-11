#include "IOperand.h"

static std::map<eOperandType, std::string> TypeNames
{
    std::make_pair(Int8, "Int8"),
    std::make_pair(Int16, "Int16"),
    std::make_pair(Int32, "Int32"),
    std::make_pair(Float, "Float"),
    std::make_pair(Double, "Double"),
};

bool IOperand::operator==(IOperand const& rhs) const
{
    return (this->toString() == rhs.toString() && this->getType() == rhs.getType());
}


std::string IOperand::getTypeName(void) const
{
    return TypeNames[this->getType()];
}

MyException::MyException(const std::string& message, bool _exitCode)
    : std::exception(message.c_str())
{
    exitCode = _exitCode;
}
