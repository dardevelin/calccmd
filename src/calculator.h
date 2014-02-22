#ifndef CALCULATOR_H
#define CALCULATOR_H

class Calculator
{
    public:
        Calculator(bool,int,char**);
        ~Calculator();
        static void printUsage(char**);
        int exec();
        int classicCalc();
        int orderedCalc();
    private:
        bool orderly;
        int argc;
        char** args;
};

#endif
