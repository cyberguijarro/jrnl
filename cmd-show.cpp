#include "cmd-show.hpp"

#include "traverser.hpp"

using namespace std;

void show(const string& timestamp)
{
   Traverser traverser;

   while (!traverser.eof())
   {
      Entry entry = traverser.next();

      if (entry.timestamp == timestamp)
         cout << entry; 
   }
}
