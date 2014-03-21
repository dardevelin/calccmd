#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>

#include "calculator.hxx"
#include "option.hxx"

using namespace std;

vector<Option*> options;
bool option;
int argc;
char** args;

Calculator::Calculator(bool b, int c, char** a)
{
    option = b;
    argc = c;
    args = a;

    setDefaultOptions();
}

void Calculator::printUsage(char** argv)
{
    cout << "Usage: " << argv[0] << " [OPTIONS] <num1> <operation> <num2> [operation] [num3] . . ." << endl;
    cout << "Do `" << argv[0] << " --help` for further instructions." << endl; 
}

void Calculator::setDefaultOptions()
{
    options.push_back(new Option("classic"));
    options.push_back(new Option("verbose"));
}

void Calculator::cleanUp()
{
    for (unsigned int i = 0; i < options.size(); i++)
    {
        delete options.at(i);
        options.at(i) = NULL;
    }
}

int Calculator::exec()
{
    if (!checkArgs()) return -1;

    int code = 0;
    if (options.at(0)->isActive()) code = classicCalc();
    else  code = orderedCalc();
    return code;
}

int Calculator::classicCalc()
{
    if (options.at(1)->isActive())
        cout << "Calculating from left to right in single pass" << endl;

    // declarations
    double ans = strtod(args[2], NULL);

    for(int i=3;i<argc;i+=2)
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
    for (int i = option ? 2 : 1; i < argc; i += 2)
        nums.push_back(strtod(args[i],NULL));
    for (int i = option ? 3 : 2; i < argc; i += 2)
        opers.push_back(args[i]);

    // exponents
    int pass = 1;
    bool done = false;
    while (!done)
    {
        if (options.at(1)->isActive())
            cout << "Calculating Exponents - Pass " << pass++ << endl;
        int changes = 0;
        for (unsigned int i = 0; i < opers.size(); i++)
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
            cout << "Not breaking operation loop properly. Loops: "
                    << changes << endl;
            return -4;
        }
        if (changes == 0) done = true;
    } 

    // multiply and divide
    pass = 1;
    done = false;
    while (!done)
    {
        if (options.at(1)->isActive())
            cout << "Multiplying and Dividing - Pass " << pass++ << endl;
        int changes = 0;
        for (unsigned int i = 0; i < opers.size(); i++)
        {
            int pos1 = i, pos2 = i + 1;
            if (!strcmp(opers.at(i), "x"))
            {
                nums.at(pos1) *= nums.at(pos2);
                nums.erase(nums.begin()+pos2);
                opers.erase(opers.begin()+(i));
                changes++;
                break;
            }
            else if (!strcmp(opers.at(i), "/"))
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
            cout << "Not breaking operation loop properly. Loops: "
                    << changes << endl;
            return -4;
        }
        if (changes == 0) done = true;
   } 

    pass = 1;
    done = false;
    while (!done)
    {
        if (options.at(1)->isActive())
            cout << "Adding and Subtracting - Pass " << pass++ << endl;
        int changes = 0;
        for (unsigned int i = 0; i < opers.size(); i++)
        {
            int pos1 = i, pos2 = i + 1;
            if (!strcmp(opers.at(i), "+"))
            {
                nums.at(pos1) += nums.at(pos2);
                nums.erase(nums.begin()+pos2);
                opers.erase(opers.begin()+(i));
                changes++;
                break;
            }
            else if (!strcmp(opers.at(i), "-"))
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
            cout << "Not breaking operation loop properly. Loops: "
                    << changes << endl;
            return -4;
        }
        if (changes == 0) done = true;
   }

    cout << "The answer is: " << nums.at(0) << endl;
    return 0;
}

bool Calculator::checkArgs()
{
    // check number of arguments
    if ((option ? argc-1 : argc)%2 != 0 ||
        (option ? argc-2 : argc-1) == 0)
    {
        cout << "Invalid argument count.\n\n" << endl;
        printUsage(args);
        return false;
    }

    // parse options
    if (option)
    {
        char arg[(sizeof(args[1])/sizeof(args[1][0]))];
        unsigned int size = sizeof(arg) / sizeof(arg[0]);
        for (unsigned int i = 0; i < size; i++) arg[i] = args[1][i];
        if (size == 1 ||
            (size == 2 && arg[1] == '-'))
        {
            cout << "No options specified." << endl;
            return false;
        }
        else
        {
            bool longform = (arg[0] == '-' && arg[1] == '-');

            if (!longform)
            {
                for (unsigned int i = 0; i < options.size(); i++)
                {
                    for (unsigned int j = 1; j < size; j++)
                    {
                        if (arg[j] == options.at(i)->getAbbr())
                            options.at(i)->setActive(true);
                    }
                }
            }
            else
            {
                char name[size-2];
                for (unsigned int i = 0; i < (size-2); i++) name[i] = arg[i+2];

                for (unsigned int i = 0; i < options.size(); i++)
                {
                    if (name == options.at(i)->getName())
                        options.at(i)->setActive(true);
                }
            }
        }
    }

    // check operations
    for (int i = (option ? 3 : 2); i < argc; i+=2)
    {
        if (strcmp(args[i],"+") != 0 &&
            strcmp(args[i],"-") != 0 &&
            strcmp(args[i],"x") != 0 &&
            strcmp(args[i],"/") != 0 &&
            strcmp(args[i],"^") != 0 )
        {
            cout << "Argument " << i << " is invalid." << endl;
            return false;
        }
    }
    return true;
}

Calculator::~Calculator()
{
    cleanUp();
}
