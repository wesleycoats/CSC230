/**
  @file spellcheck.c
  @author Wesley Coats wrcoats
  
  The spellcheck file is responsible for handling command line arguments, finding words in text,
  checking to see if they're in the dictionary, and responding to user commands
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "text.h"

#define MAX_SIZE 100
#define ESC 27
#define BRACKET 91
#define THREE 51
#define M 109
#define ZERO 48
#define ONE 49

/**
  isWordInDictionary function checks to see if the word is in the dictionary or not

  @param char **dictionaryFile the dictionary file being passed in
  @param char *wordtoCheck the current word being looked for in the dictionary
  @param int *lengthOfDictionary the number of lines in the dictionary file 
  @return 1 if word is in dictionary 0 if word is not found in dictionary
*/
int isWordInDictionary(char **dictionaryFile, char *wordToCheck, int *lengthOfDictionary)
{
  for(int i = 0; i < *lengthOfDictionary; i++) {
    if(strcmp(dictionaryFile[i], wordToCheck) == 0) {
      return 1;
    }
  }
  return 0;
}    

/**
  Adds the specified word to the dictionary array
  
  @param char **dictionary the dictionary file
  @param char *wordToAdd the word being added to the dictionary
  @param int *dictionaryLength the length of the dictionary file
*/
void addWordToDictionary(char **dictionary, char *wordToAdd, int *dictionaryLength)
{
  //Allocate space for new size of dictionary
  dictionary = (char **)realloc(dictionary, (*dictionaryLength + 1) * sizeof(char *));
  dictionary[*dictionaryLength] = (char *)malloc((strlen(wordToAdd) * sizeof(char)) +1);
  //Copy over the word to dictionary
  strcpy(dictionary[*dictionaryLength], wordToAdd);
} 

