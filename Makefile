#CC  = CC
CC = g++
CFLAGS = -g -std=c++11
#CFLAGS  = -11 -DSGI -no_auto_include
LIBS = -lm -lc
TARGET  = exttpose.exe makebin.exe getconf.exe spade.exe main.exe

default:	$(TARGET) 

clean:
	rm *.o $(TARGET)

common_header = utils.h
common_source = utils.cc

exttpose_header = exttpose/calcdb.h exttpose/Array.h exttpose/calcdb.h exttpose/Array.h
exttpose_source = exttpose/exttpose.cc exttpose/calcdb.cc exttpose/Array.cc
exttpose.exe: exttpose/main.cc $(exttpose_header) $(exttpose_source) $(common_header) $(common_source)
	$(CC) $(CFLAGS) -o exttpose.exe exttpose/main.cc $(exttpose_source) $(common_source) $(LIBS)

getconf_header = getconf/calcdb.h
getconf_source = getconf/calcdb.cc getconf/getconf.cc
getconf.exe: getconf/main.cc $(getconf_header) $(getconf_source) $(common_header) $(common_source)
	$(CC) $(CFLAGS) -o getconf.exe getconf/main.cc $(getconf_source) $(common_source) $(LIBS)

makebin_source = makebin/makebin.cc
makebin.exe: makebin/main.cc $(makebin_header) $(makebin_source) $(common_header) $(common_source)
	$(CC) $(CFLAGS) -o makebin.exe makebin/main.cc $(makebin_source) $(common_source) $(LIBS)

spade_header = spade/ArraySpade.h spade/Itemset.h spade/Lists.h spade/Eqclass.h spade/extl2.h spade/partition.h spade/maxgap.h spade/spade.h
spade_source = spade/sequence.cc spade/Itemset.cc spade/ArraySpade.cc spade/Eqclass.cc spade/Lists.cc spade/extl2.cc spade/partition.cc spade/maxgap.cc
spade.exe: spade/main.cc $(spade_header) $(spade_source) $(common_header) $(common_source)
	$(CC) $(CFLAGS) -o spade.exe spade/main.cc $(spade_source) $(common_source) $(LIBS)

main_header = StringArgvParser.h wrappers.h
main_source = main.cc StringArgvParser.cc wrappers.cc
main.exe: $(exttpose_header) $(exttpose_source) $(getconf_header) $(getconf_source) $(makebin_source) $(spade_header) $(spade_source) $(main_header) $(main_source)  $(common_header) $(common_source)
	$(CC) $(CFLAGS) -o main.exe $(main_source) $(spade_source) $(exttpose_source) $(getconf_source) $(makebin_source) $(common_source) $(LIBS)