#pragma once

#include <variant>
#include "Helper.hpp"
#include <string>
#include <vector>
using namespace std;

class InputParser
{
private:
    Helper h;
    void validPushBack(const vector<string> &expression,const string &s) const;
    void handleUnary(vector<string> expression);
public:
    vector<vector<string>> expressions;cd Des   
    void parseLine(const string &line);
};