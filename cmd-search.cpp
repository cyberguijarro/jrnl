#include "cmd-append.hpp"

#if defined(USE_BOOST_REGEX)
#include <boost/regex.hpp>
#else
#include <regex>
#endif

#include "journal.hpp"

using namespace std;
#if defined(USE_BOOST_REGEX)
using namespace boost;
#endif

void search(const string& pattern)
{
   Journal journal;
   regex regex(pattern);

   while (!journal.eof())
   {
      Entry entry = journal.next();

      if (regex_search(entry.lines, regex))
         cout << entry;
   }
}
