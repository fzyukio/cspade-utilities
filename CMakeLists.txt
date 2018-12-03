cmake_minimum_required(VERSION 3.9)
project(spade_utility)

set(CMAKE_CXX_STANDARD 11)

add_executable(getconf
        getconf/calcdb.cc
        getconf/getconf.cc
        getconf/main.cc utils.h utils.cc)

add_executable(spade_utility
        main.cc
        funcs.h
        StringArgvParser.cc
        StringArgvParser.h
        exttpose/Array.cc
        exttpose/Array.h
        spade/ArraySpade.cc
        spade/ArraySpade.h
        spade/Database.cc
        spade/Database.h
        spade/Eqclass.cc
        spade/Eqclass.h
        spade/extl2.cc
        spade/extl2.h
        spade/HashTable.cc
        spade/HashTable.h
        spade/Itemset.cc
        spade/Itemset.h
        spade/Lists.cc
        spade/Lists.h
        spade/maxgap.cc
        spade/maxgap.h
        spade/partition.cc
        spade/partition.h
        spade/sequence.cc
        spade/spade.h
        exttpose/exttpose.cc
        makebin/makebin.cc
        getconf/getconf.cc
        getconf/calcdb.cc
        getconf/calcdb.h
        exttpose/calcdb.cc
        exttpose/calcdb.h utils.h wrappers.cc wrappers.h utils.cc)
