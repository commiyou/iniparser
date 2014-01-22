AUTOMAKE_OPTIONS=foreign
noinst_PROGRAMS=iniparser
bin_PROMGRAMS = iniparser
iniparser_SOURCES= src/main.cc src/menu.h src/menu.cc src/inifile.h src/inifile.cc src/utf8.h src/utf8/checked.h src/utf8/core.h src/utf8/unchecked.h src/include/debug.h src/parser/inidata.h src/parser/inidata.cc src/parser/iniorganiser.h src/parser/iniorganiser.cc src/parser/iniparser.h src/parser/iniparser.cc src/parser/iniwriter.h src/parser/iniwriter.cc src/parser/keyvalue.h src/parser/keyvalue.cc src/parser/section.cc src/parser/section.h
AM_CPPFLAGS= -Isrc/include -Isrc/parser
export INCLUDES

iniparser_LDFLAGS= -L/usr/local/lib -D_GNU_SOURCE
DEFS+=-D_GNU_SOURCE
