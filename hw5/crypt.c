/**
  @file crypt.c
  @author Wesley Coats wrcoats
  
  This file contains the main function and is responsible for handling command line arguments
  and file opening/closing
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "des.h"

#define NUM_OF_ARGS 5
#define KEY_LENGTH 8
#define BLOCK_SIZE 8


/**
  The main function responsible for executing the program
  
  @param int argc the number of command line arguments
  @param char *argv the actual command line arguments
*/
int main(int argc, char *argv[])
{
  //Invalid number of command line arguments
  if(argc != NUM_OF_ARGS) {
    fprintf(stderr, "usage: crypt <e|d> <key> <inputfile> <outputfile>");
  }
  
  //Invalid mode
  // if(argv[1] != 'e' || argv[1] != 'd') {
    // fprintf(stderr, "Incorrect mode");
  // }
  
  //Invalid key
  if(strlen(argv[2]) != KEY_LENGTH) {
    fprintf(stderr, "Key must be exactly 8 bytes");
  }
  
  //Open read and write files
  FILE *ip = fopen(argv[3], "r");
  FILE *op = fopen(argv[4], "w");
  
  //Invalid file
  //Both files can't be opened
  if((!ip) && (!op)) {
    fprintf(stderr, "Can't open file: %s", argv[3]);
  }
  
  //Input file can't be opened
  if(!ip) {
    fprintf(stderr, "Can't open file: %s", argv[3]);
  }
  
  //Output file can't be opened
  if(!op) {
    fprintf(stderr, "Can't open file: %s", argv[4]);
  }
  
  //Close files
  fclose(ip);
  fclose(op);
}