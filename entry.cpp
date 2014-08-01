#include "entry.hpp"

#include <sstream>
#include <iterator>
#include <algorithm>

using namespace std;

vector<string> Entry::split() const
{
   istringstream stream(lines);
   vector<string> result;

   do result.emplace_back(); while (getline(stream, result.back()));
   result.pop_back();

   for_each(
      result.begin(),
      result.end(),
      [] (string& s) { s.erase(s.begin()); }
   );

   return result;
}

istream& operator>>(istream& stream, Entry& entry)
{
   string line;
   bool found = false;
   
   while (getline(stream, line))
   {
      if (!line.empty())
      {
         if (line.front() == '\t')
         {
            entry.lines += line;
            entry.lines += '\n';
         }
         else
         {
            if (found)
            {
               entry.record_length = static_cast<size_t>(stoi(line));
               break;
            }
            else
            {
               entry.timestamp = line;
               found = true;
            }
         }
      }
   }

   return stream;
}

ostream& operator<<(ostream& stream, const Entry& entry)
{
   vector<string> lines = entry.split();
   string timestamp = "Timestamp: " + entry.timestamp;

   stream << timestamp << endl;
   stream << string(timestamp.length(), '=') << endl << endl;
   
   copy(
      lines.begin(),
      lines.end(),
      ostream_iterator<string>(cout, "\n")
   );

   return stream;
}
