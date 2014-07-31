#include "cmd-append.hpp"

#include <vector>
#include <string>
#include <iostream>

#include "journal.hpp"
#include "utility.hpp"

using namespace std;

void append()
{
   vector<string> lines(1U);

   do lines.emplace_back(); while(getline(cin, lines.back()));

   Journal(true).push(trim_lines(lines));
}
