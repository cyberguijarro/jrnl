#include "cmd-ammend.hpp"

#include <fstream>
#include <algorithm>
#include <iterator>

#include "journal.hpp"
#include "entry.hpp"
#include "utility.hpp"

using namespace std;

void ammend()
{
   const string temporary = ".jrnl_edit";
   Journal journal;
   Entry entry = journal.next();
   fstream file(temporary, ios_base::out|ios_base::trunc);
   vector<string> lines = entry.split();

   copy(lines.begin(), lines.end(), ostream_iterator<string>(file, "\n"));
   file.close();

   if (edit(temporary))
   {
      file.open(temporary, ios_base::in);
      lines.clear();
      
      do lines.emplace_back(); while (getline(file, lines.back()));

      remove(temporary.c_str());

      journal.reset();
      journal.pop();
      journal.push(trim_lines(lines));
   }
}
