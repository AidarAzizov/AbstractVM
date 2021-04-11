#include "AbstractVM.h"
#include "Operation.h"

bool wasMistake;


void deleteComment(std::string& row)
{
    size_t res = row.find_first_of(";");
    if (res != std::string::npos) row.erase(res, row.size() - res);

    res = row.find_last_not_of(" ");
    if (res != std::string::npos) row.erase(res + 1, row.size() - res - 1);
    else if (row[0] == ' ') row.clear();
}
void deletePositiveSign(std::string& row)
{
    if (row[0] == '+') row.erase(0, 1);
}

void closestack(std::stack<const IOperand*>& MyStack)
{
    while (!MyStack.empty())
    {
        auto temp = MyStack.top(); MyStack.pop();
        delete[] temp;
    }
}
void mainOverflow(const std::string& row)
{
    auto first = row.find("(");
    auto second = row.find(")");

    if (first == std::string::npos) return;
    if (second - first > MAX_COUNT_NUM) throw MyException("");
}
void checkEOF(std::string& row)
{
    size_t pos1 = row.find_first_not_of(" ");
    size_t pos2 = row.find(";;");
    if (pos1 == pos2 && pos1 != std::string::npos) row = "exit";
}

bool Run(std::map<std::string, Fptr>& pubOperations,
    std::map<std::string, Fptr>& pubOthers,
    std::map<std::string, eOperandType>& pubTypes,
    const std::string & filename)
{
    std::ifstream in(filename);
    if (!in.is_open()) return printAndExit(false, "Can't open file");

    bool return_value = false;
    std::stack<const IOperand*> MyStack;

    std::stringstream ErrorMessage;
    std::string Num; Num.resize(MAX_COUNT_NUM);
    std::string Operation; Operation.resize(MAX_COUNT_NUM);
    std::string Type; Type.resize(MAX_COUNT_NUM);
    std::string row; size_t i = 1;
    std::string notEmptyCopyRow;
    for (; getline(in, row); i++)
    {
        try
        {
            checkEOF(row);
            deleteComment(row);
            if (row.empty()) continue;
            notEmptyCopyRow = row;
            if (row.size() > MAX_COUNT_NUM) throw MyException("Overflowed.");

            char symb;
            if (sscanf(row.c_str(), " push %[^(](%[^)])%c", &Type[0], &Num[0], &symb) == 2)
            {
                deletePositiveSign(Num);
                mainOverflow(row);
                if (pubTypes.count(Type.c_str()) != 1)
                    throw MyException("Bad data type(" + std::string(Type.c_str()) + ") for push operation.");
                MyStack.push(Creator(Num, pubTypes[Type.c_str()]));
            }
            else if (sscanf(row.c_str(), " assert %[^(](%[^)])%c", &Type[0], &Num[0], &symb) == 2)
            {
                mainOverflow(row);
                if (pubTypes.count(Type.c_str()) != 1)
                    throw MyException("Bad data type(" + std::string(Type.c_str()) + ") for assert operation.");
                MyStack.push(Creator(Num, pubTypes[Type.c_str()]));
                pubOthers["assert"](MyStack);
            }
            else if (sscanf(row.c_str(), " %s %c", &Operation[0], &symb) == 1)
            {
                if (pubOperations.count(Operation.c_str()) == 1)
                    pubOperations[Operation.c_str()](MyStack);
                else if (pubOthers.count(Operation.c_str()) == 1)
                    pubOthers[Operation.c_str()](MyStack);
                else throw MyException("Invalid.");
            }
            else throw MyException("Invalid.");
        }
        catch (MyException& ex)
        {
            if (!ex.GetCode())
            {
                return_value = false; wasMistake = true;
                ErrorMessage << "Line " << i << ". " << ex.what() << "\n";
            }
            else { return_value = true; break; }
        }
    }

    if (!ErrorMessage.str().empty())
        std::cout << ErrorMessage.str();
    
    if (!return_value && notEmptyCopyRow.find("exit") 
        == std::string::npos)
    {
        std::cout << "Expected exit command or symbol." << std::endl;
        return_value = false;
    }
    closestack(MyStack); in.close();
    return return_value;
}


int main()
{
    std::map<std::string, Fptr> pubOperations;
    std::map<std::string, Fptr> pubOthers;
    std::map<std::string, eOperandType> pubTypes;
    initPubs(pubOperations, pubOthers, pubTypes);

    wasMistake = false;

    if (!Run(pubOperations, pubOthers, pubTypes,
        "D:\\Users\\Aidar Azizov\\Desktop\\Projects\\AbstractVM\\example.avm"))
        return ERROR_CODE;

    return SUCCESS_CODE;
}
