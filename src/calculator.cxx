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
    options.push_back(new Option("quiet"));
    options.push_back(new Option("postfix"));
    options.push_back(new Option("factorial"));
}

int Calculator::exec()
{
    if (!checkArgs()) return -1;

    int code = 0;
    if (options.at(0)->isActive()) code = classicCalc();
    else if (options.at(3)->isActive()) code = postfixCalc();
    else if (options.at(4)->isActive()) code = calcFactorial();
    else code = orderedCalc();
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
            if (options.at(1)->isActive())
                cout << "Adding " << args[i+1] << " to " << ans << endl;
            ans += strtod(args[i+1],NULL);
        }
        else if (!strcmp(args[i], "-"))
        {
            if (options.at(1)->isActive())
                cout << "Subtracting " << args[i+1] << " from " << ans << endl;
            ans -= strtod(args[i+1],NULL);
        }
        else if (!strcmp(args[i], "x"))
        {
            if (options.at(1)->isActive())
                cout << "Multiplying " << args[i+1] << " by " << ans << endl;
            ans *= strtod(args[i+1],NULL);
        }
        else if (!strcmp(args[i], "/"))
        {
            if (options.at(1)->isActive())
                cout << "Dividing " << args[i+1] << " by " << ans << endl;
            ans /= strtod(args[i+1],NULL);
        }
        else if (!strcmp(args[i], "^"))
        {
            if (options.at(1)->isActive())
                cout << "Raising " << ans << " to the power of" << args[i+1] << endl;
            ans = pow(ans,strtod(args[i+1],NULL));
        }
    }

    if (!options.at(2)->isActive()) cout << "The answer is: ";
    cout << ans << endl;
    return 0;
}

int Calculator::postfixCalc()
{
    int operIndex;
    vector<double> nums;
    vector<char*> opers;

    for (int i = option ? 2 : 1; i < argc; i++)
    {
        if (!isOper(args[i]))
        {
            nums.push_back(strtod(args[i],NULL));
            if (options.at(1)->isActive())
                cout << "Added " << args[i] << " to num list" << endl;
        }
        else
        {
            operIndex = i;
            break;
        }
    }
    for (int i = operIndex; i < argc; i++)
    {
        if (isOper(args[i]))
        {
            opers.push_back(args[i]);
            if (options.at(1)->isActive())
                cout << "Added " << args[i] << " to opers list" << endl;
        }
        else
        {
            cout << "Invalid operation at argument " << i << "\n" << endl;
            printUsage(args);
            return -1;
        }
    }

    if (opers.size() >= nums.size() ||
        opers.size() < nums.size()-1)
    {
        cout << "Invalid number of operations\n" << endl;
        printUsage(args);
        return -1;
    }

    int pass = 1;
    bool done = false;
    while (!done)
    {
        if (options.at(1)->isActive())
            cout << "Calculating with RPN/Postfix - Pass " << pass << endl;

        if (!strcmp(opers.at(0),"+"))
        {
            if (options.at(1)->isActive())
                cout << "Adding " << nums.at(nums.size()-2)
                    << " to " << nums.at(nums.size()-1) << endl;
            nums.at(nums.size()-2) += nums.at(nums.size()-1);
            if (options.at(1)->isActive())
                cout << "Erasing last num (no longer needed)" << endl;
            nums.erase(nums.end()-1);
            if (options.at(1)->isActive())
                cout << "Erasing first oper (no longer needed)" << endl;
            opers.erase(opers.begin());
        }
        else if (!strcmp(opers.at(0),"-"))
        {
            if (options.at(1)->isActive())
                cout << "Subtracting " << nums.at(nums.size()-2)
                    << " from " << nums.at(nums.size()-1) << endl;
            nums.at(nums.size()-2) -= nums.at(nums.size()-1);
            if (options.at(1)->isActive())
                cout << "Erasing last num (no longer needed)" << endl;
            nums.erase(nums.end()-1);
            if (options.at(1)->isActive())
                cout << "Erasing first oper (no longer needed)" << endl;
            opers.erase(opers.begin());
        }
        else if (!strcmp(opers.at(0),"x"))
        {
            if (options.at(1)->isActive())
                cout << "Multiplying " << nums.at(nums.size()-2)
                    << " by " << nums.at(nums.size()-1) << endl;
            nums.at(nums.size()-2) *= nums.at(nums.size()-1);
            if (options.at(1)->isActive())
                cout << "Erasing last num (no longer needed)" << endl;
            nums.erase(nums.end()-1);
            if (options.at(1)->isActive())
                cout << "Erasing first oper (no longer needed)" << endl;
            opers.erase(opers.begin());
        }
        else if (!strcmp(opers.at(0),"/"))
        {
            if (options.at(1)->isActive())
                cout << "Dividing " << nums.at(nums.size()-2)
                    << " by " << nums.at(nums.size()-1) << endl;
            nums.at(nums.size()-2) /= nums.at(nums.size()-1);
            if (options.at(1)->isActive())
                cout << "Erasing last num (no longer needed)" << endl;
            nums.erase(nums.end()-1);
            if (options.at(1)->isActive())
                cout << "Erasing first oper (no longer needed)" << endl;
            opers.erase(opers.begin());
        }
        else if (!strcmp(opers.at(0),"^"))
        {
            if (options.at(1)->isActive())
                cout << "Raising " << nums.at(nums.size()-2)
                    << " to the power of " << nums.at(nums.size()-1) << endl;
            nums.at(nums.size()-2) = pow(nums.at(nums.size()-2),
                                            nums.at(nums.size()-1));
            if (options.at(1)->isActive())
                cout << "Erasing last num (no longer needed)" << endl;
            nums.erase(nums.end()-1);
            if (options.at(1)->isActive())
                cout << "Erasing first oper (no longer needed)" << endl;
            opers.erase(opers.begin());
        }

        if (opers.size() == 0) done = true;
    }

    if (!options.at(2)->isActive())
        cout << "The answer is: ";
    cout << nums.at(0) << endl;
    return 0;
}

