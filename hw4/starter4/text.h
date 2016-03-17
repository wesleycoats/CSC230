/**
  @file text.h
  @author Wesley Coats wrcoats
  
  The header file for text.c
*/

char *readLine(FILE *fp);

char **readLines(const char *fileName, int *count);

char *readLineForDictionary(FILE *dp);

char **readLinesForDictionary(const char *fileName, int *count);

void freeLines(char **lines, int count);