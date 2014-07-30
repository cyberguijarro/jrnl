#pragma once

#include <string>
#include <iostream>
#include <vector>

struct Entry
{
   std::string timestamp;
   std::string lines;

   std::vector<std::string> split() const;
};

std::istream& operator>>(std::istream& stream, Entry& entry);
std::ostream& operator<<(std::ostream& stream, const Entry& entry);
