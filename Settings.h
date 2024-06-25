// Settings.h
#ifndef SETTINGS_H
#define SETTINGS_H

#include <ostream>
#include <iomanip>
#include <string>
#include <vector>
class Settings
{
    public:
        static void printTableHeader(std::ostream &os);
        static void line_separator(std::ostream &os);
};
#endif

