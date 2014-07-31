#include "cmd-pop.hpp"

#include "journal.hpp"

using namespace std;

void pop()
{
   Journal(true).pop();
}
