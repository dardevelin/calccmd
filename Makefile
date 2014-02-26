EXEC=/bin/calccmd
CC=gcc
CXX=g++
CFLAGS=-Wall
CXXFLAGS=-Wall

SDIR=src
ODIR=obj

CSRCS=$(shell ls $(SDIR)/*.c)
CXXSRCS=$(shell ls $(SDIR)/*.cpp)

all: install

install: objects
	$(CXX) -o $(EXEC) $(ODIR)/*.o

objects:
	$(CC) $(CFLAGS) -c $(CSRCS)
	$(CXX) $(CXXFLAGS) -c $(CXXSRCS)
	mkdir -p $(ODIR)
	mv *.o $(ODIR)

clean:
	rm -rf obj/
