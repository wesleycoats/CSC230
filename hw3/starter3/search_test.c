/**
 * Test program for search.c.
 */
#include "search.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/** Number of assertEquals() calls */
static int num_tests;
/** Number of tests that pass */
static int pass_tests;

/** Stores the test grid */
static unsigned char test_grid[MAX_SIZE][MAX_SIZE];

/** Used to reset the set grid */
static unsigned char orig_grid[MAX_SIZE][MAX_SIZE] = {
   {'q', 's', 'm', 'v', 'i', 'y', 'x', 'a', 'z'},
   {'r', 't', 'e', 's', 't', 'u', 'n', 'g', 'y'},
   {'a', 'b', 'r', 'a', 'n', 'w', 'z', 'u', 'a'},
   {'h', 'n', 'g', 'i', 's', 'e', 'd', 'b', 'r'},
   {'c', 't', 'l', 'a', 'k', 's', 'a', 't', 'r'},
   {'c', 'o', 'm', 'p', 'u', 't', 'e', 'r', 'a'},
   {'x', 't', 'p', 'r', 'o', 'g', 'r', 'a', 'm'},
   {'r', 'e', 't', 'n', 'i', 'o', 'p', 'q', 'u'},
   {'n', 'n', 's', 'c', 'i', 'e', 'n', 'c', 'e'}};

/**
 * Compares the expected and actual values. Prints the
 * result of the test with a message identifying the test.
 * @param msg test message
 * @param exp expected value
 * @param act actual value
 */
void assertEquals(char *msg, int exp, int act)
{
   num_tests++;
   if (exp == act) {
      printf("%4s %s\n", "PASS", msg);
      pass_tests++;
   } else {
      printf("%4s %s\n", "FAIL", msg);
   }
}

/**
 * Resets the grid back to the default values.
 */
void resetGrid()
{
   for (int i = 0; i < MAX_SIZE; i++) {
      for (int j = 0; j < MAX_SIZE; j++) {
         test_grid[i][j] = orig_grid[i][j];
      }
   }
}

/**
 * Tests the matches function.
 */
void testMatches()
{
   resetGrid();
   int rtn;

   //Test invalid directions
   rtn = matches("computer", test_grid, 0, 0, -1);
   assertEquals("Direction of -1", -1, rtn);

   //Test a word is found
   rtn = matches("computer", test_grid, 5, 0, 0);
   assertEquals("Computer found", 1, rtn);

}

/**
 * Tests the find function.
 */
void testFind()
{
   resetGrid();
   int rtn;
   
   //Test finding a word
   char word[] = "computer";
   rtn = find("computer", test_grid);
   assertEquals("Finds computer", 1, rtn);
   //Checks that computer is now COMPUTER
   for (int i = 0; i < 8; i++) {
      assertEquals("Checking converted to upper case", toupper(word[i]), test_grid[5][i]);
   }

}

/**
 * Starts the program, runs the tests, and summarizes the 
 * results.
 */
int main()
{
   testMatches();
   testFind();

   printf("%d Passing / %d Tests\n", pass_tests, num_tests);

   if (pass_tests != num_tests) {
      return EXIT_FAILURE;
   }
   return EXIT_SUCCESS;
}
