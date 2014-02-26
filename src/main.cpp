#include <iostream>
#include <cstring>
#include "calculator.h"

using namespace std;

void printHelp()
{
    // todo: make help page
}

bool checkArgs(bool option, int count, char** args)
{
    // check number of arguments
    if ((option ? count : count-1)%2 != 0 ||
        (option ? count-2 : count-1) == 0)
    {
        cout << "Invalid argument count." << endl;
        return false;
    }

    // check operations
    for (int i = (option ? 3 : 2); i < count; i+=2)
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

int main(int argc, char** argv)
{
    // no args
    if (argc == 1)
    {
        Calculator::printUsage(argv);
        return -1;
    }

    bool c = false, extra = false;
    if (strcmp(argv[1],"-c") == 0)
    {
        c = true;
        extra = true;
    }

    if (strcmp(argv[1],"--help") == 0)
    {
        printHelp();
        return 0;
    }

    if (!checkArgs(extra,argc-1,argv))
    {
        return -2147483648;
    }

    // object-oriented after here
    Calculator program(c,argc,argv);
    return program.exec();
}

