CC = gcc
LD = gcc
CFLAGS = -Wall -pedantic

SERVER = server_tcp
KLIJENT = klijent_tcp

%.o: %.c
	$(CC) -c $(CFLAGS) $*.c -o $*.o

all: server klijent

server: $(SERVER).o
	$(LD) $(SERVER).o -o $(SERVER).x

klijent: $(KLIJENT).o
	$(LD) $(KLIJENT).o -o $(KLIJENT).x

clean:
	rm -f *.o *.x

.DEFAULT_GOAL := all

