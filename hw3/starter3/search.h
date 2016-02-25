/**
  @file search.h
  @author Wesley Coats wrcoats
  
  The header file for search.c
*/

#define MAX_SIZE 9

int find(char word[], unsigned char[MAX_SIZE][MAX_SIZE]);

int matches(char word[], unsigned char[MAX_SIZE][MAX_SIZE], int row, int col, int direction);