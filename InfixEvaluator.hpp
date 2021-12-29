#pragma once

#include <variant>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include "Helper.hpp"

using namespace std;

#include<iostream>

template <typename T>
class InfixEvaluator
{
private:
    Helper h;
    T getNumValue(const string &i);
    T getVarValue(const string &i, map<string, pair<int, variant<int, float, double>>> &vars);

    inline int precOp(char op)
    {
        if (op == '+' || op == '-')
            return 1;
        if (op == '*' || op == '/' || op == '%')
            return 2;
        return 0;
    }

    inline T applyOp(T a, T b, char op)
    {
        switch (op)
        {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        default:
            throw exception();
        }
    }

public:
    T result;
    InfixEvaluator(const vector<string> &expr, map<string, pair<int, variant<int, float, double>>> &vars);
};