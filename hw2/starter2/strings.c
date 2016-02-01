/**
  @file strings.c
  @author Wesley Coats wrcoats
  
  This program reads text from standard input and prints it to standard output.
  The color of the text may vary depending on whether or not there are quotation marks
*/

#include <stdlib.h>
#include <stdio.h>

#define ESC 27
#define BRACKET 91
#define THREE 51
#define FOUR 52
#define M 109
#define ZERO 48
#define ONE 49
#define SINGLEQUOTE 39
#define DOUBLEQUOTE 34

/**
  This function switches the print color to blue then back to black after reading and printing and single quoted string
*/
void markSingle()
{
  char c;
  //Change color to blue
  printf("%c%c%c%c%c",ESC,BRACKET,THREE,FOUR,M);
  putchar(SINGLEQUOTE);
  do {
    c = getchar();
    if(c == EOF) {
      //Change color back to black
      printf("%c%c%c%c",ESC,BRACKET,ZERO,M);
      exit(100);
    }
    if(c == '/') {
      c = getchar();
    }
    putchar(c);
  }
  while (c != SINGLEQUOTE);
  if(c == SINGLEQUOTE) {
    //Change color back to black
    printf("%c%c%c%c",ESC,BRACKET,ZERO,M);
  }
}

/**
  This function switches the print color to red then back to black after reading a double quoted string
*/
void markDouble()
{
  //Change color to red
  printf("%c%c%c%c%c", ESC,BRACKET,THREE,ONE,M);
  char c;
  putchar(DOUBLEQUOTE);
  do {
    c = getchar();
    if(c == EOF) {
      //Change color back to black
      printf("%c%c%c%c",ESC,BRACKET,ZERO,M);
      exit(100);
    }
    putchar(c);
  }
  while(c != DOUBLEQUOTE);
  if(c == DOUBLEQUOTE) {
    //Change color back to black
    printf("%c%c%c%c",ESC,BRACKET,ZERO,M);
  }
}

/**
  The main function reads and prints characters that aren't part of a string
*/
int main()
{
  char c;
  while ((c = getchar()) != EOF) {
    if (c == '\'') {
      markSingle();
    }
    else if (c == '\"') {
      markDouble();
    }
    else {
      putchar(c);
    }
  } 
  return EXIT_SUCCESS;
}
