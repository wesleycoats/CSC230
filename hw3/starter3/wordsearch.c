/**
  @file wordsearch.c
  @author Wesley Coats wrcoats
  
  The wordsearch file creates a wordsearch from an input file. Then prompts the user for words to search.
  Then calls functions to help perform the search.
*/

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "search.h"

#define MAX_SIZE 9

int main(int argc, char *argv[])
{
  if(argc != 2) {
    fprintf(stderr, "usage: wordsearch <grid_file>\n");
    exit(1);
  }
  FILE *ip = fopen(argv[1], "r");
  if(!ip) {
    fprintf(stdout, "Can't open file: %s\n", argv[1]);
    fprintf(stdout, "usage: wordsearch <grid_file>\n");
    exit(1);
  }
  //Read wordsearch file, store in multidimensional array
  char letter;
  unsigned char wordsearchGrid[MAX_SIZE][MAX_SIZE];
  for(int i = 0; i < MAX_SIZE; i++) {
    for (int j = 0; j < MAX_SIZE; j++) {
      fscanf(ip, "%c ", &letter);
        if(!(isalpha(letter))) {
          fprintf(stderr, "Improperly formatted file.\n");
          exit(EXIT_FAILURE);
        }
        if(isupper(letter)) {
          letter = tolower(letter);
        }
        wordsearchGrid[i][j] = letter;
    }
  }
  
  //Print wordsearch
  for(int i = 0; i < MAX_SIZE; i++) {
    for (int j = 0; j < MAX_SIZE; j++) {
      printf("%c ", wordsearchGrid[i][j]);
    }
    printf("\n");
  }
  //Prompt user for word
  char wordToCheck[MAX_SIZE];
  printf("Word (or ! to quit)? ");
  scanf("%9s", wordToCheck);
  char c;
   while(c != '\n') {
      c = getchar();
    }
  
  //Change to lowercase
  int lowerInt = 0;
  while(wordToCheck[lowerInt]) {
    wordToCheck[lowerInt] = tolower(wordToCheck[lowerInt]);
    lowerInt++;
  }
  //Get length of word
  int wordLength = strlen(wordToCheck);
  
  //Quit if !
  if(wordToCheck[0] == '!') {
    fclose(ip);
    exit(0);
  }
  else {
    while(wordToCheck[0] != '!') {
      if(wordLength == 1) {
        goto skiploop;
      }
      else {
        //Use find function, reprint grid, reprompt user
        find(wordToCheck, wordsearchGrid);
        for(int i = 0; i < MAX_SIZE; i++) {
          for (int j = 0; j < MAX_SIZE; j++) {
            printf("%c ", wordsearchGrid[i][j]);
          }
          printf("\n");
        }
        skiploop:
        printf("Word (or ! to quit)? ");
        scanf("%9s", wordToCheck);
        while(c != '\n') {
          c = getchar();
        }
        
        
        //Change to lowercase
        lowerInt = 0;
        while(wordToCheck[lowerInt]) {
          wordToCheck[lowerInt] = tolower(wordToCheck[lowerInt]);
          lowerInt++;
        }
        
        
        //Get length of word
        wordLength = strlen(wordToCheck);
      }
    }
  }
}