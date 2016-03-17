#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>







char *readLine(FILE *dp) {
  //FILE *fp = fopen("text_01.txt", "r");
  int len = 0;
  int capacity = 500;
  //Allocate array for line
  char *line = (char *)malloc(capacity * sizeof(char));
  //Process line into array
  char b;
  // if(fscanf(fp, "%c", &b) == EOF) {
    // return NULL;
  // }
  while(fscanf(dp, "%c", &b) == 1 && (b != '\n' && b != EOF)) {
    //Grow array if necessary
    if(len >= capacity) {
      capacity *= 2;
      line = (char *)realloc(line, capacity * sizeof(char));
    }
    line[len++] = b;
  }
return line;  
}

 int main() { 
  int count = 0;
  int capacity = 5;
  FILE *rp = fopen("text_01.txt", "r");
  //Allocate outer and each of inner arrays
  char **words = (char **)malloc(capacity * sizeof(char *));
  for(int i = 0; i < capacity; i++) {
    words[i] = (char *)malloc(capacity * sizeof(char));
  //Resize array if necessary
    // if(*count >= capacity) {
      // capacity *= 2;
      // **words = (char **)realloc(capacity * sizeof(char **));
    // }
    words[(count)++] = readLine(rp);
  }
  for(int i = 0; i < capacity; i++) {
  printf("%s\n", words[i]);
  }
 }