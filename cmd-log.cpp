#include "cmd-log.hpp"

#include <iostream>

#include "traverser.hpp"

using namespace std;

void log()
{
   Traverser traverser;

   while (!traverser.eof())
   {
      Entry entry = traverser.next();

      cout << "[" << entry.timestamp << "] " << entry.split().front() << endl; 
   }
}
