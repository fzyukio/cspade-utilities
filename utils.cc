#include <sstream>
#include <cstdio>
#include <dirent.h>
#include <sys/types.h>

#include "utils.h"

using std::ostringstream;

ostringstream logger;
ostringstream mined;
ostringstream memlog;

bool file_exists(const string &name) {
    ifstream f(name.c_str());
    return f.good();
}

/* Reads a file and returns the number of lines in this file. */
int num_lines(const string &filename){
    FILE * file = fopen(filename.c_str(), "r");
    int lines = 0;
    int c;
    int last = '\n';
    while (EOF != (c = fgetc(file))) {
        if (c == '\n' && last != '\n') {
            ++lines;
        }
        last = c;
    }
    fclose(file);
    return lines;
}


bool starts_with(const string &haystack, const string &needle) {
    return needle.length() <= haystack.length()
           && equal(needle.begin(), needle.end(), haystack.begin());
}


list<string> list_files(const string& folder, const string& prefix) {
    struct dirent *entry;
    list<string> retval;
    DIR *dir = opendir(folder.c_str());
    if (dir == nullptr) {
        return retval;
    }

    bool check_prefix = prefix.length() > 0;

    while ((entry = readdir(dir)) != nullptr) {
        string filename = entry->d_name;
        if (check_prefix && starts_with(filename, prefix)) {
            retval.push_back(filename);
        }
    }
    closedir(dir);

    return retval;
}

string get_raw_filename(const string &fullname) {
    size_t dot_index = fullname.find_last_of('.');
    size_t slash_index = fullname.find_last_of('/');
    return fullname.substr(slash_index + 1, dot_index - slash_index - 1);
}


string random_id(const int len) {
    auto *s = new char[len + 1];
    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % alphanumlen];
    }
    s[len] = 0;
    string retval(s);
    delete[] s;
    return retval;
}
