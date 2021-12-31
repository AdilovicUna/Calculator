#pragma once

#include "InfixEvaluator.hpp"
#include <typeinfo>

class ExpressionProcessor
{
private:
    ObjectIdentifier objId;
    // maps name of a var with its type (int representation) and the value
    // int = 0, double = 1, float = 2
    map<string, pair<int, variant<int, float, double>>> vars;
    int getExprType(const vector<string> &expr);
    int getNumberType(const string &num);

public:
    variant<int, float, double, string> processExpression(vector<string> &expr);
};