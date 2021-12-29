#include "ExpressionProcessor.hpp"

variant<int, float, double, string> ExpressionProcessor::processExpression(vector<string> &expr)
{
    if (expr.size() == 1)
    {
        if (!h.isVar(expr[0]))
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
                //cout<<"6"<<endl;

                throw exception();
            }
        }
        //cout<<"7"<<endl;

        // if nothing is returned from previous code, there is an error in the expression
        throw exception();
    }
    // assignment to a valid var
    string assign_to;
    if (expr[1] == "=")
    {
        //cout<<"1"<<endl;
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
    int type = getType(expr);
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
        //cout<<"D"<<endl;
        if (!assign_to.empty())
            vars.insert(make_pair(assign_to, make_pair(2, evalD.result)));
        return evalD.result;
        break;
    }
    default:
        //cout<<"2"<<endl;

        throw exception();
        break;
    }
    //cout<<"3"<<endl;

    throw exception();
}

int ExpressionProcessor::getType(const vector<string> &expr)
{
    int type = -1;
    int curr_type = -1;
    for (const auto &e : expr)
    {
        if (h.isNumber(e))
        {
            curr_type = getNumberType(e);
        }
        else if (h.isVar(e))
        {
            // since we loop trought the whole expression, we are sure every var exists
            // unless this function doesn't throw an exception
            if (vars.find(e) != vars.end())
            {
                curr_type = vars[e].first;
                //cout << curr_type << "*" << endl;
            }
            else
            {
                  //cout<<"4"<<endl;
                throw exception(); // invalid var, not yet assigned
            }
        }
        if (curr_type > type)
        {
            type = curr_type;
        }
    }
                  //cout<<"5"<<endl;
    //cout << type << "*" << endl;
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
