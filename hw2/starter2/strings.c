/**
  @file strings.c
  @author Wesley Coats wrcoats
  
  This program reads text from standard input and prints it to standard output.
  The color of the text may vary depending on whether or not there are quotation marks
*/

#include <stdlib.h>
#include <stdio.h>


/**
  This function switches the print color to blue then back to black after reading and printing and single quoted string
*/
void markSingle()
{
  char c;
  //Change color to blue
  printf("%c%c%c%c%c",27,91,51,52,109);
  putchar(39);
  do {
    c = getchar();
    if(c == EOF) {
      //Change color back to black
      printf("%c%c%c%c",27,91,48,109);
      exit(100);
    }
    if(c == '/') {
      c = getchar();
    }
    putchar(c);
  }
  while (c != 39);
  if(c == 39) {
    //Change color back to black
    printf("%c%c%c%c", 27,91,48,109);
  }
}

/**
  This function switches the print color to red then back to black after reading a double quoted string
*/
void markDouble()
{
  //Change color to red
  printf("%c%c%c%c%c", 27,91,51,49,109);
  char c;
  putchar(34);
  do {
    c = getchar();
    if(c == EOF) {
      //Change color back to black
      printf("%c%c%c%c",27,91,48,109);
      exit(100);
    }
    putchar(c);
  }
  while(c != 34);
  if(c == 34) {
    //Change color back to black
    printf("%c%c%c%c", 27,91,48,109);
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
