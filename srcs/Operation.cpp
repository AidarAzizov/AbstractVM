#include "Operation.h"

extern bool wasMistake;


void dump(std::stack<const IOperand*>& MyStack)
{
    std::stack<const IOperand*> tempStack;

    if (wasMistake) return;
    while (!MyStack.empty())
    {
        auto temp = MyStack.top(); MyStack.pop();
        std::cout << temp->getTypeName() << "\t-> " << temp->toString() << std::endl;
        tempStack.push(temp);
    }
    while (!tempStack.empty())
    {
        auto temp = tempStack.top(); tempStack.pop();
        MyStack.push(temp);
    }

}
void __exit(std::stack<const IOperand*>& MyStack)
{
    throw MyException("Good exit.", true); 
}
void print(std::stack<const IOperand*>& MyStack)
{
    if (MyStack.size() < 1) throw MyException("Stack is empty.");
    auto temp = MyStack.top();
    if (temp->getType() != Int8) 
        throw MyException("Bad 'print' command.\nValue at the top of the stack is not int8.");
    if (!wasMistake) 
        std::cout << (char)atoi(temp->toString().c_str()) << std::endl;
}
void pop(std::stack<const IOperand*>& MyStack) 
{
    if (MyStack.size() < 1) throw MyException("Stack is empty.");
    if (wasMistake) return;

    auto temp = MyStack.top(); MyStack.pop();
    delete[] temp;
}
void assert(std::stack<const IOperand*>& MyStack)
{
    if (MyStack.size() < 2) throw MyException("Error 'assert' operation.\nStack is too small");
    if (wasMistake) return;

    auto first = MyStack.top(); MyStack.pop();
    auto second = MyStack.top();

    if (!(*first == *second)) throw MyException("'assert' operation is not true.");
    delete[] first;
}

void mul(std::stack<const IOperand*>& MyStack)
{
    if (MyStack.size() < 2) throw MyException("Bad mul. Stack is too small.");

    auto second = MyStack.top(); MyStack.pop();
    auto first = MyStack.top(); MyStack.pop();
    MyStack.push((*first) * (*second));
    delete[] first; delete[] second;
}
void sub(std::stack<const IOperand*>& MyStack)
{
    if (MyStack.size() < 2) throw MyException("Bad sub. Stack is too small.");

    auto second = MyStack.top(); MyStack.pop();
    auto first = MyStack.top(); MyStack.pop();
    MyStack.push((*first) - (*second));
    delete[] first; delete[] second;
}
void mod(std::stack<const IOperand*>& MyStack)
{
    if (MyStack.size() < 2) throw MyException("Bad mod. Stack is too small.");

    auto second = MyStack.top(); MyStack.pop();
    auto first = MyStack.top(); MyStack.pop();
    MyStack.push((*first) % (*second));
    delete[] first; delete[] second;
}
void add(std::stack<const IOperand*>& MyStack)
{
    if (MyStack.size() < 2) throw MyException("Bad add. Stack is too small.");

    auto second = MyStack.top(); MyStack.pop();
    auto first = MyStack.top(); MyStack.pop();
    MyStack.push((*first) + (*second));
    delete[] first; delete[] second;
}
void _div(std::stack<const IOperand*>& MyStack)
{
    if (MyStack.size() < 2) throw MyException("Bad div. Stack is too small.");
    auto second = MyStack.top(); MyStack.pop();
    auto first = MyStack.top(); MyStack.pop();
    MyStack.push((*first) / (*second));
    delete[] first; delete[] second;
}


void initPubs(std::map<std::string, Fptr> &pubOperations,
    std::map<std::string, Fptr>& pubOthers,
    std::map<std::string, eOperandType>& pubTypes)
{
    pubOperations.emplace(std::make_pair("add", add));
    pubOperations.emplace(std::make_pair("div", _div));
    pubOperations.emplace(std::make_pair("sub", sub));
    pubOperations.emplace(std::make_pair("mod", mod));
    pubOperations.emplace(std::make_pair("mul", mul));

    pubOthers.emplace(std::make_pair("dump", dump));
    pubOthers.emplace(std::make_pair("print", print));
    pubOthers.emplace(std::make_pair("exit", __exit));
    pubOthers.emplace(std::make_pair("pop", pop));
    pubOthers.emplace(std::make_pair("assert", assert));


    pubTypes.emplace(std::make_pair("int8", Int8));
    pubTypes.emplace(std::make_pair("int16", Int16));
    pubTypes.emplace(std::make_pair("int32", Int32));
    pubTypes.emplace(std::make_pair("float", Float));
    pubTypes.emplace(std::make_pair("double", Double));
}
