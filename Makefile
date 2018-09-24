#
# Top level Makefile for DIOS
#

OBJS=main.o misc.o
CC=gcc
CFLAGS=-g

all: sadios

sadios: $(OBJS)
	$(CC) $(CFLAGS) -o sadios $(OBJS)

.c.o: dios.h
	$(CC) $(CFLAGS) -c $<

misc.o: misc.c misc.h
