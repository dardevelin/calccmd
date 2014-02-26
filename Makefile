EXEC=calccmd
CC=gcc
CXX=g++
CFLAGS=-Wall
CXXFLAGS=-Wall

SDIR=src
ODIR=obj

CSRCS=$(shell ls $(SDIR)/*.c)
CXXSRCS=$(shell ls $(SDIR)/*.cpp)
TEMP=$(subst $(SDIR),$(ODIR),$(CXXSRCS))
OBJS=$(subst .cpp,.o,$(TEMP))

all: executable

install: executable
	mv $(EXEC) /usr/bin

executable: $(OBJS)
	$(CXX) -o $(EXEC) $(OBJS)

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $<
	mkdir -p $(ODIR)
	mv *.o $(ODIR)

clean:
	rm -r obj/
