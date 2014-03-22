#include <iostream>
#include "help.hxx"

using namespace std;

void Help::printHelp()
{
    cout << "calcCMD Help Page\n" << endl;

    cout << "The option argument (should you choose to use it) is declared via '-'." << endl;
    cout << "Without option: `calccmd 1 + 2 x 3`" << endl;
    cout << "With option: `calccmd -v 1 + 2 x 3`\n" << endl;

    cout << "You can also pass a longform option, but you can only do it once." << endl;
    cout << "Example: `calccmd --verbose 1 + 2 x 3`\n" << endl;

    cout << "Options are passed as the first argument to the program." << endl;
    cout << "Example: `calccmd -c 2 ^ 32`\n" << endl;

    cout << "To use multiple options, add more characters to the option argument." << endl;
    cout << "Example: `calccmd -pv 2 3 4 x +`\n" << endl;

    cout << "----- Available Options -----\n" << endl;

    cout << "-c, --classic - Calculates from left to right, ignoring parentheses" << endl;
    cout << "-v, --verbose - Tells more about the parsing methods used" << endl;
    cout << "-q, --quiet - Prints only the answer on the screen" << endl;
    cout << "-p, --postfix - Parses the arguments as Reverse Polish Notation" << endl;
    cout << "-f, --factorial - Gets the factorial of the first number" << endl;
}
