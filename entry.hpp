#pragma once

#include <string>
#include <iostream>
#include <vector>

struct Entry
{
   std::string timestamp;
   std::string lines;
   size_t record_length;

   std::vector<std::string> split() const;
};

std::istream& operator>>(std::istream& stream, Entry& entry);
std::ostream& operator<<(std::ostream& stream, const Entry& entry);
