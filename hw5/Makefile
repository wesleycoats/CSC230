CC = gcc
CFLAGS = -Wall -std=c99 -g

crypt: crypt.o des.o
	gcc -Wall -std=c99 -g crypt.o des.o -o crypt

crypt.o: des.h
	gcc -Wall -std=c99 -g crypt.c -o crypt.o

des.o: des.c des.h
	gcc -Wall -std=c99 -g des.c -o des.o

clean:
	rm -f crypt
	rm -f crypt.o
	rm -f des.o
	rm -f des