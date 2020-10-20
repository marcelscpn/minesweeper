IDIR =./include
SRCDIR = ./src
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=./obj
#LDIR =../lib

#LIBS=-lm

_DEPS = board.h strategy.h minunit.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = board.o strategy.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

minesweeper: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
	rm minesweeper

