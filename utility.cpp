#include "utility.hpp"

#include <chrono>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

using namespace std;

string filename()
{
	return string(getpwuid(getuid())->pw_dir) + "/.jrnl";
}

string now()
{
   time_t t = chrono::system_clock::to_time_t(chrono::system_clock::now());
   string result(ctime(&t));

   return result.substr(0, result.length() - 1);
}
