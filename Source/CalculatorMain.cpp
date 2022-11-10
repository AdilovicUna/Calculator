#include <iostream>
#include <sstream>
#include "Include/InputParser.hpp"
#include "Include/ExpressionProcessor.hpp"

bool isSpace(const string &line)
{
    for (auto &&ch : line)
    {
        if (!isspace(ch))
        {
            return false;
        }
    }
    return true;
}

bool isNum(const string &line)
{
    for (auto &&ch : line)
    {
        if (!isdigit(ch))
        {
            return false;
        }
    }
    return true;
}

int main()
{
    string firstLine;
    getline(cin, firstLine);

    // check the correctness of the first line
    if (!isNum(firstLine))
    {
        cout << "Invalid number of lines" << endl;
        return 0;
    }

    // convert to size_t
    stringstream sstream(firstLine);
    size_t N;
    sstream >> N;

    string line;
    InputParser reader;
    vector<string> error(1, "invalid");

    // parsing input
    while (N-- > 0)
    {
        try
        {
            getline(cin, line);
            if (isSpace(line)) // line with only whitespace is invalid as well
            {
                throw exception();
            }
            for_each(line.begin(), line.end(), [](char &c)
                     { c = ::tolower(c); });
            reader.parseLine(line);
        }
        catch (const exception &e)
        {
            reader.expressions.push_back(error);
        }
    }

    // proccess and print the output
    ExpressionProcessor processor;
    for (auto &expr : reader.expressions)
    {
        try
        {
            visit([](const auto &x)
                  { cout << x << endl; },
                  processor.processExpression(expr));
        }
        catch (const exception &e)
        {
            // if something goes wrong, we print invalid
            cout << error[0] << endl;
        }
    }
}
