#include "cmd-tags.hpp"

#if defined(USE_BOOST_REGEX)
#include <boost/regex.hpp>
#else
#include <regex>
#endif

#include "traverser.hpp"
#include "cmd-search.hpp"

using namespace std;
#if defined(USE_BOOST_REGEX)
using namespace boost;
#endif

void tags()
{
   Traverser traverser;
   regex regex("\\#([^ \n\t]*)");
   smatch matches;

   while (!traverser.eof())
   {
      Entry entry = traverser.next();

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
