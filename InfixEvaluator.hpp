#pragma once

#include <variant>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include "ObjectIdentifier.hpp"

template <typename T>
class InfixEvaluator
{
private:
    ObjectIdentifier objId;

    stack<T> values;
    stack<char> ops;

    T getNumValue(const string &i) const;
    T getVarValue(const string &i, map<string, pair<int, variant<int, float, double>>> &vars) const;

    T applyOp(T a, T b, char op);
    int precOp(char op);
    void executeBinary();

public:
    T result;
    InfixEvaluator(const vector<string> &expr, map<string, pair<int, variant<int, float, double>>> &vars);
};