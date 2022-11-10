#include "Include/InputParser.hpp"

void InputParser::parseLine(const string &line)
{
    vector<string> expression;
    bool equals_seen = false;
    string obj;
    string curr;
    bool nonSpaceSeen = false;
    for (const auto &ch : line)
    {
        if(!isspace(ch))
        {
            nonSpaceSeen = true;
        }

        if (isspace(ch)) // we don't care about whitespace
        {
            if(!nonSpaceSeen) // first char has to be non-whitespace
            {
                throw exception();
            }
            if (!obj.empty()) // but we want to push whatever was in our obj
            {
                validObj(expression, obj);
                expression.push_back(obj);
                obj.clear();
            }
        }
        else if (objId.isOp(ch)) // op are always only 1 char
        {
            if (!obj.empty()) // we stored something before the op
            {
                validObj(expression, obj);
                expression.push_back(obj);
                obj.clear();
            }
            // otherwise saw a space brefore this
            obj += ch;
            expression.push_back(obj);
            obj.clear();
        }
        else if (ch == '=') // appears when assigning vars
        {
            // = is valid only once, at the beginning, after a var
            // there cannot be a space btw - name_of_var - and - = - (obj will be empty in that case)
            // and obj cannot start with $ in this case
            if (!obj.empty() && !objId.isNumber(obj, true) &&
                !equals_seen && expression.empty() && obj[0] != '$')
            {
                validObj(expression, obj);
                expression.push_back(obj);
                expression.push_back("=");
                obj.clear();
                equals_seen = true;
            }
            else
            {
                throw exception();
            }
        }
        else if (isalpha(ch) || ch == '$' || isdigit(ch) || ch == '.') // valid char, never a separator
        {
            obj += ch;
        }
        else
        {
            throw exception();
        }
    }
    if (!obj.empty())
    {
        validObj(expression, obj);
        expression.push_back(obj);
    }
    if (expression.size() == 1 && objId.isVar(expression[0]) && expression[0][0] != '$')
    {
        // just one var is a valid expression only if we call an already assigned var
        throw exception();
    }

    // handle '-' properly
    handleUnary(expression);
}

void InputParser::validObj(const vector<string> &expression, const string &obj) const
{
    // check if our object is a number or a valid var
    // (var existance is checked later when evaluating)

    if (!objId.isNumber(obj))
    {
        if (!objId.isVar(obj) || (!expression.empty() && obj[0] != '$'))
        {
            throw exception();
        }
    }
}

void InputParser::handleUnary(vector<string> &expression)
{
    vector<string> new_expression;
    size_t index = 0;
    size_t last_elem = expression.size() - 1;
    while (index < last_elem)
    {
        // current is a - and next one is a number
        if (expression[index] == "-" && objId.isNumber(expression[index + 1]))
        {
            // eg. [-,3,...]
            if (index == 0)
            {
                new_expression.push_back('-' + expression[index + 1]);
                index += 2;
                continue;
            }
            // previous elem of expression was a op or a var assignment,
            else if (objId.isOp(expression[index - 1][0]) ||
                     (index == 2 && expression[index - 1] == "="))
            {
                new_expression.push_back('-' + expression[index + 1]);
                index += 2;
                continue;
            }
        }
        // -() or (-())
        // ()-() doesnt need any additions
        else if (expression[index] == "-" && expression[index + 1] == "(")
        {
            if (index == 0 || expression[index - 1] == "(" || (index == 2 && expression[index - 1] == "="))
            {
                new_expression.push_back("-1");
                new_expression.push_back("*");
                index++;
                continue;
            }
        }
        //eg. 3() or $var()
        else if ((objId.isNumber(expression[index]) || objId.isVar(expression[index])) && expression[index + 1] == "(")
        {
            new_expression.push_back(expression[index]);
            new_expression.push_back("*");
            index++;
            continue;
        }
        new_expression.push_back(expression[index]);
        index++;
    }
    // push last element
    if (index == last_elem)
    {
        new_expression.push_back(expression[last_elem]);
    }
    expressions.push_back(new_expression);
}
