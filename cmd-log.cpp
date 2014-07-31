#include "cmd-log.hpp"

#include <iostream>

#include "journal.hpp"

using namespace std;

void log()
{
   Journal journal;

   while (!journal.eof())
   {
      Entry entry = journal.next();

      cout << "[" << entry.timestamp << "] " << entry.split().front() << endl; 
   }
}
