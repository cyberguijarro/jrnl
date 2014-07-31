#include "cmd-append.hpp"

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <iomanip>

#include "utility.hpp"

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
