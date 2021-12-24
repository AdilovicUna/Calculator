#include <iostream>
#include "InputParser.hpp"

bool isSpace(const string &line) 
{
    for (auto &&ch : line)
    {
        if(!isspace(ch))
        {
            return false;
        }
    }
    return true;
}

int main()
{

    int N;
    cin>>N;
    cin.ignore(256, '\n');

    string line;
    InputParser reader;
    vector<string> error(1,"invalid");
    while (N-- > 0)
    {
        try
        {
            getline(cin,line);
            if(isSpace(line)) // line with only whitespace is invalid as well
            {
                throw exception();
            }
            reader.parseLine(line);
        }catch (const exception &e)
        {
            reader.expressions.push_back(error);
        }
    }
    cout<<endl;
    cout<<"*****************"<<endl;
    for (size_t i = 0; i < reader.expressions.size(); i++)
    {
        cout<<"[";
        for (size_t j = 0; j < reader.expressions[i].size() - 1; j++)
        {
            cout <<reader.expressions[i][j]<<", ";
        }
         cout<<reader.expressions[i][reader.expressions[i].size() - 1]<<"]"<<endl;
    }
}