/**
  Replaces the target word in the text file with whatever the user inputs
  
  @param char *currentLine the current line with the target word being worked with
  @param char *replacement the input being inserted into the current line
  @param char *partBeingReplaced the target word being replaced
*/
char* replaceWord(char *currentLine, char *replacement, char *partBeingReplaced)
{
  //Allocate memory for new line with replacement
  char *newLine = malloc(strlen(currentLine) + strlen(replacement) - strlen(partBeingReplaced) + 1);
  //Put pointer to front of new line
  char *hold = newLine;
  
  while(*currentLine) {
    //Strings are not the same
    if(!strncmp(currentLine, partBeingReplaced, strlen(partBeingReplaced))) {
      //Concatenate sentence with replacement
      strcat(hold, replacement);
      currentLine += strlen(partBeingReplaced);
      hold += strlen(replacement);
    }
    //Strings are same
    else {
      //Traverse
      *hold = *currentLine;
      hold++;
      currentLine++;
    }
  }
  *hold = 0;
  return newLine;
}  
 
  
/**
  Main function handles command line arguments, finds words in the text,
  checks to see if they are in the dictionary, and responds to user commands.
  
  @param int argc the number of command line arguments
  @param char *argv the command line arguments
*/
int main(int argc, char *argv[])
{
  char *nameOfDictionaryFile;
  FILE *sp, *dp;
  //One command line argument; file supposed to be spellchecked
  if(argc == 2) {
    sp = fopen(argv[1], "r");
    dp = fopen("words.txt", "r");
    
    nameOfDictionaryFile = "words.txt";
    //Can't open files
    if((!sp) && (!dp)) {
      fprintf(stderr, "Can't open file: argv[1]");
    }
    else if(!sp) {
      fprintf(stderr, "Can't open file: argv[1]");
    }
    else if(!dp) {
      fprintf(stderr, "Can't open file: words.txt");
    }
  }
  //Two command line arguments; file suppposed to be spellchecked and dictionary file
  else if(argc == 3) {
    sp = fopen(argv[1], "r");
    dp = fopen(argv[2], "r");
    
    nameOfDictionaryFile = argv[2];
    //Can't open files
    if((!sp) && (!dp)) {
      fprintf(stderr, "Can't open file: argv[1]");
    }
    else if(!sp) {
      fprintf(stderr, "Can't open file: argv[1]");
    }
    else if(!dp) {
      fprintf(stderr, "Can't open file: argv[2]");
    }
  }
  //Invalid command line arguments
  else {
    fprintf(stderr, "usage: spellcheck <textfile.txt> [words.txt]");
    exit(EXIT_FAILURE);
  }
  
  int spZero = 0;
  int dZero = 0;
  int *spellFileCount = &spZero;
  int *dictionaryCount = &dZero;
  
  //Count lines in text file
  char h;
  while(!feof(sp)) {
    h = fgetc(sp);
    if(h == '\n') {
      (*spellFileCount)++;
    }
  }
  
  //Count lines in dictionary file
  char y;
  while(!feof(dp)) {
    y = fgetc(dp);
    if(y == '\n') {
      (*dictionaryCount)++;
    }
  }
  
  
  
  //Sort text file into array
  char **spellFile = readLines(argv[1], spellFileCount);

  //Sort dictionary into array
  char **dictionary = readLinesForDictionary(nameOfDictionaryFile, dictionaryCount);
  
  //Compare text words to dictionary words
  for(int i = 0; i < *spellFileCount; i++) {
    char *currentLine = spellFile[i];
    int lineLength = strlen(spellFile[i]);
    char *currentWord;
    int position = 0;
    int positionTwo = 0;
    int startOfWord = 0;
    while(position < lineLength) {
      //Not a letter in the word
      if(isalpha(currentLine[position]) == 0) {
        position++;
        continue;
      }
      
      //Is a letter in the word
      else {
        positionTwo = position;
        int wordLength = 0;
        while(isalpha(currentLine[positionTwo])) {
          wordLength++;
          positionTwo++;
        }
        
        //Allocate memory for currentWord
        currentWord = (char *)malloc((wordLength * sizeof(char)) + 1);
        startOfWord = position;
        //Fill currentWord plus null character
        for(int j = 0; j < wordLength; j++) {
          currentWord[j] = currentLine[position++];
        }
        currentWord[wordLength] = '\0';
      }
    }
      
      //Change to lower case
      for(int k = 0; k < strlen(currentWord); k++) {
        currentWord[k] = tolower(currentWord[k]);
      }
      
      //Check to see if word is in dictionary
      int check = isWordInDictionary(dictionary, currentWord, dictionaryCount);
     
      //Word is in dictionary
      if(check == 1) {
        continue;
      }
      //Word is not in dictionary and at the end of dictonary
      else {
        //Print context lines
        
        //Target word is in first line of file
        if(i == 0) {
          _Bool end = false;
          printf("\n");
          //Print 1st line with target word
          for(int p = 0; p < strlen(spellFile[i]); p++) {
            if(p == startOfWord) {
              //Change color to red
              printf("%c%c%c%c%c", ESC,BRACKET,THREE,ONE,M);
            }
            //End of word
            if(p == startOfWord + strlen(currentWord)) {
              //Change color to black
              printf("%c%c%c%c",ESC,BRACKET,ZERO,M);
            }
            //Word is at end of line
            if(startOfWord + strlen(currentWord) == strlen(spellFile[i])) {
              end = true;
            } 
            printf("%c", currentLine[p]);
          }
          //Change color to black before next line is printed
          //Or print a space after target word
          if(end == true) {
            printf("%c%c%c%c",ESC,BRACKET,ZERO,M);
          }
          else if(end == false) {
            printf(" ");
          }
          //Print 2nd line
          printf("\n");
          printf("%s\n", spellFile[i+1]);
        }
        
        //Target word is in last line of file
        else if(i == *spellFileCount - 1) {
          _Bool end = false;
          printf("\n");
          //Print to 2nd to last line
          printf("%s\n", spellFile[i-1]);
          //Print last line with target word
          for(int p = 0; p < strlen(spellFile[i]); p++) {
            if(p == startOfWord) {
              //Change color to red
              printf("%c%c%c%c%c", ESC,BRACKET,THREE,ONE,M);
            }
            //End of word
            if(p == startOfWord + strlen(currentWord)) {
              //Change color to black
              printf("%c%c%c%c",ESC,BRACKET,ZERO,M);
            }
            //Word is at end of line
            if(startOfWord + strlen(currentWord) == strlen(spellFile[i])) {
              end = true;
            } 
            printf("%c", currentLine[p]);
          }
          //Change color to black before next line is printed
          //Or print a space after target word
          if(end == true) {
            printf("%c%c%c%c",ESC,BRACKET,ZERO,M);
          }
          else if(end == false) {
            printf(" ");
          }
          printf("\n");
        }
        
        //Target word is neither first or last line of file
        else {
          _Bool end = false;
          printf("\n");
          //Print line before line with target word
          printf("%s\n", spellFile[i-1]);
          //Print line with target word
          for(int p = 0; p < strlen(spellFile[i]); p++) {
            if(p == startOfWord) {
              //Change color to red
              printf("%c%c%c%c%c", ESC,BRACKET,THREE,ONE,M);
            }
            //End of word
            if(p == startOfWord + strlen(currentWord)) {
              //Change color to black
              printf("%c%c%c%c",ESC,BRACKET,ZERO,M);
            }
            //Word is at end of line
            if(startOfWord + strlen(currentWord) == strlen(spellFile[i])) {
              end = true;
            } 
            printf("%c", currentLine[p]);
          }
          //Change color to black before next line is printed
          //Or print a space after target word
          if(end == true) {
            printf("%c%c%c%c",ESC,BRACKET,ZERO,M);
          }
          else if(end == false) {
            printf(" ");
          }
          //Print line after line with target word
          printf("\n");
          printf("%s\n", spellFile[i+1]);
        }
        //Prompt user about misspelled word
        char *response = (char *)malloc(MAX_SIZE * sizeof(char));
        reprompt:
        printf("(r)eplace, (a)dd, (n)ext or (q)uit: ");
        scanf("%s", response);
        char c;
        while(c != '\n') {
          c = getchar();
        }
        //q for quit
        if(response[0] == 'q') {
          printf("Discarding changes\n");
          exit(1);
        }
        //n for skip to next word
        else if(response[0] == 'n') {
          continue;
        }
        //a for add to dictionary
        else if(response[0] == 'a') {
          addWordToDictionary(dictionary, currentWord, dictionaryCount);
        }
        //r for replace
        else if(response[0] == 'r') {
          char *replacement = response + 1;
          spellFile[i] = replaceWord(currentLine, replacement, currentWord);
        }
        //other input
        else {
          printf("Unknown command\n");
          goto reprompt;
        }
        free(response);
      }
      free(currentWord);
  }
  //Backup the file
  printf("Spellcheck complete.\n");
  //int check;
  //char *oldFile = argv[1];
  //char *bak = ".bak";
  //char *backupFile = strcat(oldFile, bak);
  //check = rename(oldFile, backupFile);
  //printf("Backing up %s to %s\n", argv[1], backupFile);
  //FILE *wp = fopen(argv[1], "w");
  //for(int w = 0; w < *spellFileCount; w++) {
    //fprintf(wp, "%s\n", spellFile[w]);
  //}
  //printf("Writing updated %s\n", argv[1]);
  
  char *bak = ".bak";
  char *backupFile = strcat(argv[1], bak);
  
  FILE *op = fopen(argv[1], "r");
  FILE *bp = fopen(backupFile, "w");
  
  printf("%s\n", argv[1]);
  printf("%s\n", bak);
  printf("%s\n", backupFile);
  
  //fclose(wp);
 
  //Close other files
  fclose(sp);
  fclose(dp);
  
  //Free memory
  freeLines(spellFile, *spellFileCount);
  freeLines(dictionary, *dictionaryCount);
  
  return 0;
}