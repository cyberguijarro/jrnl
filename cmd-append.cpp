#include "cmd-append.hpp"

#include <vector>
#include <string>
#include <iostream>

#include "journal.hpp"

using namespace std;

void append()
{
   vector<string> lines(1U);

   while (getline(cin, lines.back()))
   {
      lines.push_back(string());
   }

   Journal(true).push(lines);
}
