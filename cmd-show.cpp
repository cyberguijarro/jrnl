#include "cmd-show.hpp"

#include "journal.hpp"

using namespace std;

void show(const string& timestamp)
{
   Journal().each(
      [&] (const Entry& entry) -> bool {
         if (entry.timestamp == timestamp) cout << entry; 
         return true;
      }
   );
}
