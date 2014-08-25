#include "cmd-log.hpp"

#include <iostream>

#include "journal.hpp"

using namespace std;

void log()
{
   Journal().each(
      [] (const Entry& entry) -> bool {
         cout << "[" << entry.timestamp << "] ";
         cout << entry.split().front() << endl; 
         return true;
      }
   );
}
