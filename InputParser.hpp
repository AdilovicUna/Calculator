#pragma once

#include "ObjectIdentifier.hpp"
#include <string>
#include <vector>

class InputParser
{
private:
    ObjectIdentifier objId;
    void validObj(const vector<string> &expression, const string &s) const;
    void handleUnary(vector<string> expression);

public:
    vector<vector<string>> expressions;
    void parseLine(const string &line);
};