#include <cstring>
#include "calculator.hxx"
#include "help.hxx"

using namespace std;

int main(int argc, char** argv)
{
    // no args
    if (argc == 1)
    {
        Calculator::printUsage(argv);
        return -1;
    }

    if (strcmp(argv[1],"--help") == 0)
    {
        Help::printHelp();
        return 0;
    }

    bool extra = false;
    if (argv[1][0] == '-')
        extra = true;

    // object-oriented after here
    Calculator program(extra,argc,argv);
    return program.exec();
}

