#include "utility.hpp"

#include <chrono>
#include <functional>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

using namespace std;

const size_t record_marker_length = 10U;

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

vector<string> trim_lines(const vector<string>& lines)
{
    static const auto empty = [] (const string& s) { return s.empty(); };

    return vector<string>(
        find_if_not(lines.begin(), lines.end(), empty),
        find_if_not(lines.rbegin(), lines.rend(), empty).base()
    ); 
}

bool edit(const string& filename)
{
    bool result = true;

    if (getenv("EDITOR") != NULL)
        system(("$EDITOR " + filename).c_str());
    else
    {
        cerr << "No $EDITOR environment variable found." << endl;
        result = false;
    }

    return result;
}
