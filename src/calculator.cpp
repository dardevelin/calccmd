#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cmath>

#include "calculator.h"

using namespace std;

bool orderly;
int argc;
char** args;

Calculator::Calculator(bool b, int c, char** a)
{
    orderly = b;
    argc = c;
    args = a;
}

void Calculator::printUsage(char** argv)
{
    cout << "Usage: " << argv[0] << " [OPTIONS] <num1> <operation> <num2> [operation] [num3] . . ." << endl;
    cout << "Do `" << argv[0] << " --help` for further instructions." << endl; 
}

int Calculator::exec()
{
    if (!orderly) return classicCalc();
    else return orderedCalc();
    // something derped
    return -2;
}

int Calculator::classicCalc()
{
    // declarations
    vector<signed char> opers;
    double ans = strtod(args[1], NULL);

    // populate operation list
    for (int i = 2; i < argc; i += 2)
    {
        signed char oper = 0;
        if (!strcmp(args[i], "+")) oper = 1;
        else if (!strcmp(args[i], "-")) oper = 2;
        else if (!strcmp(args[i], "x")) oper = 3;
        else if (!strcmp(args[i], "/")) oper = 4;
        else if (!strcmp(args[i], "^")) oper = 5;

        if (oper != 0) opers.push_back(oper);
        else
        {
            printUsage(args);
            return -3;
        }
    }

    for(int i=2;i<argc;i+=2)
    {
        if (!strcmp(args[i], "+"))
        {
            ans += strtod(args[i+1],NULL);
        }
        else if (!strcmp(args[i], "-"))
        {
            ans -= strtod(args[i+1],NULL);
        }
        else if (!strcmp(args[i], "x"))
        {
            ans *= strtod(args[i+1],NULL);
        }
        else if (!strcmp(args[i], "/"))
        {
            ans /= strtod(args[i+1],NULL);
        }
        else if (!strcmp(args[i], "^"))
        {
            ans = pow(ans,strtod(args[i+1],NULL));
        }
    }

    cout << "The answer is: " << ans << endl;
    return 0;
}

int Calculator::orderedCalc()
{
    return 0;
}

Calculator::~Calculator()
{}
