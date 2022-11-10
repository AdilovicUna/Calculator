#pragma once

#include <string>
using namespace std;

class ObjectIdentifier
{
public:
    bool isOp(char ch) const;

    bool isNumber(const string &s, bool building = false) const;

    bool isVar(const string &s) const;
};