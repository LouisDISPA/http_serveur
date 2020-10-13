SRCDIR = src
LIBDIR = lib
BINDIR = bin
DOCDIR = doc
INCLUDEDIR = include

CC = gcc
CFLAGS = -Wall -pedantic -g -I$(INCLUDEDIR)
LDFLAGS = -lm

EXEC = $(BINDIR)/httpserver
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:.c=.o)
INCLUDE = $(wildcard $(INCLUDEDIR)/*.h)


all : prg doc

clean :
	rm -rf $(BINDIR)/*
	rm -rf $(SRCDIR)/*.o
	rm -rf $(DOCDIR)/*

prg : $(EXEC)
	
doc : $(DOCDIR)/html/index.html 



$(EXEC) : $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o : %.c
	$(CC) -c -o $@ $< $(CFLAGS)


$(DOCDIR)/html/index.html : $(INCLUDE)
	doxygen
