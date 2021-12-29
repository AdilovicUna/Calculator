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
        bool f_found = false;
        auto it = s.begin();
        if(*it == '.') // eg. ".34" isn't allowed
        {
            return false;
        }
        while (it != s.end() &&
               (isdigit(*it) || (*it == '.' && !dot_found) || (*it == 'f' && !f_found)))
        {
            if (*it == '.')
            {
                dot_found = true;
            }
             if (*it == 'f')
            {
                f_found = true;
            }
            it++;
        }
        if (!building && s[s.length()-1] == '.') // . has to be in the middle
        {
            return false;
        }
        if(f_found && s[s.length()-1] != 'f') // f can only be at the end (indicates float)
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
        // expressions such as 2&var aren't allowed
        while (it != s.end() && isalpha(*it))
        {
            it++;
        }
        return !s.empty() && it == s.end();
    }
};