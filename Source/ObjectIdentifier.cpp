#include "Include/ObjectIdentifier.hpp"

bool ObjectIdentifier::isOp(char ch) const
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
           ch == '%' || ch == '(' || ch == ')';
}

bool ObjectIdentifier::isNumber(const string &s, bool building) const
{
    if (s.length() == 1 && !isdigit(s[0]))
    {
        return false;
    }

    auto it = s.begin();
    if (*it == '-')
    {
        it++;
    }
    bool dot_found = false;
    bool f_found = false;

    while (it != s.end() &&
           (isdigit(*it) || (*it == '.' && !dot_found) || (*it == 'f' && !f_found)))
    {
        if (*it == '.')
            dot_found = true;
        if (*it == 'f')
            f_found = true;
        it++;
    }
    if (!building && (s[0] == '.' || s[s.length() - 1] == '.')) // . has to be in the middle (unless we haven't seen the whole number yet)
    {
        return false;
    }
    if (f_found && s[s.length() - 1] != 'f') // f can only be at the end (indicates float)
    {
        return false;
    }
    return !s.empty() && it == s.end();
}

bool ObjectIdentifier::isVar(const string &s) const
{
    auto it = s.begin();
    if (*it == '$') // $ can only be at the beginning
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