#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define START_SIZE 100


// char *replaceWord(char *currentLine, char *replacement, char *partBeingReplaced)
// {
  // char *point = malloc(strlen(currentLine) + strlen(replacement) - strlen(partBeingReplaced) + 1);
  // char *hold = point;
  //*point = 0;
  
  // while(*currentLine) {
    // if(!strncmp(currentLine, partBeingReplaced, strlen(partBeingReplaced))) {
      // strcat(hold, replacement);
      // currentLine += strlen(partBeingReplaced);
      // hold += strlen(replacement);
    // }
    // else {
      // *hold = *currentLine;
      // hold++;
      // currentLine++;
    // }
  // }
  // *hold = 0;
  // return point;
// }


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
    words[(*count)++] = readLine(rp);
  }
  return words;
}

 int main() { 
  FILE *rp = fopen("text_01.txt", "r");
  
  int myZero = 0;
  int *spellFileCount = &myZero;
  
  char h;
  while(!feof(rp)) {
    h = fgetc(rp);
    if(h == '\n') {
      (*spellFileCount)++;
    }
  }
  
  char *myFile = "text_01.txt";
  char **textFile = readLines(myFile, spellFileCount);
  
  for(int i = 0; i < *spellFileCount; i++) {
    printf("%s\n", textFile[i]);
  }
  
}
 