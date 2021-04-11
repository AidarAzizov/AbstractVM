#pragma once

#include <iostream>
#include <cstring>


class MyException : public std::exception
{
    bool exitCode;

public:
    MyException(const std::string& message, bool _exitCode = false);
    bool GetCode() const { return exitCode; }
};

