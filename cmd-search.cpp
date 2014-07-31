#include "cmd-append.hpp"

#if defined(USE_BOOST_REGEX)
#include <boost/regex.hpp>
#else
#include <regex>
#endif

#include "traverser.hpp"

using namespace std;
#if defined(USE_BOOST_REGEX)
using namespace boost;
#endif

void search(const string& pattern)
{
   Traverser traverser;
   regex regex(pattern);

   while (!traverser.eof())
   {
      Entry entry = traverser.next();

      if (regex_search(entry.lines, regex))
         cout << entry;
   }
}
