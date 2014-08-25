#include "cmd-init.hpp"

#include <vector>
#include <string>
#include <unistd.h>

#include "journal.hpp"

using namespace std;

void init()
{
   const string path = "./.jrnl";

   if (access(path.c_str(), R_OK) != 0)
      Journal(path).push(vector<string>({"Journal created."}));
}
