#include <map>

#include "cmd-append.hpp"
#include "cmd-search.hpp"
#include "cmd-tags.hpp"
#include "cmd-log.hpp"
#include "cmd-show.hpp"
#include "cmd-pop.hpp"

using namespace std;

typedef map<string, function<void(const string&)>> mapping;

static const map<int, mapping> commands({
   make_pair(
      2,
      mapping({
         make_pair("log", [] (const string&) { log(); }),
         make_pair("tags", [] (const string&) { tags(); }),
         make_pair("pop", [] (const string&) { pop(); }),
      })
   ),
   make_pair(
      3,
      mapping({
         make_pair("search", [] (const string& s) { search(s); }),
         make_pair("show", [] (const string& s) { show(s); }),
         make_pair("tag", [] (const string& s) { tag(s); }),
      })
   ),
});

int main(int argc, const char* argv[])
{
   if (argc == 1)
   {
      append();
   }
   else if(
      (commands.find(argc) != commands.end())
      && (commands.at(argc).find(argv[1]) != commands.at(argc).end())
   )
   {
      commands.at(argc).at(argv[1])(argc >= 3 ? argv[2] : "");
   }

   return 0;
}
