#include "journal.hpp"

#include <algorithm>
#include <iomanip>
#include <iterator>
#include <unistd.h>

#include "utility.hpp"

using namespace std;

void Journal::open()
{
   file.open(
      path.empty() ? filename() : path,
      ios_base::in | ios_base::out | ios_base::ate | ios_base::app
   );
   file.seekg(0, ios_base::end);
}

void Journal::close()
{
   file.close();
}

Journal::Journal(const string& path) : path(path)
{
}

void Journal::each(function<bool(const Entry&)> callback)
{
   open();

   while (file.tellg() > 0) {
      string temp;
      off_t record_length;
      Entry entry;
   
      file.seekg(-static_cast<off_t>(record_marker_length) - 1, ios_base::cur);
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

      if (!callback(entry))
         break;
   }

   close();
}

Entry Journal::back()
{
   Entry result;

   each([&] (const Entry& entry) { result = entry; return false; });

   return result;
}

void Journal::push(const vector<string>& lines)
{
   open();

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
   }

   close();
}

void Journal::pop()
{
   off_t record_length, file_length = file.tellg();
   
   open();
   
   file_length = file.tellg();
   file.seekg(-static_cast<off_t>(record_marker_length), ios_base::cur);
   file >> record_length;
   file_length -= record_length + record_marker_length + 1;
   
   close();

   if (truncate(filename().c_str(), file_length)) { }
}

void Journal::reset()
{
   close();
   open();
}
