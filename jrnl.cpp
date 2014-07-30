#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <regex>

#include "entry.hpp"
#include "utility.hpp"

using namespace std;

void append()
{
   vector<string> lines(1U);
   ofstream file(filename(), ios_base::out | ios_base::ate | ios_base::app);
   string timestamp;

   while (getline(cin, lines.back()))
   {
      lines.push_back(string());
   }

   file << (timestamp = now()) << endl;
   
   for_each(
      lines.begin(),
      lines.end(),
      [] ( string& line ) { line.insert(line.begin(), 1, '\t'); }
   );

   copy(lines.begin(), lines.end(), ostream_iterator<string>(file, "\n"));

   cout << "New journal entry added (" << timestamp << ")." << endl;
}

void search(string pattern)
{
   ifstream file(filename(), ios_base::in );
   regex regex(pattern);

   while (file)
   {
      Entry entry;

      file >> entry;

      if (regex_match(entry.lines, regex))
         cout << entry;
   }
}

int main(int argc, const char* argv[])
{
   if ( argc == 1 )
   {
      append();
   }
   else
   {
      search(string(argv[1]));
   }

   return 0;
}
