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
    double ans = strtod(args[1], NULL);

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
    // declarations
    vector<double> nums;
    vector<char*> opers;

    // populate vectors
    for (int i = 2; i < argc; i += 2)
        nums.push_back(strtod(args[i],NULL));
    for (int i = 3; i < argc; i += 2)
        opers.push_back(args[i]);

    // exponents
    int pass = 1;
    bool done = false;
    while (!done)
    {
        cout << "Calculating Exponents - Pass " << pass++ << endl;
        int changes = 0;
        for (int i = 0; i < opers.size(); i++)
        {
            int pos1 = i, pos2 = i + 1;
            if (!strcmp(opers.at(i), "^"))
            {
                nums.at(pos1) = pow(nums.at(pos1),nums.at(pos2));
                nums.erase(nums.begin()+pos2);
                opers.erase(opers.begin()+(i));
                changes++;
                break;
            } 
        }
        if (changes > 1)
        {
            cout << "Not breaking operation loop properly. Loops: " << changes << endl;
            return -4;
        }
        if (changes == 0) done = true;
    } 

    // multiply and divide
    pass = 1;
    done = false;
    while (!done)
    {
        cout << "Multiplying and Dividing - Pass " << pass++ << endl;
        int changes = 0;
        for (int i = 0; i < opers.size(); i++)
        {
            int pos1 = i, pos2 = i + 1;
            if (!strcmp(opers.at(i), "x"))
            {
                nums.at(pos1) *= nums.at(pos2);
                nums.erase(nums.begin()+pos2);
                opers.erase(opers.begin()+(i));
                changes++;
                break;
            } else if (!strcmp(opers.at(i), "/"))
            {
                nums.at(pos1) /= nums.at(pos2);
                nums.erase(nums.begin()+pos2);
                opers.erase(opers.begin()+(i));
                changes++;
                break;
            }
        }
        if (changes > 1)
        {
            cout << "Not breaking operation loop properly. Loops: " << changes << endl;
            return -4;
        }
        if (changes == 0) done = true;
   } 

    pass = 1;
    done = false;
    while (!done)
    {
        cout << "Adding and Subtracting - Pass " << pass++ << endl;
        int changes = 0;
        for (int i = 0; i < opers.size(); i++)
        {
            int pos1 = i, pos2 = i + 1;
            if (!strcmp(opers.at(i), "+"))
            {
                nums.at(pos1) += nums.at(pos2);
                nums.erase(nums.begin()+pos2);
                opers.erase(opers.begin()+(i));
                changes++;
                break;
            } else if (!strcmp(opers.at(i), "-"))
            {
                nums.at(pos1) -= nums.at(pos2);
                nums.erase(nums.begin()+pos2);
                opers.erase(opers.begin()+(i));
                changes++;
                break;
            }
        }
        if (changes > 1)
        {
            cout << "Not breaking operation loop properly. Loops: " << changes << endl;
            return -4;
        }
        if (changes == 0) done = true;
   }

    cout << "The answer is: " << nums.at(0) << endl;
    return 0;
}

Calculator::~Calculator()
{}
