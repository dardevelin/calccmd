EXEC=countdowncmd
PREFIX=/usr/local
CC=gcc
CXX=g++
CFLAGS=-Wall
CXXFLAGS=-Wall

SDIR=src
ODIR=obj
XDIR=bin

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
