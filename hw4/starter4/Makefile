CC = gcc
CFLAGS = -Wall -std=c99 -g

spellcheck: spellcheck.o text.o
	gcc -Wall -std=c99 -g spellcheck.o text.o -o spellcheck

spellcheck.o: text.h
	gcc -Wall -std=c99 -g -c spellcheck.c -o spellcheck.o

text.o: text.c text.h
	gcc -Wall -std=c99 -g -c text.c -o text.o

clean:
	rm -f text.o
	rm -f spellcheck.o
	rm -f output.txt