CC = gcc
CFLAGS = -Wall -std=c99 -g

mygrep: mygrep.o pattern.o
	gcc -Wall -std=c99 -g mygrep.o pattern.o -o mygrep

mygrep.o: pattern.h
	gcc -Wall -std=c99 -g -c mygrep.c -o mygrep.o

pattern.o: pattern.c pattern.h
	gcc -Wall -std=c99 -g -c pattern.c -o pattern.o

clean:
	rm -f pattern.o
	rm -f mygrep.o
	rm -f output.txt