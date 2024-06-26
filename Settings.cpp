// Settings.cpp
#include "Settings.h"

void Settings::printTableHeader(std::ostream &os)
{
   os << std::left
      << std::setw(10) << "ID"
      << std::setw(60) << "Name"
      << std::setw(20) << "Category"
      << std::setw(20) << "Price"
      << std::setw(10) << "Quantity"
      << std::endl;
}
// print user table
void Settings::printUserTableHeader(std::ostream &os)
{
   os << std::left
      << std::setw(20) << "Username"
      << std::setw(20) << "Password"
      << std::setw(10) << "Role"
      << std::endl;
}
void Settings::line_separator(std::ostream &os)
{
   os << std::string(120, '-') << std::endl;
}
