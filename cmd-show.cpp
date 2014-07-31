#include "cmd-show.hpp"

#include "journal.hpp"

using namespace std;

void show(const string& timestamp)
{
   Journal journal;

   while (!journal.eof())
   {
      Entry entry = journal.next();

      if (entry.timestamp == timestamp)
         cout << entry; 
   }
}
