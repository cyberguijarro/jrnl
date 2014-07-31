#include "journal.hpp"

#include "utility.hpp"

using namespace std;

Journal::Journal() : file(filename(), ios_base::in)
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