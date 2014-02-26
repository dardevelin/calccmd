EXEC=calccmd
DESTDIR=/usr/local/bin
CC=gcc
CXX=g++
CFLAGS=-Wall
CXXFLAGS=-Wall

SDIR=src
ODIR=obj

CSRCS=$(shell ls $(SDIR)/*.c)
CXXSRCS=$(shell ls $(SDIR)/*.cpp)
CTEMP=$(subst $(SDIR),$(ODIR),$(CSRCS))
COBJS=$(subst .c,.o,$(CTEMP))
CXXTEMP=$(subst $(SDIR),$(ODIR),$(CXXSRCS))
CXXOBJS=$(subst .cpp,.o,$(CXXTEMP))

all: executable

install: executable
	mv $(EXEC) $(DESTDIR)

executable: $(CXXOBJS) $(COBJS)
	$(CXX) -o $(EXEC) $(CXXOBJS) $(COBJS)

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $<
	mkdir -p $(ODIR)
	mv *.o $(ODIR)

$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) $(CFLAGS) -c $<
	mkdir -p $(ODIR)
	mv *.o $(ODIR)

clean:
	rm -rf obj/
	rm -f $(EXEC)
