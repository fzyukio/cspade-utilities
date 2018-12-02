//
// Created by Yukio Fukuzawa on 2/12/18.
//

#include <strings.h>
#include <err.h>
#include <cstdlib>
#include <cstdio>
#include "utils.h"
#include "StringArgvParser.h"


void StringArgvParser::addCharToToken(char c) {
    int n;

    n = static_cast<int>(strlen(token));
    if (n == ARGV_TOKEN_MAX - 1)
        errx(1, "addCharToToken: reached max token length (%d)", ARGV_TOKEN_MAX);

    token[n] = c;
}


/* finish the current token: copy it into argv and setup next token */
void StringArgvParser::finishToken() {
    if (argc == ARGV_MAX)
        errx(1, "finishToken: reached max argv length (%d)", ARGV_MAX);

/*STATUS("finishing token: '%s'\n", token);*/
    argv[argc++] = token;
    if ((token = static_cast<char *>(calloc(ARGV_TOKEN_MAX, sizeof(char)))) == NULL)
        err(1, "finishToken: failed to calloc");
    bzero(token, ARGV_TOKEN_MAX * sizeof(char));
}

void StringArgvParser::parse(string s) {
    bool in_token;
    bool in_container;
    bool escaped;
    char container_start;
    char c;
    int len;
    int i;

    container_start = 0;
    in_token = false;
    in_container = false;
    escaped = false;

    len = static_cast<int>(s.length());

    for (i = 0; i < len; i++) {
        c = s[i];

        switch (c) {
            /* handle whitespace */
            case ' ':
            case '\t':
            case '\n':
                if (!in_token)
                    continue;

                if (in_container) {
                    addCharToToken(c);
                    continue;
                }

                if (escaped) {
                    escaped = false;
                    addCharToToken(c);
                    continue;
                }

                /* if reached here, we're at end of token */
                in_token = false;
                finishToken();
                break;

                /* handle quotes */
            case '\'':
            case '\"':

                if (escaped) {
                    addCharToToken(c);
                    escaped = false;
                    continue;
                }

                if (!in_token) {
                    in_token = true;
                    in_container = true;
                    container_start = c;
                    continue;
                }

                if (in_container) {
                    if (c == container_start) {
                        in_container = false;
                        in_token = false;
                        finishToken();
                        continue;
                    } else {
                        addCharToToken(c);
                        continue;
                    }
                }

                /* XXX in this case, we:
                 *    1. have a quote
                 *    2. are in a token
                 *    3. and not in a container
                 * e.g.
                 *    hell"o
                 *
                 * what's done here appears shell-dependent,
                 * but overall, it's an error.... i *think*
                 */
                printf("Parse Error! Bad quotes\n");
                break;

            case '\\':

                if (in_container && s[i + 1] != container_start) {
                    addCharToToken(c);
                    continue;
                }

                if (escaped) {
                    addCharToToken(c);
                    continue;
                }

                escaped = true;
                break;

            default:
                if (!in_token) {
                    in_token = true;
                }

                addCharToToken(c);
        }
    }

    if (in_container)
        printf("Parse Error! Still in container\n");

    if (escaped)
        printf("Parse Error! Unused escape (\\)\n");
}

int StringArgvParser::getArgc() const {
    return argc;
}

char** StringArgvParser::getArgv() {
    return argv;
}

StringArgvParser::StringArgvParser(string s) {
    argc = 0;
    if ((token = static_cast<char *>(calloc(ARGV_TOKEN_MAX, sizeof(char)))) == NULL)
        err(1, "argv_init: failed to calloc");
    bzero(token, ARGV_TOKEN_MAX * sizeof(char));

    parse(s);
}