int Calculator::calcFactorial()
{
    int num = (int)strtod(args[2],NULL);
    int newNum = num;

    if (options.at(1)->isActive())
        cout << "Calculating factorial of " << num << endl;

    while (newNum > 1)
    {
        if (options.at(1)->isActive())
            cout << "Multiplying " << num << " by " << newNum-1 << endl;
        num *= --newNum;
    }

    if (!options.at(2)->isActive())
        cout << "The answer is: ";
    cout << num << endl;
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

    if (!options.at(2)->isActive()) cout << "The answer is: ";
    cout << nums.at(0) << endl;
    return 0;
}

bool Calculator::isOper(char* arg)
{
    return (strcmp(arg,"+") == 0 ||
            strcmp(arg,"-") == 0 ||
            strcmp(arg,"x") == 0 ||
            strcmp(arg,"/") == 0 ||
            strcmp(arg,"^") == 0 );
}

bool Calculator::checkArgs()
{
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

    // check number of arguments
    if (options.at(4)->isActive() &&
        argc > 3)
    {
        cout << "Invalid argument count.\n" << endl;
        printUsage(args);
        return false;
    }
    else if ((option ? argc-1 : argc)%2 != 0 ||
                (option ? argc-2 : argc-1) == 0)
    {
        cout << "Invalid argument count.\n" << endl;
        printUsage(args);
        return false;
    }

    // check operations
    if (!options.at(3)->isActive() &&
        !options.at(4)->isActive())
    {
        for (int i = (option ? 3 : 2); i < argc; i+=2)
        {
            if (!isOper(args[i]))
            {
                cout << "Argument " << i << " is invalid." << endl;
                return false;
            }
        }
    }

    if ((options.at(0)->isActive() &&
        options.at(3)->isActive()) ||
        (options.at(0)->isActive() &&
        options.at(4)->isActive()) ||
        (options.at(3)->isActive() &&
        options.at(4)->isActive()))
    {
        cout << "Mode panic! Don't try to activate more than one mode!\n" << endl;
        printUsage(args);
        return false;
    }
    return true;
}

Calculator::~Calculator()
{
    for (unsigned int i = 0; i < options.size(); i++)
    {
        delete options.at(i);
        options.at(i) = NULL;
    }
}
