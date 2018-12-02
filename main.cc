#include <iostream>
#include <vector>

#include "funcs.h"
#include "StringArgvParser.h"

using namespace std;

int main(int argc, char **argv) {
    bool mb = false;
    bool gc = false;
    bool et = false;
    bool spade = false;

    if (argc == 1) {
        mb = true;
        gc = true;
        et = true;
        spade = true;
    } else {
        char *command = argv[1];
        if (!strcmp(command, "makebin")) {
            mb = true;
            gc = false;
            et = false;
            spade = false;
        }
        if (!strcmp(command, "getconf")) {
            mb = true;
            gc = true;
            et = false;
            spade = false;
        }
        if (!strcmp(command, "exttpose")) {
            mb = true;
            gc = true;
            et = true;
            spade = false;
        }
        if (!strcmp(command, "spade")) {
            mb = true;
            gc = true;
            et = true;
            spade = true;
        }
    }

    if (mb) {
        StringArgvParser mbParser("makebin zaki.txt zaki.data\n");
        makebinFunc(mbParser.getArgc(), mbParser.getArgv());
    }

    if (gc) {
        StringArgvParser gcParser("getconf -i zaki -o zaki\n");
        getconfFunc(gcParser.getArgc(), gcParser.getArgv());
    }

    if (et) {
        StringArgvParser etParser("exttpose -i zaki -o zaki -p 1 -l -x -s 0.3\n");
        exttposeFunc(etParser.getArgc(), etParser.getArgv());
    }

    if (spade) {
        StringArgvParser spadeParser("spade -i zaki -s 0.3 -Z 10 -z 10 -u 1 -r -e 1 -o\n");
        sequenceFunc(spadeParser.getArgc(), spadeParser.getArgv());
    }
    return 0;
}