#include "InfixEvaluator.hpp"

template <typename T>
InfixEvaluator<T>::InfixEvaluator(const vector<string> &expr, map<string, pair<int, variant<int, float, double>>> &vars)
{
    try
    {
        for (const auto &e : expr)
        {
            if (e == "(")
            {
                ops.push(e[0]);
            }
            else if (objId.isNumber(e))
            {
                values.push(getNumValue(e));
            }
            else if (objId.isVar(e))
            {
                values.push(getVarValue(e, vars));
            }
            else if (e == ")")
            {
                // we have an extra - ) -
                if (ops.empty())
                {
                    throw exception();
                }

                //get everything inside ()
                while (!ops.empty() && ops.top() != '(')
                {
                    executeBinary();
                }

                // pop - ( -
                if (!ops.empty())
                    ops.pop();
            }
            else
            {
                // find op with biggest precidence
                while (!ops.empty() && precOp(ops.top()) >= precOp(e[0]))
                {
                    executeBinary();
                }
                ops.push(e[0]);
            }
        }
        //get rest of the operators
        while (!ops.empty())
        {
            executeBinary();
        }

        // we have some extra numbers
        if (values.size() != 1)
        {
            throw exception();
        }
        // asign the result
        result = values.top();
    }
    catch (const exception &e)
    {
        throw exception();
    }
}

template <typename T>
const T InfixEvaluator<T>::getNumValue(const string &i) const
{
    if (is_same_v<T, int>)
    {
        return stoi(i);
    }
    else if (is_same_v<T, float>)
    {
        return stof(i);
    }
    else if (is_same_v<T, double>)
    {
        return stod(i);
    }
    throw exception();
}

template <typename T>
const T InfixEvaluator<T>::getVarValue(const string &i, map<string, pair<int, variant<int, float, double>>> &vars) const
{
    switch (vars[i].first)
    {
    case 0:
        return getNumValue(to_string(get<int>(vars[i].second)));
    case 1:
        return getNumValue(to_string(get<float>(vars[i].second)));
    case 2:
        return getNumValue(to_string(get<double>(vars[i].second)));
    default:
        throw exception();
    }
}

template <typename T>
const T InfixEvaluator<T>::applyOp(T a, T b, char op) const
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        if (b == 0)
        {
            throw exception();
            break;
        }
        return a / b;
    case '%':
        if (b == 0 || is_same_v<T, float> || is_same_v<T, double>)
        {
            throw exception();
            break;
        }
        return int(a) % int(b);
    default:
        throw exception();
    }
}

template <typename T>
int InfixEvaluator<T>::precOp(char op) const
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/' || op == '%')
        return 2;
    return 0;
}

template <typename T>
void InfixEvaluator<T>::executeBinary()
{
    try
    {
        if (values.size() < 2 || ops.empty())
        {
            throw exception();
        }
        T v2 = values.top();
        values.pop();

        T v1 = values.top();
        values.pop();

        char op = ops.top();
        ops.pop();

        values.push(applyOp(v1, v2, op));
    }
    catch (const exception &e)
    {
        throw exception();
    }
}

template class InfixEvaluator<int>;
template class InfixEvaluator<float>;
template class InfixEvaluator<double>;