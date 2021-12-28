#pragma once

#include <variant>
#include <string>
#include <vector>
#include <map>
#include <typeinfo>
#include "Helper.hpp"
using namespace std;

class ExpressionProcessor
{
private:
    Helper h;
    // maps name of a var with its type (int representation) and the value
    // int = 0, double = 1, float = 2
    map<string,pair<int,variant<int, double, float>>> vars;
    int getType(const vector<string> &expr);
    int getNumberType(const string &num);
    // vector<string>& prepareExpression(vector<string> &expr);
public:
    variant<int, double, float, string> processExpression(vector<string> &expr);
};