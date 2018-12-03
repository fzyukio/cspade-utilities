#include <cmath>
#include "StringArgvParser.h"
#include "wrappers.h"
#include "funcs.h"
#include "spade/spade.h"

void spadeWrapper(const string &s) {
    args_t *args = parse(s);
    sequenceFunc(args->argc, args->argv);
    delete args;
}

void exttposeWrapper(const string &s) {
    args_t *args = parse(s);
    exttposeFunc(args->argc, args->argv);
    delete args;
}

void getconfWrapper(const string &s) {
    args_t *args = parse(s);
    getconfFunc(args->argc, args->argv);
    delete args;
}

void makebinWrapper(const string &s) {
    args_t *args = parse(s);
    makebinFunc(args->argc, args->argv);
    delete args;
}

result_t getResult() {
    result_t result;

    result.mined = mined.str();
    result.logger = logger.str();
    result.memlog = memlog.str();
    result.nsequences = DBASE_NUM_TRANS;

    // Clear the stringstream otherwise the next run will get duplicated result
    mined.str(std::string());
    mined.clear();
    logger.str(std::string());
    logger.clear();
    memlog.str(std::string());
    memlog.clear();
    return result;
}

void clean_up(const string& tmpprefix) {
    list<string> tmpfiles = list_files("/tmp", tmpprefix);
    for (string& tmpfile : tmpfiles) {
        string filepath = "/tmp/" + tmpfile;
        if(remove(filepath.c_str()) != 0) {
            logger << "Error deleting file " << filepath << endl;
        }
        else {
            logger << "Cleaned up successful: " << filepath << endl;
        }
    }
}

result_t runSpade(const string &filename, spade_arg_t args) {

    if (!file_exists(filename)) {
        throw runtime_error("File " + filename + " does not exist.");
    }

    if (args.support <= 0 || args.support > 1) {
        throw runtime_error("Support must be a floating point in range (0-1]");
    }

    if (args.mingap > 0 && args.maxgap > 0 && args.maxgap < args.mingap) {
        args.mingap = args.maxgap;
    }
    string rawname = get_raw_filename(filename);
    int nrows = num_lines(filename);
    stringstream opt;

    auto nop = static_cast<int>(ceil((nrows + 2 * nrows) * sizeof(long) / pow(4, 10) / 5));
    if (args.memsize > 0) {
        opt << "-m " << args.memsize;
        nop = static_cast<int>(ceil(nop * 32 / args.memsize));
    }

    if (args.numpart > 0) {
        if (args.numpart < nop) {
            logger << "numpart less than recommended\n";
        }
        nop = args.numpart;
    }

    string random_suffix = random_id(16);
    string tmpprefix = rawname + random_suffix;
    string otherfile = "/tmp/" + tmpprefix;
    string datafile = otherfile + ".data";

    stringstream makebin_args;
    stringstream getconf_args;
    stringstream exttpose_args;
    stringstream spade_args;

    makebin_args << "makebin " << filename << " " << datafile;
    getconf_args << "getconf -i " << otherfile << " -o " << otherfile;
    exttpose_args << "exttpose -i " << otherfile << " -o " << otherfile << " -p " << nop << " -l -x -s " << args.support;

    if (args.maxsize > 0) {
        opt << " -Z " << args.maxsize;
    }
    if (args.maxlen > 0) {
        opt << " -z " << args.maxlen;
    }
    if (args.mingap > 0) {
        opt << " -l " << args.mingap;
    }
    if (args.maxgap > 0) {
        opt << " -u " << args.maxgap;
    }
    if (args.maxwin > 0) {
        opt << " -w " << args.maxwin;
    }
    if (not args.bfstype) {
        opt << " -r";
    }
    if (args.tid_lists) {
        opt << " -y";
    }

    spade_args << "spade -i " << otherfile << " -s " << args.support << opt.str() << " -e " << nop << " -o";

    try {
        makebinWrapper(makebin_args.str());
        getconfWrapper(getconf_args.str());
        exttposeWrapper(exttpose_args.str());
        spadeWrapper(spade_args.str());

        clean_up(tmpprefix);
        return getResult();
    }
    catch (exception& e) {
        clean_up(tmpprefix);
        throw e;
    }
}
