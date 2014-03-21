#ifndef OPTION_HXX
#define OPTION_HXX

class Option
{
    public:
        Option(std::string);
        Option(std::string,char);
        Option(std::string,bool);
        Option(std::string,char,bool);
        std::string getName();
        char getAbbr();
        bool isActive();
        void setActive(bool);
    private:
        std::string name;
        char abbr;
        bool active;
};

#endif
