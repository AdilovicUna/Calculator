#include "InfixEvaluator.hpp"

template <typename T>
InfixEvaluator<T>::InfixEvaluator(const vector<string> &expr, map<string, pair<int, variant<int, float, double>>> &vars)
{
    try
    {
        stack<T> values;
        stack<char> ops;

        for (const auto &e : expr)
        {
            if (e == "(")
            {
            //cout<<"7"<<endl;
                ops.push(e[0]);
            }
            else if (h.isNumber(e))
            {
            //cout<<"8"<<endl;
                values.push(getNumValue(e));
            }
            else if (h.isVar(e))
            {
            //cout<<"9"<<endl;
                values.push(getVarValue(e, vars));
            }
            else if (e == ")")
            {
                //get everything inside ()
            //cout<<"10"<<endl;
                while (!ops.empty() && ops.top() != '(')
                {
            //cout<<"11"<<endl;
                    T v2 = values.top();
                    values.pop();

                    T v1 = values.top();
                    values.pop();

                    char op = ops.top();
                    ops.pop();

                    values.push(applyOp(v1, v2, op));
                }

                if (!ops.empty())
                    ops.pop();
            }
            else
            {
            //cout<<"12"<<endl;
                // find op with biggest precidence
                while (!ops.empty() && precOp(ops.top()) >= precOp(e[0]))
                {
            //cout<<"13"<<endl;
                    T v2 = values.top();
                    values.pop();

                    T v1 = values.top();
                    values.pop();

                    char op = ops.top();
                    ops.pop();

                    values.push(applyOp(v1, v2, op));
                }
                ops.push(e[0]);
            }
        }
        while (!ops.empty())
        {
            //cout<<"14"<<endl;
            T v2 = values.top();
            values.pop();

            T v1 = values.top();
            values.pop();

            char op = ops.top();
            ops.pop();

            values.push(applyOp(v1, v2, op));
        }
        result = values.top();
    }
    catch (const exception &e)
    {
            //cout<<"2"<<endl;
        throw exception();
    }
}
template <typename T>
T InfixEvaluator<T>::getNumValue(const string &i)
{
            //cout<<"5"<<endl;
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
            //cout<<"3"<<endl;
    throw exception();
}

template <typename T>
T InfixEvaluator<T>::getVarValue(const string &i, map<string, pair<int, variant<int, float, double>>> &vars)
{
            //cout<<"6"<<endl;
    switch (vars[i].first)
    {
    case 0:
        return getNumValue(to_string(get<int>(vars[i].second)));
    case 1:
        return getNumValue(to_string(get<float>(vars[i].second)));
    case 2:
        return getNumValue(to_string(get<double>(vars[i].second)));
    default:
            //cout<<"4"<<endl;
        throw exception();
    }
}

template class InfixEvaluator<int>;
template class InfixEvaluator<float>;
template class InfixEvaluator<double>;