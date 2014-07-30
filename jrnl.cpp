#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <regex>
#include <iomanip>

#include "entry.hpp"
#include "utility.hpp"
#include "traverser.hpp"

using namespace std;


void append()
{
   vector<string> lines(1U);
   ofstream file(filename(), ios_base::out | ios_base::ate | ios_base::app);
   string timestamp;
   auto start = file.tellp();

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
   
   file << setw(record_marker_length)
      << setfill('0')
      << file.tellp() - start
      << endl;

   cout << "New journal entry added (" << timestamp << ")." << endl;
}

void search(string pattern)
{
   Traverser traverser;
   regex regex(pattern);

   while (!traverser.eof())
   {
      Entry entry = traverser.next();

      if (regex_match(entry.lines, regex))
         cout << entry;
   }
}

void log()
{
   Traverser traverser;

   while (!traverser.eof())
   {
      Entry entry = traverser.next();

      cout << "[" << entry.timestamp << "] " << entry.split().front() << endl; 
   }
}

int main(int argc, const char* argv[])
{
   switch (argc)
   {
   case 1:
      append();
      break;
   case 2:
      if (string(argv[1]) == "log")
      {
         log();
      }
      break;
   case 3:
      if (string(argv[1]) == "search")
      {
         search(argv[2]);
      }
      break;
   }

   return 0;
}
