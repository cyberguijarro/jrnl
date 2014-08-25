#include "cmd-last.hpp"

#include <iostream>

#include "journal.hpp"

using namespace std;

void last()
{
   cout << Journal().back() << endl;
}
