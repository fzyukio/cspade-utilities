#ifndef SPADE_UTILITY_STRINGARGVPARSER_H
#define SPADE_UTILITY_STRINGARGVPARSER_H

#include <iostream>
#include <string>

using namespace std;

const int ARGV_MAX = 255;
const int ARGV_TOKEN_MAX = 255;

class StringArgvParser {
    int argc;
    char *argv[ARGV_MAX];
    char *token;

    /* add a character to the current token */
    void addCharToToken(char c);

    /* finish the current token: copy it into argv and setup next token */
    void finishToken();
    void parse(string s);
public:
    int getArgc() const;
    char* *getArgv();

    StringArgvParser(string s);
};


#endif //SPADE_UTILITY_STRINGARGVPARSER_H
