SRCDIR = src
LIBDIR = lib
BINDIR = bin
INCLUDEDIR = include

CC = gcc
CFLAGS = -Wall -pedantic -g -I$(INCLUDEDIR)
LDFLAGS = -lm

EXEC = $(BINDIR)/httpserver
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:.c=.o)
INCLUDE = $(wildcard $(INCLUDEDIR)/*.h)


all : prg

clean :
	rm -rf $(BINDIR)/*
	rm -rf $(SRCDIR)/*.o

prg : $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o : %.c
	$(CC) -c -o $@ $< $(CFLAGS)
