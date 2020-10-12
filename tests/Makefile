IDIR =../include
SRCDIR =../src
CXX=g++
CXXFLAGS=-I$(IDIR) -std=c++17
CC=gcc
CFLAGS=-I$(IDIR) -Wall -Wextra -std=c99 -pedantic -Wmissing-prototypes \
    -Wstrict-prototypes -Wold-style-definition

ODIR=./obj
LDIR =../lib

LIBS=-lboost_unit_test_framework

_OBJ = lrr_math.o lrr_kty8x.o main.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/lrr_math.o: $(SRCDIR)/lrr_math.c $(IDIR)/lrr_math.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/lrr_kty8x.o: $(SRCDIR)/lrr_kty8x.c $(IDIR)/lrr_kty8x.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/main.o: main.cpp TestMathc.hpp TestKTY8x.hpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

test: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

.DEFAULT_GOAL := test
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core test