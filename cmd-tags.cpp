#include "cmd-tags.hpp"

#if defined(USE_BOOST_REGEX)
#include <boost/regex.hpp>
#else
#include <regex>
#endif

#include "journal.hpp"
#include "cmd-search.hpp"

using namespace std;
#if defined(USE_BOOST_REGEX)
using namespace boost;
#endif

void tags()
{
   regex regex("\\#([^ \n\t]*)");
   smatch matches;
   int count = 0;
   
   Journal().each(
      [&] (const Entry& entry) {
         string lines = entry.lines;

         while (regex_search(lines, matches, regex)) {
            cout << matches[0] << " ";
            lines = matches.suffix().str();
            count++;
         }

         return true;
      }
   );

   if (count > 0) cout << endl;
}

void tag(const string& name)
{
   search(string("\\#") + name);
}
