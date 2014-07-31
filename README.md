# jrnl

jrnl is a command line tool built for fast and effortles maintenance of an activity journal. jrnl features:

 * Fast and portable implementation (C++11, no mandatory dependencies)
 * git-style commands
 * Efficient storage in plain text, human readable format (human writable not so much)

## Building

Only a modern C++ compiler with decent C++11 support, and `make` are required:

    make CXX=g++-4.6

or, if you have a solid default C++ compiler, just:

    make

If your compiler's STL implementation has lacky or missing std::regex support, you can build using boost's regex implementation:

    make USE_BOOST_REGEX=y

## File format

jrnl stores your journal entries in one single text file (`~/.jrnl`) with the following structure:

    <entry timestamp>
    <tab><entry line 1>
    <tab><entry line 2>
    ...
    <tab><entry line n>
    <entry length in bytes>
    ...

The last field allows fast backwards traversal, while keeping append operations also efficient (each new entry is added to the end of the file).

## Command-line syntax

To add a new journal entry just type:

    jrnl

write as many lines as you want, then hit `ctrl-d` to finish your entry. If you prefer to write in your text editor of choice, make sure your `EDITOR` environment variable is set, then run:

    jrnl longform

Again, with your `EDITOR` environment variable set, you can ammend your last entry running:

    jrnl ammend

To list all your journal entries, from most to least recent, invoke:

    jrnl log

Each entry will be displayed along with its timestamp. Use the timestamp to show one particular entry in full:

    jrnl "Thu Jul 31 18:09:49 2014"

If the last entry bothers you, just kill it using:

    jrnl pop

Also, you can display all entries matching a particular search string:

    jrnl search "my great project"

And even throw in regular expressions (http://en.cppreference.com/w/cpp/regex/ecmascript) now that you are at it:

    jrnl search "my.*project"

But the most powerful search-and-find tool is the tagging system. Add any tags to your entries:

    jrnl
    Just realized C++ rules #awesomeness

Then list all available tags using:

    jrnl tags

And display all entries containing a certain tag:

    jrnl tag awesomeness
