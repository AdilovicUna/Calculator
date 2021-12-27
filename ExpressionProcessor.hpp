#pragma once

#include <variant>
#include <string>
#include <vector>
#include <map>
#include "Helper.hpp"
using namespace std;

class ExpressionProcessor
{
private:
    Helper h;
    map<string,variant<int, double, float>> vars;
    int getType(const vector<string> &expr);
    // T calculate(const vector<string> &expr, T type);
public:
    variant<int, double, float, string> processExpression(const vector<string> &expr);
};