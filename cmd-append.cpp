#include "cmd-append.hpp"

#include <vector>
#include <string>
#include <iostream>

#include "journal.hpp"
#include "utility.hpp"

using namespace std;

void append(bool external)
{
   vector<string> lines;

   if (external)
   {
      const string temporary = ".jrnl_edit";
      fstream file(temporary, ios_base::out|ios_base::trunc);

      file.close();

      if (edit(temporary))
      {
         file.open(temporary, ios_base::in);
         
         do lines.emplace_back(); while (getline(file, lines.back()));
      }
      
      remove(temporary.c_str());
   }
   else
   {
      do lines.emplace_back(); while(getline(cin, lines.back()));
   }

   Journal().push(trim_lines(lines));
}
