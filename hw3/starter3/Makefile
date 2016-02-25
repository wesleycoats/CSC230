CC = gcc
CFLAGS = -Wall -std=c99

wordsearch: wordsearch.o search.o
	gcc -Wall -std=c99 wordsearch.o search.o -o wordsearch

search.o: search.c search.h
	gcc -Wall -std=c99 -c search.c -o search.o

wordsearch.o: search.h
	gcc -Wall -std=c99 -c wordsearch.c -o wordsearch.o
  
search_test: search.c search_test.c
	gcc -Wall -std=c99 -c search_test.c search.c search_test
  
clean:
	rm -f search.o
	rm -f output.txt