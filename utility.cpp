#include "utility.hpp"

#include <chrono>
#include <functional>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

using namespace std;

const size_t record_marker_length = 10U;

string filename()
{
    char* buffer = getcwd(NULL, 4096);
    string directory = string(buffer) + "/", result;
    bool found = false;
    
    free(buffer);

    do
    {
        result = directory + ".jrnl";
        found = (access(result.c_str(), R_OK) == 0);

        if (directory == "/")
            break;

        directory.erase(directory.rfind("/", directory.length() - 2) + 1);
    }
    while (!found);

    if (!found)
    {
        result = string(getpwuid(getuid())->pw_dir) + "/.jrnl";
    }

    return result;
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
    {
        if (system(("$EDITOR " + filename).c_str()))
            ;
    }
    else
    {
        cerr << "No $EDITOR environment variable found." << endl;
        result = false;
    }

    return result;
}
