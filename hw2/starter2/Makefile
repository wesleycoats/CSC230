CC = gcc
CFLAGS = -g -Wall -std=c99
LDLIBS = -lm

all: strings venn

strings: strings.o

venn: venn.o

clean:
	rm -f output.txt
	rm -f strings strings.o
	rm -f image.ppm
	rm -f venn venn.o
