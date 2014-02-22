#ifndef CALCULATOR_H
#define CALCULATOR_H

class Calculator
{
    public:
        Calculator(bool,int,char**);
        ~Calculator();
        static void printUsage(char**);
        int exec();
    private:
        bool orderly;
        int argc;
        char** args;
        int classicCalc();
        int orderedCalc();
};

#endif
