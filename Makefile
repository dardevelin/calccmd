EXEC=calccmd
PREFIX=/usr/local
CC=gcc
CXX=g++
CFLAGS=-Wall
CXXFLAGS=-Wall

SDIR=src
ODIR=obj
XDIR=bin
LDIR=lib

CSRCS=$(shell if [ -e $(SDIR)/*.c ]; then ls $(SDIR)/*.c; fi;)
CXXSRCS=$(shell ls $(SDIR)/*.cxx)
CTEMP=$(subst $(SDIR),$(ODIR),$(CSRCS))
COBJS=$(subst .c,.o,$(CTEMP))
CXXTEMP=$(subst $(SDIR),$(ODIR),$(CXXSRCS))
CXXOBJS=$(subst .cxx,.o,$(CXXTEMP))
XPATH=$(XDIR)/$(EXEC)

all: executable

install: all
	install -D -m755 $(XPATH) $(DESTDIR)$(PREFIX)/bin/$(EXEC)

executable: $(CXXOBJS) $(COBJS)
	mkdir -p $(XDIR)
	$(CXX) -o $(XPATH) $(CXXOBJS) $(COBJS)

$(ODIR)/%.o: $(SDIR)/%.cxx
	$(CXX) $(CXXFLAGS) -c $<
	mkdir -p $(ODIR)
	mv *.o $(ODIR)

$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) $(CFLAGS) -c $<
	mkdir -p $(ODIR)
	mv *.o $(ODIR)

clean:
	rm -rf $(ODIR)
	rm -rf $(XDIR)
	rm -rf $(LDIR)

#FIXME: do proper library build in make

libraries32: $(SDIR)/calculator.cxx $(SDIR)/option.cxx
#make x86, x86_64, include folders
	mkdir -p $(LDIR)/x86/../x86_64/../include
#copy the header for easy redistribution
	cp $(SDIR)/calculator.hxx $(LDIR)/include
	cp $(SDIR)/option.hxx $(LDIR)/include
#build objects for x86
	$(CXX) -Wall -std=c++11 -m32 -c $(SDIR)/calculator.cxx $(SDIR)/option.cxx
#generate the static x86
	ar rcs libcalccmd32.a calculator.o option.o
	mv libcalccmd32.a $(LDIR)/x86
#build shared version
	rm *.o
	$(CXX) -Wall -std=c++11 -fPIC -c $(SDIR)/calculator.cxx $(SDIR)/option.cxx
	$(CXX) -shared -Wl,-soname,libcalccmd.so.1 -o libcalccmd32.so.1.0.1 calculator.o option.o
#relocate for redistribution
	mv libcalccmd32.so.1.0.1 $(LDIR)/x86
#clean up
	rm *.o


libraries: $(SDIR)/calculator.cxx $(SDIR)/option.cxx
#make x86, x86_64, include folders
	mkdir -p $(LDIR)/x86/../x86_64/../include
#copy the header for easy redistribution
	cp $(SDIR)/calculator.hxx $(LDIR)/include
	cp $(SDIR)/option.hxx $(LDIR)/include
#build objects for x86_64
	$(CXX) -Wall -std=c++11 -m64 -c $(SDIR)/calculator.cxx $(SDIR)/option.cxx
#generate the static x86_64
	ar rcs libcalccmd.a calculator.o option.o
	mv libcalccmd.a $(LDIR)/x86_64
#build shared version
	rm *.o
	$(CXX) -Wall -std=c++11 -m64 -fPIC -c $(SDIR)/calculator.cxx $(SDIR)/option.cxx
	$(CXX) -shared -Wl,-soname,libcalccmd.so.1 -o libcalccmd.so.1.0.1 calculator.o option.o
#relocate for redistribution
	mv libcalccmd.so.1.0.1 $(LDIR)/x86_64
#clean up
	rm *.o
