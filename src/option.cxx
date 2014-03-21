#include <string>
#include "option.hxx"

std::string name;
char abbr;
bool active;

Option::Option(std::string name)
{
    this->name = name;
    this->abbr = name[0];
    this->active = false;
}

Option::Option(std::string name, char abbr)
{
    this->name = name;
    this->abbr = abbr;
    this->active = false;
}

Option::Option(std::string name, bool active)
{
    this->name = name;
    this->abbr = name[0];
    this->active = active;
}

Option::Option(std::string name, char abbr, bool active)
{
    this->name = name;
    this->abbr = abbr;
    this->active = active;
}

std::string Option::getName()
{
    return name;
}

char Option::getAbbr()
{
    return abbr;
}

bool Option::isActive()
{
    return active;
}

void Option::setActive(bool active)
{
    this->active = active;
}
