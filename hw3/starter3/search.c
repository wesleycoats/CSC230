/**
  @file search.c
  @author Wesley Coats wrcoats
  
  Responsible for finding words in the wordsearch grid and updating them to all caps
*/

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "search.h"

#define MAX_SIZE 9
#define RIGHT 0
#define UP_RIGHT 1
#define UP 2
#define UP_LEFT 3
#define LEFT 4
#define DOWN_LEFT 5
#define DOWN 6
#define DOWN_RIGHT 7

/**
  Finds the target word in the wordsearch and updates it to all caps if it is found
  
  @param word the word being searched for
  @param grid the wordsearch grid
  @return 1 if the word is found or 0 if it is not found
*/
int find(char word[], unsigned char grid[MAX_SIZE][MAX_SIZE])
{
  int result = 0;
  for(int i = 0; i < MAX_SIZE; i++) {
    for (int j = 0; j < MAX_SIZE; j++) {
      for(int k = 0; k < MAX_SIZE - 1; k++) {
        result = matches(word, grid, i, j, k);
        if(result == 1) {
          int newi = i;
          int newj = j;
          int m = 0;
          while(word[m]) {
            if(k == RIGHT) {
              grid[newi][newj] = toupper(grid[newi][newj]);
              newj++; //right one
            }
            else if(k == UP_RIGHT) {
              grid[newi][newj] = toupper(grid[newi][newj]);
              newi--; //up one
              newj++; //right one
            }
            else if(k == UP) {
              grid[newi][newj] = toupper(grid[newi][newj]);
              newi--; //up one
            }
            else if(k == UP_LEFT) {
              grid[newi][newj] = toupper(grid[newi][newj]);
              newi--; //up one
              newj--; //left one
            }
            else if(k == LEFT) {
              grid[newi][newj] = toupper(grid[newi][newj]);
              newj--; //left one
            }
            else if(k == DOWN_LEFT) {
              grid[newi][newj] = toupper(grid[newi][newj]);
              newi++; //down one
              newj--; //left one
            }
            else if(k == DOWN) {
              grid[newi][newj] = toupper(grid[newi][newj]);
              newi++; //down one
            }
            else if(k == DOWN_RIGHT) {
              grid[newi][newj] = toupper(grid[newi][newj]);
              newi++; //down one
              newj++; //right one
            }
            m++;  
          }
        }
      }
    }
  }
  return result;
}

/**
  Starts at intersection of row and column and looks in specified direction for the word
  
  @param word the word being searched for
  @param grid the wordsearch grid
  @param row the row being passed in
  @param col the col being passed in
  @param direction the direction being searched
  @return 1 if word is found, 0 if word is not found
*/
int matches(char word[], unsigned char grid[MAX_SIZE][MAX_SIZE], int row, int col, int direction)
{
  int answer = 0;
  int wordLength = strlen(word);
  
  //If illegal direction
  if(direction < RIGHT || direction > DOWN_RIGHT) {
    answer = -1;
  }
  //Running past edge of wordsearch matrix
  if(MAX_SIZE - row > wordLength) {
    answer = -1;
  }
  if(MAX_SIZE - col > wordLength) {
    answer = -1;
  }
  int newRow = row;
  int newCol = col;
  int n = 0;
  while(word[n]) {
    if(direction == RIGHT) {
      if(word[n] == tolower(grid[newRow][newCol])) {
        newCol++; //right one
        answer = 1;
      }
      else {
        return 0;
      }
    }
    else if(direction == UP_RIGHT) {
      if(word[n] == tolower(grid[newRow][newCol])) {
        newRow--; //up one
        newCol++; //right one
        answer = 1;
      }
      else {
        return 0;
      }
    }
    else if(direction == UP) {
      if(word[n] == tolower(grid[newRow][newCol])) {
        newRow--; //up one
        answer = 1;
      }
      else {
        return 0;
      }
    }
    else if(direction == UP_LEFT) {
      if(word[n] == tolower(grid[newRow][newCol])) {
        newRow--; //up one
        newCol--; //left one
        answer = 1;
      }
      else {
        return 0;
      }
    }
    else if(direction == LEFT) {
      if(word[n] == tolower(grid[newRow][newCol])) {
        newCol--; //left one
        answer = 1;
      }
      else {
        return 0;
      }
    }
    else if(direction == DOWN_LEFT) {
      if(word[n] == tolower(grid[newRow][newCol])) {
        newRow++; //down one
        newCol--; //left one
        answer = 1;
      }
      else {
        return 0;
      }
    }
    else if(direction == DOWN) {
      if(word[n] == tolower(grid[newRow][newCol])) {
        newRow++; //down one
        answer = 1;
      }
      else {
        return 0;
      }
    }
    else if(direction == DOWN_RIGHT) {
      if(word[n] == tolower(grid[newRow][newCol])) {
        newRow++; //down one
        newCol++; //right one
        answer = 1;
      }
      else {
        return 0;
      }
    }
    n++;
  }
  return answer;
}