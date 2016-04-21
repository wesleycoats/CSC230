/**
  @file mygrep.c
  @author Wesley Coats wrcoats
  
  The mygrep file is responsible for the main function, handling command line arguments, parsing regular expressions,
  and matching it against lines from input.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pattern.h"

#define START_SIZE 100

/**
   Return true if the given character is ordinary, if it should just
   match occurrences of itself.  This returns false for metacharacters
   like '*' that control how patterns are matched.

   @param c Character that should be evaluated as ordinary or special.
   @return True if c is not special.
*/
static bool ordinary( char c )
{
  // See if c is on our list of special characters.
  if ( strchr( ".^$*?+|()[{", c ) )
    return false;
  return true;
}

/**
  Print the appropriate error message for an invalid pattern and exit unsuccessfully.
*/
static void invalidPattern()
{
  fprintf( stderr, "Invalid pattern\n" );
  exit( EXIT_FAILURE );
}

/**
   Parse regular expression syntax with the highest precedence,
   individual, ordinary symbols, start and end anchors, character
   classes and patterns surrounded by parentheses.

   @param str The string being parsed.
   @param pos A pass-by-reference value for the location in str being parsed,
              increased as characters from str are parsed.
   @return a dynamically allocated representation of the pattern for the next
           portion of str.
*/
static Pattern *parseAtomicPattern( char *str, int *pos )
{
  if ( ordinary( str[ *pos ] ) ) {
    return makeSymbolPattern( str[ (*pos)++ ] );
  }
  
  //Dot symbol
  //Any character except empty string
  if(str[*pos] == '.') {
    return makeDotSymbolPattern(str[(*pos)++]);
  }
  
  //Carrot symbol
  //Start of line
  if(str[*pos] == '^') {
    (*pos)++;
    char *tempLine = (char *)calloc(strlen(str), sizeof(char));
    for(int i = 0; i < strlen(str) - 1; i++) {
      if(str[i] == '|') {
        break;
      }
      tempLine[i] = str[(*pos)++];
    }
    tempLine[strlen(str) -1] = '\0';
    return makeCarrotSymbolPattern(tempLine);
  }
  
  //Dollar sign symbol
  //End of line
  if(str[strlen(str) - 1] == '$') {
    char *tempLine = (char *)calloc(strlen(str), sizeof(char));
    for(int i = 0; i < (strlen(str) - 1); i++) {
      tempLine[i] = str[(*pos)++];
    }
    (*pos)++;
    tempLine[strlen(str) - 1] = '\0';
    return makeDollarSignSymbolPattern(tempLine);
  }
  
  //Bracket symbol
  //Match anything inside except ] or newline
  if(str[*pos] == '[') {
    int currentLength = 0;
    for(int i = (*pos) + 1; i < strlen(str); i++) {
      if(str[i] == ']') {
        break;
      }
      currentLength++;
    }
    (*pos)++;
    char *tempLine = (char *)malloc((currentLength + 1) * sizeof(char));
    for(int i = 0; i <  currentLength; i++) {
      tempLine[i] = str[(*pos)++];
    }
    tempLine[currentLength] = '\0';
    return makeBracketSymbolPattern;
  }
  
  
  invalidPattern();
  return NULL; // Just to make the compiler happy.
}

/**
   Parse regular expression syntax with the second-highest precedence,
   a pattern, p, optionally followed by one or more repetition syntax like '*' or '+'.
   If there's no repetition syntax, it just returns the pattern object for p.

   @param str The string being parsed.
   @param pos A pass-by-reference value for the location in str being parsed,
              increased as characters from str are parsed.
   @return a dynamically allocated representation of the pattern for the next
           portion of str.
*/
static Pattern *parseRepetition( char *str, int *pos )
{
  Pattern *p = parseAtomicPattern( str, pos );
  return p;
}

/**
   Parse regular expression syntax with the third-highest precedence,
   one pattern, p, (optionally) followed by additional patterns
   (concatenation).  If there are no additional patterns, it just
   returns the pattern object for p.

   @param str The string being parsed.
   @param pos A pass-by-reference value for the location in str being parsed,
              increased as characters from str are parsed.
   @return a dynamically allocated representation of the pattern for the next
           portion of str.
*/
static Pattern *parseConcatenation( char *str, int *pos )
{
  // Parse the first pattern
  Pattern *p1 = parseRepetition( str, pos );
  // While there are additional patterns, parse them
  while ( str[ *pos ] && str[ *pos ] != '|' && str[ *pos ] != ')' ) {
    Pattern *p2 = parseRepetition( str, pos );
    // And build a concatenation pattern to match the sequence.
    p1 = makeConcatenationPattern( p1, p2 );
  }

  return p1;
}

