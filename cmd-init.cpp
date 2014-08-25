#include "cmd-init.hpp"

#include <vector>
#include <string>

#include "journal.hpp"

using namespace std;

void init()
{
   Journal("./.jrnl").push(vector<string>({"Journal created."}));
}
