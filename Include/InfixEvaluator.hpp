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

    const T getNumValue(const string &i) const;
    const T getVarValue(const string &i, map<string, pair<int, variant<int, float, double>>> &vars) const;

    const T applyOp(T a, T b, char op) const;
    int precOp(char op) const;
    void executeBinary();

public:
    T result;
    InfixEvaluator(const vector<string> &expr, map<string, pair<int, variant<int, float, double>>> &vars);
};