/**
   Parse regular expression syntax with the lowest precedence,
   one pattern, p, (optionally) followed by additional patterns
   separated by | (alternation).  If there are no additional patterns, it just
   returns the pattern object for p.

   @param str The string being parsed.
   @param pos A pass-by-reference value for the location in str being parsed, increased as characters
              from str are parsed.
   @return a dynamically allocated representation of the pattern for the next portion of str.
*/
static Pattern *parseAlternation( char *str, int *pos )
{
  Pattern *p1 = parseConcatenation( str, pos );
  return p1;
}



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
  int numLines = 0;
  FILE *rp = fopen(fileName, "r");
  //Allocate outer and each of inner arrays
  char **words = (char **)malloc(capacity * sizeof(char *));
  for(int i = 0; i < capacity; i++) {
     //Resize array if necessary
    if(numLines >= capacity) {
      capacity *= 2;
      words = (char **)realloc(words, capacity * sizeof(char **));
    }
    words[numLines++] = readLine(rp);
  }
  return words;
}


/**
   A temporary version of main, that just shows a little bit about how
   regular expressions and pattern matching are supposed to work.
*/
int main(int argc, char *argv[])
{
  //Count lines in input file
  FILE *rp = fopen(argv[2], "r");
  
  int myZero = 0;
  int *inputFileCount = &myZero;
  
  char h;
  while(!feof(rp)) {
    h = fgetc(rp);
    if(h == '\n') {
      (*inputFileCount)++;
    }
  }
  
  //Read lines and print them
  char **entireFile = readLines(argv[2], inputFileCount);
  
  Pattern *pat;
  int pos = 0;
  
  //Three total command line arguments
  if(argc == 3) {
    pat = parseAlternation(argv[1], &pos);
    FILE *op = fopen(argv[2], "r");
    if(!op) {
      fprintf(stderr, "Can't open input file: %s", argv[2]);
    }
    
    for(int i = 0; i < *inputFileCount; i++) {
      //Create boolean array
      bool before[strlen(entireFile[i]) + 1];
      for(int j = 0; j < strlen(entireFile[i]); j++) {
        before[i] = true;
      }
      //Creat boolean after array
      bool after[strlen(entireFile[i]) + 1];
      pat->match(pat, strlen(entireFile[i]), entireFile[i], before, after);
      
      //Print matched lines
      for(int x = 0; x < sizeof(before)/sizeof(before[0]); x++) {
        if(after[x] == true) {
          printf("%s\n", entireFile[x]);
          break;
        }
      }
    }   
  }  
  
  //Two total command line arguments
  else if(argc == 2) {
    pat = parseAlternation(argv[1], &pos);
  }
  
  //Invalid arguments
  else {
    fprintf(stderr, "usage: mygrep <pattern> [input-file.txt]");
  }
 

  // Parse a simple pattern.
  // int pos = 0;
  // pat = parseAlternation( "b", &pos );
  // printf( "For pattern 'b'\n" );

  // Try matching this pattern against "abc", I make a new block here
  // so I can let these variables go out of scope when I'm done with them.
  // {
    // char *str = "abc";

    //before we've matched anything, everywhere in the string is a match.
    // bool before[] = { true, true, true, true };
    // bool after[ sizeof( before ) / sizeof( before[ 0 ] ) ];

    //Show where the marks are before and after matching.
    // printf( "Before matching: " );
    // reportMarks( str, before );

    // pat->match( pat, strlen( str ), str, before, after );

    // printf( "After matching:  " );
    // reportMarks( str, after );
  // }

  //Try matching against a longer string, with more occurrences of b.
  // {
    // char *str = "abbbcbbdb";

    // bool before[] = { true, true, true, true, true, true, true, true, true, true  };
    // bool after[ sizeof( before ) / sizeof( before[ 0 ] ) ];

    // printf( "Before matching: " );
    // reportMarks( str, before );

    // pat->match( pat, strlen( str ), str, before, after );

    // printf( "After matching:  " );
    // reportMarks( str, after );
  // }

  //Done with the first pattern.
  // pat->destroy( pat );

  //Try a pattern with concatenation.
  // pos = 0;
  // pat = parseAlternation( "bc", &pos );
  // printf( "For pattern 'bc'\n" );

  // {
    // char *str = "abcbcdbcb";

    // bool before[] = { true, true, true, true, true, true, true, true, true, true  };
    // bool after[ sizeof( before ) / sizeof( before[ 0 ] ) ];

    // printf( "Before matching: " );
    // reportMarks( str, before );

    // pat->match( pat, strlen( str ), str, before, after );

    // printf( "After matching:  " );
    // reportMarks( str, after );
  // }

  // pat->destroy( pat );

   return EXIT_SUCCESS;
 }
