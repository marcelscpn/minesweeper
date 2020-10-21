IDIR =./include
SRCDIR = ./src
TESTDIR = ./test
EXECDIR = ./exec
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=./obj

_OBJ = board.o strategy.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SRCDIR)/%.c 
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/main.o: $(SRCDIR)/main.c
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ) $(ODIR)/main.o 
	$(CC) -o $(EXECDIR)/minesweeper $^ $(CFLAGS)

$(ODIR)/test.o: $(TESTDIR)/test.c
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ) $(ODIR)/test.o
	$(CC) -o $(EXECDIR)/unit_test $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
	rm -f $(EXECDIR)/*

