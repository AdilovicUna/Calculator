#include "InputParser.hpp"

void InputParser::parseLine(const string &line)
{
    vector<string> expression;
    bool equals_seen = false;
    string s;
    string curr;
    for (const auto &ch : line)
    {
        if (isspace(ch)) // we don't care about whitespace
        {
            if (!s.empty())
            {
                validPushBack(expression, s);
                expression.push_back(s);
                s.clear();
            }
        }
        else if (h.isOp(ch)) // op are always only 1 char
        {
            if (!s.empty()) // we had something before
            {
                validPushBack(expression, s);
                expression.push_back(s);
                s.clear();
            }
            // otherwise before we had a space
            s += ch;
            expression.push_back(s);
            s.clear();
        }
        else if (ch == '=') // appears when assigning vars
        {
            // = is valid only once, at the beginning
            // after a var, and there cannot be a space
            // btw name_of_var and = (s will be empty in that case)
            // and s cannot start with $ in this case
            if (!s.empty() && !h.isNumber(s, true) &&
                !equals_seen && expression.empty() && s[0] != '$')
            {
                validPushBack(expression, s);
                s += '=';
                expression.push_back(s);
                s.clear();
                equals_seen = true;
            }
            else
            {
                throw exception();
            }
        }
        else if (isalpha(ch) || ch == '$' || isdigit(ch) || ch == '.') // valid char, never a separator
        {
            s += ch;
        }
        else
        {
            throw exception();
        }
    }
    if (!s.empty())
    {
        validPushBack(expression, s);
        expression.push_back(s);
    }
    handleUnary(expression);
}

void InputParser::validPushBack(const vector<string> &expression, const string &s) const
{
    if (!h.isNumber(s))
    {
        if (!h.isVar(s) || (!expression.empty() && s[0] != '$'))
        {
            throw exception();
        }
    }
}

void InputParser::handleUnary(vector<string> expression)
{
    vector<string> new_expression;
    size_t index = 0;
    size_t last_elem = expression.size() - 1;
    while (index < last_elem)
    {
        // current is a - and next one is a number
        if(expression[index] == "-" && h.isNumber(expression[index + 1]))
        {
            // eg. [-,3,...]
            if (index == 0)
            {
                new_expression.push_back('-' + expression[index + 1]);
                index += 2;
                continue;
            }
            // previous elem of expression was a op or a var assignment,
            else if (h.isOp(expression[index - 1][0]) ||
                    (index == 1 && expression[0][expression[0].size() - 1] == '='))
            {
                new_expression.push_back('-' + expression[index + 1]);
                index += 2;
                continue;
            }
        }
        // -() or (-())
        // ()-() doesnt need any additions
        else if(expression[index] == "-" && expression[index + 1] == "(")
        {
            if(index == 0 || expression[index-1] == "(")
            {
                new_expression.push_back("-1");
                new_expression.push_back("*");
                index++;
                continue;
            }
        }
        new_expression.push_back(expression[index]);
        index++;
    }
    // push last element
    if(index == last_elem)
    {
        new_expression.push_back(expression[last_elem]);
    }
    expressions.push_back(new_expression);
}
