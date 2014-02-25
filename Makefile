EXEC=/bin/calccmd
CXX=g++
CXXFLAGS=-Wall

SDIR=src
ODIR=obj

CXXSRCS=$(shell ls $(SDIR)/*.cpp)

all: install

install: objects
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(ODIR)/*.o

objects:
	$(CXX) $(CXXFLAGS) -c $(CXXSRCS)
	mkdir -p $(ODIR)
	mv *.o $(ODIR)

clean:
	rm -rf obj/
