CC = gcc
FLGS = -std=c11 -Wall -Wextra
all: programa gerador
PROG = programa
OBJS = main.o pol_esp.o

programa: main.o pol_esp.o
	$(CC) $(FLGS) -o programa main.o pol_esp.o

gerador: gerador.c
	$(CC) $(FLGS) -o gerador gerador.c

main.o: main.c pol_esp.h
	$(CC) $(FLGS) -c main.c

pol_esp.o: pol_esp.c pol_esp.h
	$(CC) $(FLGS) -c pol_esp.c

clean:
	rm -f *.o programa gerador