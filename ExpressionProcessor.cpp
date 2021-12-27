#include "ExpressionProcessor.hpp"

variant<int, double, float, string> ExpressionProcessor::processExpression(const vector<string> &expr)
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
    }
    else if(expr.size() > 1 && expr[1] == "=")
    {
        if(vars.find(expr[0]) != vars.end())
        {
            
        }
    }
    return "invalid";

}