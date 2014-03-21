#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <vector>

class Option;

class Calculator
{
    public:
        Calculator(bool,int,char**);
        ~Calculator();
        static void printUsage(char**);
        int exec();
    private:
        std::vector<Option*> options;
        int argc;
        char** args;
        bool checkArgs();
        void setDefaultOptions();
        void cleanUp();
        int classicCalc();
        int orderedCalc();
};

#endif
