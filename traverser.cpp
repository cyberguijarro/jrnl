#include "traverser.hpp"

#include "utility.hpp"

using namespace std;

Traverser::Traverser() : file(filename(), ios_base::in)
{
   file.seekg(0, ios_base::end);
   position = file.tellg();
}

Entry Traverser::next()
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

bool Traverser::eof()
{
   return (position == 0);
}
