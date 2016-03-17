/**
  @file text.c
  @author Wesley Coats wrcoats
  
  The text file is responsible for reading text from files and returning it as a string stored in a dynamically allocated array.
  It will stop reading when it encounters a newline or the end-of-file. If it can't read anything before reaching EOF, it will return NULL.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text.h"

#define START_SIZE 100

char *readLine(FILE *fp)
{
  int len = 0;
  int capacity = START_SIZE;
  //Allocate array for line
  char *line = (char *)malloc(capacity * sizeof(char));
  //Process line into array
  char b;
  while(fscanf(fp, "%c", &b) == 1 && (b != '\n' && b != EOF)) {
    //Grow array if necessary
    if(len >= capacity) {
      capacity *= 2;
      line = (char *)realloc(line, capacity * sizeof(char));
    }
    line[len++] = b;
  }
  return line;
}

char **readLines(const char *fileName, int *count)
{
  int capacity = *count;
  //int capacity = START_SIZE;
  int numLines = *count;
  FILE *rp = fopen(fileName, "r");
  //Allocate outer and each of inner arrays
  char **words = (char **)malloc(numLines * sizeof(char *));
  for(int i = 0; i < capacity; i++) {
    words[i] = (char *)malloc(capacity * sizeof(char));
  //Resize array if necessary
    // if(*count >= numLines) {
      // numLines++;
      // words = (char **)realloc(words, numLines * sizeof(char **));
      // words[numLines] = (char *)malloc(capacity * sizeof(char));
    // }
    words[i] = readLine(rp);
  }
  return words;
}

char *readLineForDictionary(FILE *dp)
{
  int len = 0;
  int capacity = START_SIZE;
  //Allocate array for line
  char *lineInDictionary = (char *)malloc(capacity * sizeof(char));
  //Process line into array
  char d;
  // if(fscanf(dp, "%c", &b) == EOF) {
    // return NULL;
  // }
  while(fscanf(dp, "%c", &d) == 1 && (d != '\n' && d != EOF)) {
    //Not a lowercase letter
    if((d < 'a') || (d > 'z')) {
      fprintf(stderr, "Invalid word, line: %d", len);
      exit(EXIT_FAILURE);
    }
    //Grow array if necessary
    if(len >= capacity) {
      capacity *= 2;
      lineInDictionary = (char *)realloc(lineInDictionary, capacity * sizeof(char));
    }
    lineInDictionary[len++] = d;
  }
  return lineInDictionary;
  
}

char **readLinesForDictionary(const char *fileName, int *count)
{
  int capacity = *count;
  //int capacity = START_SIZE;
  int numLines = *count;
  FILE *tp = fopen(fileName, "r");
  //Allocate outer and each of inner arrays
  char **words = (char **)malloc(numLines * sizeof(char *));
  for(int i = 0; i < capacity; i++) {
    words[i] = (char *)malloc(capacity * sizeof(char));
  //Resize array if necessary
    // if(*count >= numLines) {
      // numLines++;
      // words = (char **)realloc(words, numLines * sizeof(char **));
      // words[numLines] = (char *)malloc(capacity * sizeof(char));
    // }
    words[i] = readLineForDictionary(tp);
  }
  return words;

}

void freeLines(char **lines, int count)
{
  for(int i = 0; i < count; i++) {
      free(lines[i]);
  }
  free(lines);
}