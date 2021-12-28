#include "ExpressionProcessor.hpp"

variant<int, double, float, string> ExpressionProcessor::processExpression(vector<string> &expr)
{
    if(expr.size() == 1)
    {
        if(!h.isVar(expr[0]))
        {
            // if expr only contains ["invalid"] or some number (eg. 3.94)
            // no need to convert the number since we will just print it
            return expr[0];
        }
        else if(vars.find(expr[0]) != vars.end())
        {
            // if expr is a var and already assigned to
            visit([](const auto &x) { return x; }, vars[expr[0]]);
        }
        // if nothing is returned from previous code, there is an error in the expression
        throw exception();

    }
    // assignment to a valid var
    string assign_to;
    if(expr[1] == "=" ) 
    {
        if(vars.find(expr[0]) == vars.end())
        {
            throw exception();
        }
        assign_to = expr[0]; // vars are saved with $
        expr.erase(expr.begin());
        expr.erase(expr.begin());
    }
    // just an expression
    int type = getType(expr);
    switch(type)
    {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        default:
            throw exception();
    }
}

int ExpressionProcessor::getType(const vector<string> &expr)
{
    int type = -1;
    int curr_type = -1;
    for(const auto &e : expr)
    {
        if(h.isNumber(e))
        {
            curr_type = getNumberType(e);
        }
        else if(h.isVar(e))
        {
            // since we loop trought the whole expression, we are sure every var exists
            // unless this function doesn't throw an exception
            if(vars.find(expr[0]) != vars.end())
            {
                curr_type = vars[expr[0]].first;
                continue;
            }
            throw exception(); // invalid var, not yet assigned
        }
        if(curr_type > type)
        {
            type = curr_type;
        }
    }
    return type != -1 ? type : throw exception();
}

int ExpressionProcessor::getNumberType(const string &num)
{
    int type = -1;
    try
    {
        stod(num);
        type = 2;
        stof(num);
        type = 1;
        stoi(num);
        return 0;
    }
    catch(const std::exception& e)
    {
        return type != -1 ? type : throw exception();
    }
}
