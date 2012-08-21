SHELL = /bin/sh
CXX   = g++
LD    = g++
RM    = rm -f
MKDIR = mkdir -p
CP    = cp -p

# Installation directories.
PREFIX ?= /usr/local
BINDIR =  $(PREFIX)/bin

# The operating system.
OS = $(shell uname)

# Libraries and directories.
ifeq ($(OS),Linux)
    LIBDIRS = /usr/lib64 /usr/local/lib/ncl
else
    LIBDIRS = /usr/local/lib /usr/local/lib/ncl
endif
LIBS = -lboost_program_options -lncl-2.1.18

# Sources, object files and executables.
SOURCES = tree_parser.cpp main.cpp
OBJECTS = $(SOURCES:%.cpp=%.o)
PROG    = buggalo

# Command-line option flags.
CXXFLAGS = -Wall -m64
LDFLAGS  = -m64
LDLIBS   = $(LIBDIRS:%=-Wl,-rpath %) $(LIBDIRS:%=-L%) $(LIBS)

.SUFFIXES:
.SUFFIXES: .cpp .o

.PHONY: all clean install rpm

all: $(PROG)

buggalo: $(OBJECTS)
	$(LD) -o $@ $(LDFLAGS) $(OBJECTS) $(LDLIBS)

clean:
	$(RM) $(OBJECTS) $(PROG) $(PROG)*.tar.gz $(PROG)*.rpm

install: $(PROG)
	$(MKDIR) $(BINDIR)
	$(CP) $(PROG) $(BINDIR)

rpm:
	./buildrpm.sh buggalo.spec
