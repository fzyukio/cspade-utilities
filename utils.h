#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <sstream>
#include <fstream>
#include <list>

using std::ostringstream;
using std::string;
using std::ifstream;
using std::count;
using std::istreambuf_iterator;
using std::list;

#ifndef bzero
#define bzero(b, len) (memset((b), '\0', (len)), (void) 0)
#endif

const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const int alphanumlen = sizeof(alphanum) - 1;

// Logger and mem logger
extern ostringstream logger;
extern ostringstream mined;
extern ostringstream memlog;

struct result_t {
    int nsequences;
    string mined;
    string logger;
    string memlog;
};

struct spade_arg_t {
    double support = 0.1;
    int maxsize = -1;
    int maxlen = -1;
    int mingap = -1;
    int maxgap = -1;
    int memsize = -1;
    int numpart = -1;
    int maxwin = -1;
    bool bfstype = false;
    bool tid_lists = false;
};


bool file_exists(const string &name);

int num_lines(const string &filename);

list<string> list_files(const string& folder, const string& prefix = "");

string get_raw_filename(const string &fullname);

string random_id(const int len);

#endif
