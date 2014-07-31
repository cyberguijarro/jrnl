#include "journal.hpp"

#include <algorithm>
#include <iomanip>
#include <unistd.h>

#include "utility.hpp"

using namespace std;

Journal::Journal(bool write) : file(
   filename(),
   ios_base::in | ios_base::out | ios_base::ate | ios_base::app
)
{
   file.seekg(0, ios_base::end);
   position = file.tellg();
}

Entry Journal::next()
{
   off_t record_length;
   Entry entry;
   
   file.seekg(-static_cast<off_t>(record_marker_length), ios_base::cur);
   file >> record_length;
   file.seekg(
      -static_cast<off_t>(record_marker_length) - record_length,
      ios_base::cur
   );
   file >> entry;
   file.seekg(
      -static_cast<off_t>(record_marker_length) - record_length - 1,
      ios_base::cur
   );
   position -= static_cast<off_t>(record_marker_length) + record_length + 1;

   return entry;
}

bool Journal::eof()
{
   return (position == 0);
}

void Journal::push(const vector<string>& lines)
{
   auto start = file.tellp();
   vector<string> formatted_lines;

   file << now() << endl;
   
   transform(
      lines.begin(),
      lines.end(),
      back_inserter<vector<string>>(formatted_lines),
      [] ( const string& l ) { return '\t' + l; }
   );

   copy(
      formatted_lines.begin(),
      formatted_lines.end(),
      ostream_iterator<string>(file, "\n")
   );
   
   file << setw(record_marker_length)
      << setfill('0')
      << file.tellp() - start
      << endl;

   position = file.tellp();
}

void Journal::pop()
{
   next();
   file.close();

   truncate(filename().c_str(), position);

   file.open(
      filename(),
      ios_base::in | ios_base::out | ios_base::ate | ios_base::app
   );
   file.seekg(0, ios_base::end);
   position = file.tellg();
}

void Journal::reset()
{
   file.close();
   file.open(
      filename(),
      ios_base::in | ios_base::out | ios_base::ate | ios_base::app
   );
   file.seekg(0, ios_base::end);
   position = file.tellg();
}
