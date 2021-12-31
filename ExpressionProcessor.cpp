#include "ExpressionProcessor.hpp"

variant<int, float, double, string> ExpressionProcessor::processExpression(vector<string> &expr)
{
    if (expr.size() == 1)
    {
        if (!objId.isVar(expr[0]))
        {
            // if expr only contains ["invalid"] or some number (eg. 3.94)
            // no need to convert the number since we will just print it
            return expr[0];
        }
        else if (vars.find(expr[0]) != vars.end())
        {
            // if expr is a var and already assigned to
            // return value of the var
            switch (vars[expr[0]].first)
            {
            case 0:
                return get<0>(vars[expr[0]].second);
            case 1:
                return get<1>(vars[expr[0]].second);
            case 2:
                return get<2>(vars[expr[0]].second);
            default:
                throw exception();
            }
        }

        // if nothing is returned from previous code, there is an error in the expression
        throw exception();
    }
    // assignment to a valid var
    string assign_to;
    if (expr[1] == "=")
    {
        if (vars.find(expr[0]) != vars.end())
        {
            throw exception();
        }
        assign_to = "$" + expr[0]; // vars are saved with $

        // remove name of the var and = sign from expr
        expr.erase(expr.begin());
        expr.erase(expr.begin());
    }
    // just an expression
    int type = getExprType(expr);
    switch (type)
    {
    case 0:
    {
        InfixEvaluator<int> evalI(expr, vars);
        if (!assign_to.empty())
            vars.insert(make_pair(assign_to, make_pair(0, evalI.result)));
        return evalI.result;
        break;
    }
    case 1:
    {
        InfixEvaluator<float> evalF(expr, vars);
        if (!assign_to.empty())
            vars.insert(make_pair(assign_to, make_pair(1, evalF.result)));
        return evalF.result;
        break;
    }
    case 2:
    {
        InfixEvaluator<double> evalD(expr, vars);
        if (!assign_to.empty())
            vars.insert(make_pair(assign_to, make_pair(2, evalD.result)));
        return evalD.result;
        break;
    }
    default:
        throw exception();
        break;
    }
    throw exception();
}

int ExpressionProcessor::getExprType(const vector<string> &expr)
{
    // we want to find the "biggest" type in order to convert everything to it
    // eg. int + float will become float + float
    int type = -1;
    int curr_type = -1;
    for (const auto &e : expr)
    {
        if (objId.isNumber(e))
        {
            curr_type = getNumberType(e);
        }
        else if (objId.isVar(e))
        {
            // since we loop trought the whole expression, we are sure every var exists
            // unless this function doesn't throw an exception
            if (vars.find(e) != vars.end())
            {
                curr_type = vars[e].first;
            }
            else
            {
                throw exception(); // invalid var, not yet assigned
            }
        }
        if (curr_type > type)
        {
            type = curr_type;
        }
    }
    return type != -1 ? type : throw exception();
}

int ExpressionProcessor::getNumberType(const string &num)
{
    if (num.find('.') != string::npos)
    {
        if (num.find('f') != string::npos)
        {
            return 1;
        }
        return 2;
    }
    return 0;
}
