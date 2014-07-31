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
   Journal journal;
   regex regex("\\#([^ \n\t]*)");
   smatch matches;

   while (!journal.eof())
   {
      Entry entry = journal.next();

      while (regex_search(entry.lines, matches, regex))
      {
         cout << matches[0] << " ";
         entry.lines = matches.suffix().str(); 
      }
   }
   
   cout << endl;
}

void tag(const string& name)
{
   search(string("\\#") + name);
}
