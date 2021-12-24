#pragma once

#include <string>
using namespace std;

class Helper
{
public:
    inline bool isOp(char ch) const
    {
        return ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
               ch == '%' || ch == '(' || ch == ')';
    }

    inline bool isNumber(const string &s, bool building = false) const
    {
        bool dot_found = false;
        auto it = s.begin();
        if(*it == '.') // eg. ".34" isn't allowed
        {
            return false;
        }
        while (it != s.end() &&
               (isdigit(*it) || (*it == '.' && !dot_found)))
        {
            if (*it == '.')
            {
                dot_found = true;
            }
            it++;
        }
        if (!building && s[s.length()-1] == '.')
        {
            return false;
        }
        return !s.empty() && it == s.end();
    }

    inline bool isVar(const string &s) const
    {
        auto it = s.begin();
        if(*it == '$') // $ can only be at the beginning
        {
            it++;
        }
        while (it != s.end() && isalpha(*it))
        {
            it++;
        }
        return !s.empty() && it == s.end();
    }
};