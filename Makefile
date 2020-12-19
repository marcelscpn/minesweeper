IDIR =./include
SRCDIR = ./src
TESTDIR = ./test
EXECDIR = ./exec
CC=gcc
CFLAGS=-I$(IDIR)
CFLAGS += -Wall -Wextra

ODIR=./obj

_OBJ = board.o command.o strategy.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SRCDIR)/%.c 
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/main.o: $(SRCDIR)/main.c
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ) $(ODIR)/main.o 
	$(CC) -o $(EXECDIR)/minesweeper $^ $(CFLAGS)

_OBJT = test.o 
OBJT = $(patsubst %,$(ODIR)/test/%,$(_OBJT))

$(ODIR)/test/%.o: $(TESTDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ) $(OBJT)
	$(CC) -o $(EXECDIR)/unit_test $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
	rm -f $(EXECDIR)/*

